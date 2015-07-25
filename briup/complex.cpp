#include "complex.h"
#include "ui_complex.h"

#include <QMovie>
#include <QTimer>
#include <QSerialPortInfo>
#include <QBitmap>
#include <QPainter>
#include <QByteArray>
#include "frame.h"
#include <QDebug>

int signalNum = -1;
int order = -1;
int temp = 0;
int step = 0;

Complex::Complex(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Complex)
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
    //*********************************************************************************
    connect(ui->pushButton_2,SIGNAL(on_pushButton_2_clicked()),this,SLOT(readSlot()));
    //*********************************************************************************
}

Complex::~Complex()
{
    delete ui;
}

void Complex::readSlot(){
    QByteArray data;
    QTimer *timer_2 = new QTimer();
    //E:\briup_gif
    QMovie *movie_2 = new QMovie("E:/briup_gif/2_800ms.gif");
    QMovie *movie_3 = new QMovie("E:/briup_gif/3_1800ms.gif");
    QMovie *movie_4 = new QMovie("E:/briup_gif/4_1600ms.gif");
    QMovie *movie_5 = new QMovie("E:/briup_gif/5_6100.gif");
    QMovie *movie_6 = new QMovie("E:/briup_gif/6_1500ms.gif");
    QMovie *movie_7 = new QMovie("E:/briup_gif/7_3800ms.gif");
    QMovie *movie_8 = new QMovie("E:/briup_gif/8_2600ms.gif");
    QMovie *movie_9 = new QMovie("E:/briup_gif/9_3000ms.gif");
    QMovie *movie_10 = new QMovie("E:/briup_gif/10_4500ms.gif");
    connect(timer_2,SIGNAL(timeout()),this,SLOT(stopMovie()));
    timer_2->setSingleShot(true);
    data=this->serialport->readAll();//接受数
    if( data.isEmpty() || data.length()==0 ){
        return ;
    }
    qDebug()<<data.toHex();
    switch(step){
    case 0:
        break;
    case 1:
        if(isFrame(data,0x05,3)){
            char ch = data.at(1);
            if(ch == 1){
                ui->gifLabel->setMovie(movie_2);
                ui->gifLabel->movie()->start();
                timer_2->start(850);
                signalNum = 2;
                step++;
            }
        }
        break;
    case 2:

        if(isFrame(data,0x15,3)){
            char ch = data.at(1);
            if(ch == 1){
                ui->gifLabel->setMovie(movie_3);
                ui->gifLabel->movie()->start();
                timer_2->start(2000);
                signalNum = 3;
                step++;
            }
        }
        break;
    case 3:
        if(isFrame(data,0x15,3)){
            char ch = data.at(1);
            if(ch == 2){
                ui->gifLabel->setMovie(movie_4);
                ui->gifLabel->movie()->start();
                timer_2->start(1580);
                signalNum = 4;
                step++;
            }
        }
        break;
    case 4:
        if(isFrame(data,0x15,3)){
            char ch = data.at(1);
            if(ch == 8){
                ui->gifLabel->setMovie(movie_5);
                ui->gifLabel->movie()->start();
                timer_2->start(6050);
                signalNum++;
                step++;
            }
        }
        break;
    case 5:
        if(isFrame(data,0x15,3)){
            char ch = data.at(1);
            if(ch == 9){
                ui->gifLabel->setMovie(movie_6);
                ui->gifLabel->movie()->start();
                timer_2->start(1470);
                signalNum++;
                step++;
            }
        }
        break;
    case 6:
        if(isFrame(data,0x15,3)){
            char ch = data.at(1);
            if(ch == 3){
                ui->gifLabel->setMovie(movie_7);
                ui->gifLabel->movie()->start();
                timer_2->start(3850);
                signalNum++;
                step++;
            }
        }
        break;
    case 7:
        if(isFrame(data,0x07,4)){
            char ch = data.at(1);
            if(ch >= 29){
                char message[] = {0x15,0x05,0xFF};
                serialport->write(message);
                ui->gifLabel->setMovie(movie_8);
                ui->gifLabel->movie()->start();
                timer_2->start(2580);
                signalNum++;
                step++;
            }
        }
        break;
    case 8:
        if(isFrame(data,0x05,3)){
            char ch = data.at(1);
            if(ch ==1){
                ui->gifLabel->setMovie(movie_9);
                ui->gifLabel->movie()->start();
                timer_2->start(2970);
                signalNum++;
                step++;
            }
        }
        break;
    case 9:
        if(isFrame(data,0x15,3)){
            char ch = data.at(1);
            if(ch ==7){
                ui->gifLabel->setMovie(movie_10);
                ui->gifLabel->movie()->start();
                timer_2->start(4450);
                signalNum++;
                step++;
            }
        }
        break;
    }
}

