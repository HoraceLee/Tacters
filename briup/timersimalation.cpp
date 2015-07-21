#include "timersimalation.h"
#include "ui_timersimalation.h"
#include <QDebug>
#include <QLCDNumber>
#include <QTime>
#include <QLabel>
#include <qtimer.h>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QByteArray>
#include <QSerialPortInfo>
#include <QBitmap>
#include "frame.h"

timersimalation::timersimalation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::timersimalation)
{
    ui->setupUi(this);
    ui->label->setStyleSheet("QLabel{color:black;size:100}");
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
    this->isPortOpen=false;
    serialport = new QSerialPort;

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
        char send[2]={0x02,0xff};
        serialport->write(send);
        readTimer.start(200);//每隔2ms
        connect(&readTimer,SIGNAL(timeout()),this,SLOT(readSlot()));
        //连接设备
    }
}

timersimalation::~timersimalation()
{
    delete ui;
}
void timersimalation::readSlot()
{
    QByteArray data;
    data=this->serialport->readAll();//接受数据
    if(!isFrame(data,0x02,3)){
        return;
    }
    if(data.isEmpty()){
       return;
    }
    order=(unsigned char)data.at(1);
    if(order == 0)
    {
        QPixmap pixmap;
        pixmap.load(":/images/boomggg.png");
        ui->label_4->setPixmap(pixmap);
        ui->pushButton->setText(" ");
        QTimer *timer = new QTimer(this);
        connect(timer,SIGNAL(timeout()),this,SLOT(closel()));
         timer->setSingleShot(true);
         timer->start(3000);
    }
    else{
        int minu=order/60;//分
        int sec = order%60;//秒
        ui->minute->display(minu);
        ui->second->display(sec);
    }
}

void timersimalation::on_pushButton_clicked()
{
    char sendmessage[3];
    QString s = ui->lineEdit->text();
    int send = s.toInt();
    qDebug()<<s;
    int minu=send/60;//分
    int sec = send%60;//秒
    ui->minute->display(minu);
    ui->second->display(sec);
//    char c = (char)send;
//    qDebug()<<c;

    QByteArray ba = s.toLatin1();
    char *mm = ba.data();
    int len =strlen(mm);
//    qDebug()<<len;
//    qDebug()<<mm[0];
//    qDebug()<<mm[1];
    char temp = 0;
    for(int a=0;a<len;a++){
        temp =temp + mm[a]*10^(len-a-1);
//        qDebug()<<temp;
    }
    sendmessage[0]=0x02;
//    sendmessage[1]=(temp));
    sendmessage[1]=(char)send;
//    QString nn = QString(QLatin1String(temp));
    qDebug()<<sendmessage[1];
    sendmessage[2]=0xFF;
    //应该传走sendmessage
    serialport->write(sendmessage);
}

void timersimalation::closel(){
    ui->label_4->clear();
    ui->pushButton->setText("SET");
    ui->lineEdit->clear();
    ui->minute->display(0);
    ui->second->display(0);
}

void timersimalation::on_closeBtn_clicked()
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
