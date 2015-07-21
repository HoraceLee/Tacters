#include "interinstruction.h"
#include "ui_interinstruction.h"
#include <QMovie>
#include <QLabel>
#include <QBitmap>
#include <QPainter>
#include <QTimer>
#include <qserialportinfo.h>
#include "frame.h"

interinstruction::interinstruction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::interinstruction)
{
    ui->setupUi(this);
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
    movie = new QMovie(":/images/movie.gif");
    ui->label->setMovie(movie);
    movie->start();
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
        char send[2]={0x03,0xff};
        serialport->write(send);
        readTimer.start(200);//每隔200ms
    }
    connect(&readTimer,SIGNAL(timeout()),this,SLOT(readSlot()));
}

interinstruction::~interinstruction()
{
    delete ui;
}
void interinstruction::readSlot()
{
    QByteArray data;
    data=this->serialport->readAll();//接受数据
    if(!isFrame(data,0x03,3)){
        return;
    }
    if(data.isEmpty()) return ;
    if(data[0]!=3) return ;
    order=(unsigned char)data.at(1);
    switch(order)
    {
    case 1:
        movie->stop();
        break;
    case 2:
        movie->start();
        break;
    default:
        break;
    }
}

void interinstruction::on_clsoeBtn_clicked()
{
    if(serialport == NULL){
        return;
    }
    if(!isPortOpen){
        serialport = NULL;
        return;
    }
    readTimer.stop();
    serialport->close();
    serialport = NULL;
    this->close();
}