void Complex::stopMovie(){
    ui->gifLabel->movie()->stop();
    qDebug()<<"---------------";
    switch (signalNum) {
    case 2:
        qDebug()<<"2";
        char writeorder[3];
        writeorder[0]=0x15;
        writeorder[1]=0x01;
        writeorder[2]=0xff;
        serialport->write(writeorder);
        break;
    case 3:
        qDebug()<<"3";
        char writeorder2[3];
        writeorder2[0]=0x15;
        writeorder2[1]=0x02;
        writeorder2[2]=0xff;
        serialport->write(writeorder2);
        break;
    case 4:
        qDebug()<<"4";
        char writeorder3[3];
        writeorder3[0]=0x15;
        writeorder3[1]=0x08;
        writeorder3[2]=0xff;
        serialport->write(writeorder3);
        break;
    case 5:
        qDebug()<<"5";
        char writeorder4[3];
        writeorder4[0]=0x15;
        writeorder4[1]=0x09;
        writeorder4[2]=0xff;
        serialport->write(writeorder4);
        break;
    case 6:
        qDebug()<<"6";
        char writeorder5[3];
        writeorder5[0]=0x15;
        writeorder5[1]=0x03;
        writeorder5[2]=0xff;
        serialport->write(writeorder5);
        break;
    case 7:
        qDebug()<<"7";
        char writeorder6[3];
        writeorder6[0]=0x15;
        writeorder6[1]=0x04;
        writeorder6[2]=0xff;
        serialport->write(writeorder6);
        break;
    case 8:
        qDebug()<<"8";
        char writeorder7[3];
        writeorder7[0]=0x15;
        writeorder7[1]=0x06;
        writeorder7[2]=0xff;
        serialport->write(writeorder7);
        break;
    case 9:
        qDebug()<<"9";
        char writeorder8[3];
        writeorder8[0]=0x15;
        writeorder8[1]=0x07;
        writeorder8[2]=0xff;
        serialport->write(writeorder8);
        break;
    default:
        break;
    }
}

//*
//*
//*
//*测试函数
//*
//*
//*
void Complex::on_pushButton_2_clicked()
{
    order = ui->lineEdit->text().toInt();

    QMovie *movie_2 = new QMovie("E:/briup_gif/2_800ms.gif");
    QMovie *movie_3 = new QMovie("E:/briup_gif/3_1800ms.gif");
    QMovie *movie_4 = new QMovie("E:/briup_gif/4_1600ms.gif");
    QMovie *movie_5 = new QMovie("E:/briup_gif/5_6100.gif");
    QMovie *movie_6 = new QMovie("E:/briup_gif/6_1500ms.gif");
    QMovie *movie_7 = new QMovie("E:/briup_gif/7_3800ms.gif");
    QMovie *movie_8 = new QMovie("E:/briup_gif/8_2600ms.gif");
    QMovie *movie_9 = new QMovie("E:/briup_gif/9_3000ms.gif");
    QMovie *movie_10 = new QMovie("E:/briup_gif/10_4500ms.gif");
    QTimer *timer_2 = new QTimer();
    QByteArray data;
    connect(timer_2,SIGNAL(timeout()),this,SLOT(stopMovie()));
    timer_2->setSingleShot(true);

    switch (order) {
    case 1:
        ui->gifLabel->setMovie(movie_3);
        ui->gifLabel->movie()->start();
        timer_2->start(2000);
        signalNum = 3;
        temp++;
        break;
    case 2:
        ui->gifLabel->setMovie(movie_4);
        ui->gifLabel->movie()->start();
        timer_2->start(1580);
        signalNum = 4;
        break;
    case 8:
        ui->gifLabel->setMovie(movie_5);
        ui->gifLabel->movie()->start();
        timer_2->start(6050);
        signalNum = 5;
        break;
    case 9:
        ui->gifLabel->setMovie(movie_6);
        ui->gifLabel->movie()->start();
        timer_2->start(1470);
        signalNum = 6;
        break;
    case 3:
        ui->gifLabel->setMovie(movie_7);
        ui->gifLabel->movie()->start();
        timer_2->start(3850);
        signalNum = 7;
        break;
    case 7:
        ui->gifLabel->setMovie(movie_10);
        ui->gifLabel->movie()->start();
        timer_2->start(4450);
        break;
    case 11:
        ui->gifLabel->setMovie(movie_2);
        ui->gifLabel->movie()->start();
        timer_2->start(850);
        signalNum = 2;
        break;
    case 12:
        ui->gifLabel->setMovie(movie_8);
        ui->gifLabel->movie()->start();
        timer_2->start(2580);
        signalNum = 8;
        break;
    case 10:
        ui->gifLabel->setMovie(movie_9);
        ui->gifLabel->movie()->start();
        timer_2->start(2970);
        signalNum = 9;
        break;
    default:
        break;
    }
}

void Complex::on_label_LabelClicked()
{
    QMovie *movie_1 = new QMovie("E:/briup_gif/1_4550ms.gif");
    QTimer *timer_1 = new QTimer();
    step++;
    connect(timer_1,SIGNAL(timeout()),this,SLOT(stopMovie()));
    timer_1->setSingleShot(true);
    ui->gifLabel->setMovie(movie_1);
    ui->gifLabel->movie()->start();
    timer_1->start(4450);
    ui->label->clear();
    ui->label->setEnabled(false);
    char message[] = {0x15,0xFF};
    serialport->write(message);
}
