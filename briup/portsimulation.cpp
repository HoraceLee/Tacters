#include "portsimulation.h"
#include "ui_portsimulation.h"
#include <QMouseEvent>
#include <QLabel>
#include <QColor>
#include "qmovie.h"
#include <QTimer>
#include <QSerialPortInfo>
#include <QBitmap>
#include <QPainter>

portsimulation::portsimulation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::portsimulation)
{
    ui->setupUi(this);
    ui->screen->setStyleSheet("QLabel{color:white;size:100}");
    ui->title->setStyleSheet("QLabel{color:white;size:100}");

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

portsimulation::~portsimulation()
{
    delete ui;
}

void portsimulation::readSlot(){
    QByteArray data;
    data=this->serialport->readAll();//接受数据
    if(data.isEmpty()){
       return;
    }
    for(int i=2;i<data.length();i++)
    {
        order[i]=(char)data.at(i);
    }
    QString str=QString(QLatin1String(order));
    QMovie *movie = new QMovie(":/images/shock.gif");
    ui->label_2->setMovie(movie);
    ui->label_2->movie()->start();
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(portDisplay(str)));
    timer->setSingleShot(true);
    timer->start(2000);

}

void portsimulation::mousePressEvent(QMouseEvent *e)
{
    int moux = ui->mouse->x();
    int mouy = ui->mouse->y();
    int mouxx = ui->mouse->width()+moux;
    int mouyy = ui->mouse->height()+mouy;
    if(e->button()==Qt::LeftButton && e->x()>moux && e->x()<mouxx && e->y()>mouy && e->y()<mouyy)
    {
        ui->title->setText("loading... ...");
        QString send = ui->lineEdit->text();
        ui->lineEdit->clear();
//        ui->screen->setText(send);
//        QString send = ui->lineEdit->text();
//        ui->screen->setText(send);
    }
}


void portsimulation::portDisplay(QString s)
{
//    ui->screen->setStyleSheet("color:#ffffff;");
//    ui->screen->setStyleSheet("size:100;");
    ui->label_2->clear();
    ui->title->setText("返回内容为：");
    ui->screen->setText(s);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(portInit()));
    timer->setSingleShot(true);
    timer->start(2000);

}

void portsimulation::portInit()
{
    ui->screen->clear();
    ui->title->setText("请输入发送内容：");
}

void portsimulation::on_pushButton_clicked()
{
    this->close();
    this->serialport->close();
}
