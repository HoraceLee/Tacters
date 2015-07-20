#include "infarredsimulation.h"
#include "ui_infarredsimulation.h"
#include <QPainter>
#include <QPixmap>
#include <QBitmap>
#include <QLabel>
#include <QMovie>
#include <qserialportinfo.h>
#include <QTimer>
#include "frame.h"

infarredsimulation::infarredsimulation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::infarredsimulation)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    movie =new QMovie(":/red.gif");
    ui->label->setMovie(movie);
    people=new QPixmap(":/people.png");
    //movie->start();
    //生成一张位图
    QBitmap objBitmap(size());
    //QPainter用于在位图上绘画
    QPainter painter(&objBitmap);
    //填充位图矩形框(用白色填充)
    painter.fillRect(rect(),Qt::white);
    painter.setBrush(QColor(0,0,0));
    //在位图上画圆角矩形(用黑色填充)
    painter.drawRoundedRect(this->rect(),10,10);
    //使用setmask过滤即可
    setMask(objBitmap);
    setMinimumWidth(850);
    setMinimumHeight(600);
    this->isPortOpen=false;
    serialport=new QSerialPort;

    if(isPortOpen){
     //停止读取数据
     readTimer.stop();
     serialport->close();
     this->isPortOpen=false;
    }
    else
    {
        //设置设备号
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            serialport->setPortName(info.portName());
        }
        serialport->open(QIODevice::ReadWrite);
        serialport->setBaudRate(9600);
        //设置数据位
        serialport->setDataBits((QSerialPort::DataBits)(8));
        //设置停止位
        serialport->setStopBits((QSerialPort::StopBits)(1));
        //校验
        serialport->setParity((QSerialPort::Parity)(0));//23333333
        this->isPortOpen=true;
        char send[2]={0x09,0xff};
        serialport->write(send);
        readTimer.start(200);//每隔2ms
        connect(&readTimer,SIGNAL(timeout()),this,SLOT(readSlot()));
        //连接设备
    }
}

infarredsimulation::~infarredsimulation()
{
    delete ui;
}

void infarredsimulation::readSlot()
{
    QByteArray data;
    data=this->serialport->readAll();//接受数据
    if(!isFrame(data,0x09,3)){
        return;
    }
    if(data.isEmpty()){
       return;
    }
    order=(unsigned char)data.at(1);
    if(order==1){
        QPixmap people(":/people.png");
        ui->label_2->setPixmap(people);
        movie->start();
    }else{
        movie->stop();
        ui->label_2->clear();
    }
}

void infarredsimulation::paintEvent(QPaintEvent *e)
{
    QPainter  painter(this);
    QPixmap pixmap(":/images/redbackground.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}

void infarredsimulation::on_closeBtn_clicked()
{
    serialport->close();
    this->close();
}
