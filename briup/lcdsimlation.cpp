#include "lcdsimlation.h"
#include "ui_lcdsimlation.h"
#include <QPainter>
#include <QPalette>
#include <QString>
#include <QDebug>
#include <QLabel>
#include <QColor>
#include <QTimer>
#include <qserialport.h>
#include <qserialportinfo.h>
#include <QBitmap>

int flag = 0;
lcdsimlation::lcdsimlation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lcdsimlation)
{
    ui->setupUi(this);
    ui->title->setStyleSheet("QLabel{color:white;size:100}");
    ui->contents->setStyleSheet("QLabel{color:white;size:100}");

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


    //连接设备
    this->isPortOpen=false;
    serialport=new QSerialPort;
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

lcdsimlation::~lcdsimlation()
{
    delete ui;
}

//从下位机接收数据
void lcdsimlation::readSlot(){
    QByteArray data;
    data=this->serialport->readAll();//接受数据
    if(!data.isEmpty()){
        ui->title->clear();
        ui->contents->setText("数据发送成功！");
        QTimer * timer = new QTimer();
        connect(timer,SIGNAL(tiemout()),this,SLOT(clrearscree()));
        timer->setSingleShot(true);
        timer->start(2000);
    }
}

void lcdsimlation::clearscreen(){
    ui->title->setText("需要发送的数据：");
    ui->contents->clear();
}

void lcdsimlation::on_key1_clicked()
{
    QString temp=ui->contents->text();
    QString s = "1";
    ui->contents->setText(temp+s);
}

void lcdsimlation::on_key2_clicked()
{
    QString temp=ui->contents->text();
    QString s = "2";
    ui->contents->setText(temp+s);
}

void lcdsimlation::on_key3_clicked()
{
    QString temp=ui->contents->text();
    QString s = "3";
    ui->contents->setText(temp+s);
}

void lcdsimlation::on_key4_clicked()
{
    QString temp=ui->contents->text();
    QString s = "4";
    ui->contents->setText(temp+s);
}

void lcdsimlation::on_key5_clicked()
{
    QString temp=ui->contents->text();
    QString s = "5";
    ui->contents->setText(temp+s);
}

void lcdsimlation::on_key6_clicked()
{
    QString temp=ui->contents->text();
    QString s = "6";
    ui->contents->setText(temp+s);
}

void lcdsimlation::on_key7_clicked()
{
    QString temp=ui->contents->text();
    QString s = "7";
    ui->contents->setText(temp+s);
}

void lcdsimlation::on_key8_clicked()
{
    QString temp=ui->contents->text();
    QString s = "8";
    ui->contents->setText(temp+s);
}

void lcdsimlation::on_key9_clicked()
{
    QString temp=ui->contents->text();
    QString s = "9";
    ui->contents->setText(temp+s);
}

void lcdsimlation::on_key0_clicked()
{
    QString temp=ui->contents->text();
    QString s = "0";
    ui->contents->setText(temp+s);
}

void lcdsimlation::on_keyq_clicked()
{
    QString temp=ui->contents->text();
    QString s = "q";
    QString S = "Q";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyw_clicked()
{
    QString temp=ui->contents->text();
    QString s = "w";
    QString S = "W";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keye_clicked()
{
    QString temp=ui->contents->text();
    QString s = "e";
    QString S = "E";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyr_clicked()
{
    QString temp=ui->contents->text();
    QString s = "r";
    QString S = "R";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyt_clicked()
{
    QString temp=ui->contents->text();
    QString s = "t";
    QString S = "T";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyy_clicked()
{
    QString  temp=ui->contents->text();
    QString s = "y";
    QString S = "Y";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyu_clicked()
{
    QString temp=ui->contents->text();
    QString s = "u";
    QString S = "U";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyi_clicked()
{
    QString temp=ui->contents->text();
    QString s = "i";
    QString S = "I";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyo_clicked()
{
    QString temp=ui->contents->text();
    QString s = "o";
    QString S = "O";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyp_clicked()
{
    QString temp=ui->contents->text();
    QString s = "p";
    QString S = "P";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keya_clicked()
{
    QString temp=ui->contents->text();
    QString s = "a";
    QString S = "A";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keys_clicked()
{
    QString temp=ui->contents->text();
    QString s = "s";
    QString S = "S";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyd_clicked()
{
    QString temp=ui->contents->text();
    QString s = "d";
    QString S = "D";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyf_clicked()
{
    QString  temp=ui->contents->text();
    QString s = "f";
    QString S = "F";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyg_clicked()
{
    QString temp=ui->contents->text();
    QString s = "g";
    QString S = "G";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyh_clicked()
{
    QString temp=ui->contents->text();
    QString s = "h";
    QString S = "H";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyj_clicked()
{
    QString temp=ui->contents->text();
    QString s = "j";
    QString S = "J";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyk_clicked()
{
    QString temp=ui->contents->text();
    QString s = "k";
    QString S = "K";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyl_clicked()
{
    QString temp=ui->contents->text();
    QString s = "l";
    QString S = "L";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyz_clicked()
{
    QString temp=ui->contents->text();
    QString s = "z";
    QString S = "Z";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyx_clicked()
{
    QString temp=ui->contents->text();
    QString s = "x";
    QString S = "X";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyc_clicked()
{
    QString temp=ui->contents->text();
    QString s = "c";
    QString S = "C";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyv_clicked()
{
    QString temp=ui->contents->text();
    QString s = "v";
    QString S = "V";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyb_clicked()
{
    QString temp=ui->contents->text();
    QString s = "b";
    QString S = "B";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keyn_clicked()
{
    QString temp=ui->contents->text();
    QString s = "n";
    QString S = "N";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_keym_clicked()
{
    QString temp=ui->contents->text();
    QString s = "m";
    QString S = "M";
    if(flag==0)
        ui->contents->setText(temp+s);
    else
        ui->contents->setText(temp+S);
}

void lcdsimlation::on_space_clicked()
{
    QString temp=ui->contents->text();
    QString s = " ";
   ui->contents->setText(temp+s);
}

void lcdsimlation::on_enter_clicked()
{
    char send[22];
    for(int k=0;k<22;k++){
        send[k]=0;
    }
    QString sendmessage=ui->contents->text();
//    qDebug()<<ui->contents->text();
   // qDebug()<<sendmessage;
    QByteArray ba = sendmessage.toLatin1();
    char *mm = ba.data();
//    qDebug()<<mm[2];
    int i=strlen(mm);
//    qDebug()<<i;
    int length;
    if(i>20)
        length=20;
    else
        length=i;
    for(int j=1;j<=length;j++)
    {
        send[j]=mm[j-1];
        //qDebug()<<send[j];
    }
     send[0]=0x13;
//     char a = 0x30;
//    qDebug()<<send[1];
//    qDebug()<<a;
    send[length+1]=0xFF;

   // qDebug()<<send[1];
    ui->title->setText("loading... ...");
//    ui->contents->clear();
    //sendmessage=null;
    //写入指令
    serialport->write(send);
}


void lcdsimlation::on_capslk_clicked()
{
    if(flag==0)
        flag=1;
    else
        flag=0;
}

void lcdsimlation::on_closeBtn_clicked()
{
    serialport->close();
    this->close();
}
