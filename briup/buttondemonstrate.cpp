#include "buttondemonstrate.h"
#include "ui_buttondemonstrate.h"

#include <QPixmap>
#include <QTimer>
#include <qserialport.h>
#include <qserialportinfo.h>
#include <QBitmap>
#include <QPainter>
#include <QPaintEvent>
#include "frame.h"

int reciver;

buttonDemonstrate::buttonDemonstrate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::buttonDemonstrate)
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
    this->isPortOpen=false;
    serialport = new QSerialPort;
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
        char send[2]={0x12,0xff};
        serialport->write(send);
        readTimer.start(200);//每隔2ms
        connect(&readTimer,SIGNAL(timeout()),this,SLOT(readSlot()));
        //连接设备
    }
}

buttonDemonstrate::~buttonDemonstrate()
{
    delete ui;
}
void buttonDemonstrate::readSlot()
{
    QByteArray data;
    data=this->serialport->readAll();//接受数据
    if(!isFrame(data,0x12,3))
    if(data.isEmpty())
        return;
    order=(unsigned char)data.at(1);
    if(order < 0 | order > 15)
        return;
    ui->pageCover->setGeometry(50,90,61,51);
    ui->pageContents->setGeometry(130,90,61,51);
    ui->pageIntro->setGeometry(210,90,61,51);
    ui->page_1->setGeometry(290,80,61,51);
    ui->page_2->setGeometry(360,90,61,51);
    ui->page_3->setGeometry(420,90,81,61);
    ui->page_4->setGeometry(500,90,61,51);
    ui->page_5->setGeometry(570,90,61,51);
    ui->page_6->setGeometry(50,150,61,51);
    ui->page_7->setGeometry(130,140,61,61);
    ui->page_8->setGeometry(210,150,61,51);
    ui->page_9->setGeometry(280,146,81,61);
    ui->page_10->setGeometry(360,150,61,51);
    ui->page_11->setGeometry(430,150,61,51);
    ui->page_12->setGeometry(500,150,61,51);
    ui->pageEnd->setGeometry(570,140,61,61);
    QPixmap enterPixmap;
    switch (order) {
    case 0:
        enterPixmap.load(":/images/enter_0.png");
        ui->enterBtn->setPixmap(enterPixmap);
        ui->pageIntro->setGeometry(100, 210, 530, 400);
        break;
    case 1:
        enterPixmap.load(":/images/enter_1.png");
        ui->enterBtn->setPixmap(enterPixmap);
        ui->page_1->setGeometry(100, 210, 530, 400);
        break;
    case 2:
        enterPixmap.load(":/images/enter_2.png");
        ui->enterBtn->setPixmap(enterPixmap);
        ui->page_2->setGeometry(100, 210, 530, 400);
        break;
    case 3:
        enterPixmap.load(":/images/enter_3.png");
        ui->enterBtn->setPixmap(enterPixmap);
        ui->page_3->setGeometry(100, 210, 530, 400);
        break;
    case 4:
        enterPixmap.load(":/images/enter_4.png");
        ui->enterBtn->setPixmap(enterPixmap);
        ui->page_4->setGeometry(100, 210, 530, 400);
        break;
    case 5:
        enterPixmap.load(":/images/enter_5.png");
        ui->enterBtn->setPixmap(enterPixmap);
        ui->page_5->setGeometry(100, 210, 530, 400);
        break;
    case 6:
        enterPixmap.load(":/images/enter_6.png");
        ui->enterBtn->setPixmap(enterPixmap);
        ui->page_6->setGeometry(100, 210, 530, 400);
        break;
    case 7:
        enterPixmap.load(":/images/enter_7.png");
        ui->enterBtn->setPixmap(enterPixmap);
        ui->page_7->setGeometry(100, 210, 530, 400);
        break;
    case 8:
        enterPixmap.load(":/images/enter_8.png");
        ui->enterBtn->setPixmap(enterPixmap);
        ui->page_8->setGeometry(100, 210, 530, 400);
        break;
    case 9:
        enterPixmap.load(":/images/enter_9.png");
        ui->enterBtn->setPixmap(enterPixmap);
        ui->page_9->setGeometry(100, 210, 530, 400);
        break;
    case 10:
        enterPixmap.load(":/images/enter_A.png");
        ui->enterBtn->setPixmap(enterPixmap);
        ui->page_10->setGeometry(100, 210, 530, 400);
        break;
    case 11:
        enterPixmap.load(":/images/enter_B.png");
        ui->enterBtn->setPixmap(enterPixmap);
        ui->page_11->setGeometry(100, 210, 530, 400);
        break;
    case 12:
        enterPixmap.load(":/images/enter_C.png");
        ui->enterBtn->setPixmap(enterPixmap);
        ui->page_12->setGeometry(100, 210, 530, 400);
        break;
    case 13:
        enterPixmap.load(":/images/enter_D.png");
        ui->enterBtn->setPixmap(enterPixmap);
        ui->pageEnd->setGeometry(100, 210, 530, 400);
        break;
    case 14:
        enterPixmap.load(":/images/enter_star.png");
        ui->enterBtn->setPixmap(enterPixmap);
        ui->pageCover->setGeometry(100, 210, 530, 400);
        break;
    case 15:
        enterPixmap.load(":/images/enter_hashtag.png");
        ui->enterBtn->setPixmap(enterPixmap);
        ui->pageContents->setGeometry(100, 210, 530, 400);
        break;
    default:
        break;
    }
}

void buttonDemonstrate::on_pushButton_clicked()
{
    readTimer.stop();
    serialport->close();
    serialport = NULL;
    this->close();
}

void buttonDemonstrate::paintEvent(QPaintEvent *event){
    QPainter pa(this);
    QPixmap p(":/images/back_all.jpg");
    pa.drawPixmap(0,0,1000,618,p);
}
