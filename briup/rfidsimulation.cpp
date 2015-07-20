#include "rfidsimulation.h"
#include "ui_rfidsimulation.h"
#include <QMovie>
#include <QBrush>
#include <QSerialPortInfo>
#include <QTimer>
#include <QBitmap>
#include <QPixmap>
#include <QPainter>

RFIDsimulation::RFIDsimulation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RFIDsimulation)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
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
    QMovie *movie = new QMovie(":/images/signal3.gif");
    ui->signal->setMovie(movie);
    movie->start();
    ui->contents->setWordWrap(true);
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
        serialport->setBaudRate(4800);
        //设置数据位
        serialport->setDataBits((QSerialPort::DataBits)(8));
        //设置停止位
        serialport->setStopBits((QSerialPort::StopBits)(1));
        //校验
        serialport->setParity((QSerialPort::Parity)(0));//23333333
        this->isPortOpen=true;
        readTimer.start(200);//每隔2ms
        connect(&readTimer,SIGNAL(timeout()),this,SLOT(readSlot()));
        //连接设备
    }
}

RFIDsimulation::~RFIDsimulation()
{
    delete ui;
}
void RFIDsimulation::readSlot(){
    QByteArray data;
    data=this->serialport->readAll();//接受数据
    if(data.isEmpty()){
        ui->RFIDcard->clear();
       return;
    }
    QPixmap  card ;
    card.load(":/images/RFIDcard.png");
    ui->RFIDcard->setPixmap(card);
    for(int i=2;i<data.length();i++)
    {
    order[i]=(char)data.at(i);
  }
    QString str=QString(QLatin1String(order));
    ui->contents->setText(str);
}
