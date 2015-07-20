#include "lightdemonstrate.h"
#include "ui_lightdemonstrate.h"

#include <QMovie>
#include <QTimer>
#include <QSerialPortInfo>
#include <QBitmap>
#include <QPainter>

lightDemonstrate::lightDemonstrate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lightDemonstrate)
{
    ui->setupUi(this);

//    QMovie *daytonight = new QMovie(":/im/day_to_night.gif");
//    QMovie *nighttoday = new QMovie(":/im/night_to_day.gif");

//    QTimer *timer = new QTimer();
//    connect(timer,SIGNAL(timeout()),this,SLOT(stopMovie()));
//    timer->setSingleShot(true);

//    ui->label->setMovie(daytonight);
//    ui->label->movie()->start();

//    QTimer *timer = new QTimer();
//    connect(timer,SIGNAL(timeout()),this,SLOT(stopMovie()));
//    timer->setSingleShot(true);
//    timer->start(1100);
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
        readTimer.start(200);//每隔200ms
    }
    connect(&readTimer,SIGNAL(timeout()),this,SLOT(readSlot()));
}

lightDemonstrate::~lightDemonstrate()
{
    delete ui;
}
void lightDemonstrate::readSlot(){
    QByteArray data;
    data=this->serialport->readAll();//接受数据
    if(!data.isEmpty())
    {
        return;
    }
    if( order ==1 ){
        QMovie *daytonight = new QMovie(":/images/day_to_night.gif");
        QTimer *timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this,SLOT(stopMovie()));
        timer->setSingleShot(true);
        ui->label->setMovie(daytonight);
        ui->label->movie()->start();
        timer->start(1000);
    }else if( order == 2){
        QMovie *nighttoday = new QMovie(":/images/night_to_day.gif");
        QTimer *timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this,SLOT(stopMovie()));
        timer->setSingleShot(true);
        ui->label->setMovie(nighttoday);
        ui->label->movie()->start();
        timer->start(900);
   }
}

void lightDemonstrate::stopMovie(){
    ui->label->movie()->stop();
}


void lightDemonstrate::on_pushButton_clicked()
{
    this->close();
    this->serialport->close();
}
