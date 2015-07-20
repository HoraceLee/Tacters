#include "ledsimulation.h"
#include "ui_ledsimulation.h"
#include <QPainter>
#include <QMouseEvent>
#include <qserialportinfo.h>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QBitmap>
#include <QtCore/qmath.h>

int state[8] = {0,0,0,0,0,0,0,0};
bool twinkleFlag = false;
int tempp=0;

unsigned char Test[3]={0,0,0};

ledsimulation::ledsimulation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ledsimulation)
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
        readTimer.start(200);//每隔2ms
        waitTimer.start(3000);//每3s
    }
    connect(&readTimer,SIGNAL(timeout()),this,SLOT(readSlot()));
    connect(&waitTimer,SIGNAL(timeout()),this,SLOT(judgeSlot()));
}


ledsimulation::~ledsimulation()
{
    delete ui;

}
void ledsimulation::readSlot(){
    QByteArray data;
    data=this->serialport->readAll();
    if(!data.isEmpty()){
        for(int i = 0;i<data.length();i++){
            Test[i]=(unsigned char)data.at(i);
        }
        order=(unsigned char)data.at(1);
    }
    QPixmap LEDON(":/images/LEDon.png");
    QPixmap LEDOFF(":/images/LEDoff.png");
    if(data.length()!=2){
        for(int i=7;i>=0;i--){
            if(order-qPow(2,i)>=0){
                order=order-qPow(2,i);
                state[7-i]=1;
            }else{
                state[7-i]=0;
            }
        }
        if(state[0]==1){
            ui->label->setPixmap(LEDON);
        }else{
            ui->label->setPixmap(LEDOFF);
        }
        if(state[1]==1){
            ui->label_2->setPixmap(LEDON);
        }else{
            ui->label_2->setPixmap(LEDOFF);
        }
        if(state[2]==1){
            ui->label_3->setPixmap(LEDON);
        }else{
            ui->label_3->setPixmap(LEDOFF);
        }
        if(state[3]==1){
            ui->label_4->setPixmap(LEDON);
        }else{
            ui->label_4->setPixmap(LEDOFF);
        }
        if(state[4]==1){
            ui->label_5->setPixmap(LEDON);
        }else{
            ui->label_5->setPixmap(LEDOFF);
        }
        if(state[5]==1){
            ui->label_6->setPixmap(LEDON);
        }else{
            ui->label_6->setPixmap(LEDOFF);
        }
        if(state[6]==1){
            ui->label_7->setPixmap(LEDON);
        }else{
            ui->label_7->setPixmap(LEDOFF);
        }
        if(state[7]==1){
            ui->label_8->setPixmap(LEDON);
        }else{
            ui->label_8->setPixmap(LEDOFF);
        }
    }else {
      ui->label->setPixmap(LEDOFF);
      ui->label_2->setPixmap(LEDOFF);
      ui->label_3->setPixmap(LEDOFF);
      ui->label_4->setPixmap(LEDOFF);
      ui->label_5->setPixmap(LEDOFF);
      ui->label_6->setPixmap(LEDOFF);
      ui->label_7->setPixmap(LEDOFF);
      ui->label_8->setPixmap(LEDOFF);
    }
}
void ledsimulation::judgeSlot(){

}

