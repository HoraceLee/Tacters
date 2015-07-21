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
#include "frame.h"
#include <QDebug>

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
        char send[2]={0x04,0xff};
        serialport->write(send);
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
    qDebug()<<data.toHex();
    if(!isFrame(data,0x04)){
        return;
    }
    if(data.isEmpty()){
       return;
    }
    if(data.length()<4){
        return ;
    }
    char order[data.length()-2];
    qDebug()<<"================";
    for(int i=2;i<data.length()-1;i++)
    {
        order[i-2]=(char)data.at(i);
    }
    order[data.length()-3] = 0;
    qDebug()<<order;
    QString str=QString(QLatin1String(order));
    qDebug()<<"str:::::::"<<str<<endl;
    QMovie *movie = new QMovie(":/images/shock.gif"); //ui->screen->setText(str);
    ui->label_2->setMovie(movie);
    ui->label_2->movie()->start();
    ui->title->setText("返回内容为：");
    qDebug()<<"-------------";
    ui->screen->setText(str);

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(portDisplay()));

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
        QString send_str = ui->lineEdit->text();
        ui->lineEdit->clear();
        ///////////////////////////////////////////////////
        char send[22] = {0};
//        for(int k=0;k<22;k++){
//            send[k]=0;
//        }
        QByteArray ba = send_str.toLatin1();
        char *mm = ba.data();

        int i=strlen(mm);
        int length;
        if(i>20)
            length=20;
        else
            length=i;
        for(int j=2;j<length+2;j++)
        {
            send[j]=mm[j-2];
        }
         send[0]=0x04;
         send[1]=0x21;
        send[length+2]=0xFF;
        ui->title->setText("loading... ...");
        //写入指令
        serialport->write(send);
    }
}


void portsimulation::portDisplay()
{
//    ui->screen->setStyleSheet("color:#ffffff;");
//    ui->screen->setStyleSheet("size:100;");
    ui->label_2->clear();
    qDebug()<<"shoudaolexiaoxi1"<<endl;

    qDebug()<<"shoudaolexiaoxi2"<<endl;

    qDebug()<<"shoudaolexiaoxi3"<<endl;
    QTimer *timer = new QTimer(this);
    qDebug()<<"shoudaolexiaoxi4"<<endl;
    connect(timer,SIGNAL(timeout()),this,SLOT(portInit()));
    qDebug()<<"shoudaolexiaoxi5"<<endl;
    timer->setSingleShot(true);
    qDebug()<<"shoudaolexiaoxi6"<<endl;
    timer->start(2000);
    qDebug()<<"shoudaolexiaoxi7"<<endl;

}

void portsimulation::portInit()
{
    ui->screen->clear();
    ui->title->setText("请输入发送内容：");
}

void portsimulation::on_pushButton_clicked()
{
    if(serialport == NULL){
return;
    }
    this->close();
    readTimer.stop();
    serialport->close();
    serialport = NULL;
}
void portsimulation::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);
    QPixmap p(":/images/back_all.jpg");
    paint.drawPixmap(0,0,1000,618,p);
}