void ledsimulation::mousePressEvent(QMouseEvent *e){
    int led1x=ui->label->x();
    int led1y=ui->label->y();
    int led1yy=ui->label->height()+led1y;
    int led1xx=ui->label->width()+led1x;
    //LED1 label 事件

    int led2x=ui->label_2->x();
    int led2y=ui->label_2->y();
    int led2yy=ui->label_2->height()+led2y;
    int led2xx=ui->label_2->width()+led2x;
    //LED2

    int led3x=ui->label_3->x();
    int led3y=ui->label_3->y();
    int led3yy=ui->label_3->height()+led3y;
    int led3xx=ui->label_3->width()+led3x;
    //LED3

    int led4x=ui->label_4->x();
    int led4y=ui->label_4->y();
    int led4yy=ui->label_4->height()+led4y;
    int led4xx=ui->label_4->width()+led4x;
    //LED4

    int led5x=ui->label_5->x();
    int led5y=ui->label_5->y();
    int led5yy=ui->label_5->height()+led5y;
    int led5xx=ui->label_5->width()+led5x;
    //LED5

    int led6x=ui->label_6->x();
    int led6y=ui->label_6->y();
    int led6yy=ui->label_6->height()+led6y;
    int led6xx=ui->label_6->width()+led6x;
    //LED6

    int led7x=ui->label_7->x();
    int led7y=ui->label_7->y();
    int led7yy=ui->label_7->height()+led7y;
    int led7xx=ui->label_7->width()+led7x;
    //LED7

    int led8x=ui->label_8->x();
    int led8y=ui->label_8->y();
    int led8yy=ui->label_8->height()+led8y;
    int led8xx=ui->label_8->width()+led8x;
    //LED8

    QPixmap LEDON(":/images/LEDon.png");
    QPixmap LEDOFF(":/images/LEDoff.png");

    if(e->button()==Qt::LeftButton && e->x()>led1x && e->x()<led1xx && e->y()>led1y && e->y()<led1yy)
    {
        // QMessageBox::information(this,"nimei","haiyounimeimei",QMessageBox::Ok);
        QString str;
        unsigned char Order[32] = {0X01, 0X30, 0XFF};
        for(int i = 0; i < str.length(); i++){
            Order[i+9] = *qPrintable(str.mid(i,1));
        }
        for(int i=0;i<32;i++){
            //Text[i]=Order[i];
        }
        Order[3] = str.length();
        serialport->write((char*)Order);
    }
    else if(e->button()==Qt::LeftButton && e->x()>led2x &&e->x()<led2xx &&e->y()>led2y&&e->y()<led2yy)
    {
        QString str;
        unsigned char Order[64] = {0X01, 0X31, 0XFF};
        for(int i = 0; i < str.length(); i++){
            Order[i+9] = *qPrintable(str.mid(i,1));
        }
        Order[3] = str.length();
        serialport->write((char*)Order);
    }
    else if(e->button()==Qt::LeftButton && e->x()>led3x &&e->x()<led3xx &&e->y()>led3y&&e->y()<led3yy)
    {
        QString str;
        unsigned char Order[64] = {0X01, 0X32, 0XFF};
        for(int i = 0; i < str.length(); i++){
            Order[i+9] = *qPrintable(str.mid(i,1));
        }
        Order[3] = str.length();
        serialport->write((char*)Order);
    }
    else if(e->button()==Qt::LeftButton && e->x()>led4x &&e->x()<led4xx &&e->y()>led4y&&e->y()<led4yy)
    {
        QString str;
        unsigned char Order[64] = {0X01, 0X33, 0XFF};
        for(int i = 0; i < str.length(); i++){
            Order[i+9] = *qPrintable(str.mid(i,1));
        }
        Order[3] = str.length();
        serialport->write((char*)Order);
    }
    else if(e->button()==Qt::LeftButton && e->x()>led5x &&e->x()<led5xx &&e->y()>led5y&&e->y()<led5yy)
    {
        QString str;
        unsigned char Order[64] = {0X01, 0X34, 0XFF};
        for(int i = 0; i < str.length(); i++){
            Order[i+9] = *qPrintable(str.mid(i,1));
        }
        Order[3] = str.length();
        serialport->write((char*)Order);
    }
    else if(e->button()==Qt::LeftButton && e->x()>led6x &&e->x()<led6xx &&e->y()>led6y&&e->y()<led6yy)
    {
        QString str;
        unsigned char Order[64] = {0X01, 0X35, 0XFF};
        for(int i = 0; i < str.length(); i++){
            Order[i+9] = *qPrintable(str.mid(i,1));
        }
        Order[3] = str.length();
        serialport->write((char*)Order);
    }
    else if(e->button()==Qt::LeftButton && e->x()>led7x &&e->x()<led7xx &&e->y()>led7y&&e->y()<led7yy)
    {
        QString str;
        unsigned char Order[64] = {0X01, 0X36, 0XFF};
        for(int i = 0; i < str.length(); i++){
            Order[i+9] = *qPrintable(str.mid(i,1));
        }
        Order[3] = str.length();
        serialport->write((char*)Order);
    }
    else if(e->button()==Qt::LeftButton && e->x()>led8x &&e->x()<led8xx &&e->y()>led8y&&e->y()<led8yy)
    {
        QString str;
        unsigned char Order[64] = {0X01, 0X37, 0XFF};
        for(int i = 0; i < str.length(); i++){
            Order[i+9] = *qPrintable(str.mid(i,1));
        }
        Order[3] = str.length();
        serialport->write((char*)Order);
    }
}

void ledsimulation::on_twinkleStrBtn_clicked()
{
    QString str;
    unsigned char Order[64] = {0X01, 0X11, 0XFF};
    for(int i = 0; i < str.length(); i++){
        Order[i+9] = *qPrintable(str.mid(i,1));
    }
    Order[3] = str.length();
    serialport->write((char*)Order);
}


void ledsimulation::on_twinkleStpBtn_clicked()
{
    QString str;
    unsigned char Order[64] = {0X01, 0X12, 0XFF};
    for(int i = 0; i < str.length(); i++){
        Order[i+9] = *qPrintable(str.mid(i,1));
    }
    Order[3] = str.length();
    serialport->write((char*)Order);
}


void ledsimulation::on_pushButton_3_clicked()
{
    QString str;
    unsigned char Order[64] = {0X01, 0X21, 0XFF};
    for(int i = 0; i < str.length(); i++){
        Order[i+9] = *qPrintable(str.mid(i,1));
    }
    Order[3] = str.length();
    serialport->write((char*)Order);
}

void ledsimulation::on_pushButton_4_clicked()
{
    QString str;
    unsigned char Order[64] = {0X01, 0X22, 0XFF};
    for(int i = 0; i < str.length(); i++){
        Order[i+9] = *qPrintable(str.mid(i,1));
    }
    Order[3] = str.length();
    serialport->write((char*)Order);
}

void ledsimulation::on_closeBtn_clicked()
{
    this->close();
}
