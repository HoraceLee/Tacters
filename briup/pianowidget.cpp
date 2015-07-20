#include "pianowidget.h"
#include "ui_pianowidget.h"
#include <QSerialPortInfo>

pianowidget::pianowidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pianowidget)
{
    ui->setupUi(this);
    //连接设备
    this->isPortOpen=false;
    serialport=new QSerialPort;
   // serialport=new QSerialPort;
    if(isPortOpen){
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
        //连接设备
    }
}

pianowidget::~pianowidget()
{
    delete ui;
}

void pianowidget::on_pianolabel1_LabelClicked()
{
     ui->musiclabel->setPixmap(QPixmap(":/images/music.png"));
     ui->musiclabel2->setPixmap(QPixmap(":/images/music2.png"));
     ui->pianolabel1->setPixmap(QPixmap(":/images/1.png"));
     char send[4];
     send[0]=0x10;
     send[1]=0x20;
     send[2]=0x01;
     send[3]=0xff;
     serialport->write(send);
}

void pianowidget::on_pianolabel1_LabelRelease()
{
    ui->pianolabel1->setPixmap(QPixmap());
    ui->musiclabel->setPixmap(QPixmap());
    ui->musiclabel2->setPixmap(QPixmap());
}

void pianowidget::on_pianolabel2_LabelClicked()
{
    ui->musiclabel->setPixmap(QPixmap(":/images/music.png"));
    ui->musiclabel2->setPixmap(QPixmap(":/images/music2.png"));
    ui->pianolabel2->setPixmap(QPixmap(":/images/2.png"));
    char send[4];
    send[0]=0x10;
    send[1]=0x20;
    send[2]=0x02;
    send[3]=0xff;
    serialport->write(send);
}

void pianowidget::on_pianolabel2_LabelRelease()
{
    ui->pianolabel2->setPixmap(QPixmap());
    ui->musiclabel->setPixmap(QPixmap());
    ui->musiclabel2->setPixmap(QPixmap());
}

void pianowidget::on_pianolabel3_LabelClicked()
{
    ui->musiclabel->setPixmap(QPixmap(":/images/music.png"));
    ui->musiclabel2->setPixmap(QPixmap(":/images/music2.png"));
    ui->pianolabel3->setPixmap(QPixmap(":/images/3.png"));
    char send[4];
    send[0]=0x10;
    send[1]=0x20;
    send[2]=0x03;
    send[3]=0xff;
    serialport->write(send);
}

void pianowidget::on_pianolabel3_LabelRelease()
{
    ui->pianolabel3->setPixmap(QPixmap());
    ui->musiclabel->setPixmap(QPixmap());
    ui->musiclabel2->setPixmap(QPixmap());
}

void pianowidget::on_pianolabel4_LabelClicked()
{
    ui->musiclabel->setPixmap(QPixmap(":/images/music.png"));
    ui->musiclabel2->setPixmap(QPixmap(":/images/music2.png"));
    ui->pianolabel4->setPixmap(QPixmap(":/images/4.png"));
    char send[4];
    send[0]=0x10;
    send[1]=0x20;
    send[2]=0x04;
    send[3]=0xff;
    serialport->write(send);
}

void pianowidget::on_pianolabel4_LabelRelease()
{
    ui->pianolabel4->setPixmap(QPixmap());
    ui->musiclabel->setPixmap(QPixmap());
    ui->musiclabel2->setPixmap(QPixmap());
}

void pianowidget::on_pianolabel5_LabelClicked()
{
    ui->musiclabel->setPixmap(QPixmap(":/images/music.png"));
    ui->musiclabel2->setPixmap(QPixmap(":/images/music2.png"));
    ui->pianolabel5->setPixmap(QPixmap(":/images/5.png"));
    char send[4];
    send[0]=0x10;
    send[1]=0x20;
    send[2]=0x05;
    send[3]=0xff;
    serialport->write(send);
}

void pianowidget::on_pianolabel5_LabelRelease()
{
    ui->pianolabel5->setPixmap(QPixmap());
    ui->musiclabel->setPixmap(QPixmap());
    ui->musiclabel2->setPixmap(QPixmap());
}

void pianowidget::on_pianolabel6_LabelClicked()
{
    ui->musiclabel->setPixmap(QPixmap(":/images/music.png"));
    ui->musiclabel2->setPixmap(QPixmap(":/images/music2.png"));
    ui->pianolabel6->setPixmap(QPixmap(":/images/6.png"));
    char send[4];
    send[0]=0x10;
    send[1]=0x20;
    send[2]=0x06;
    send[3]=0xff;
    serialport->write(send);
}

void pianowidget::on_pianolabel6_LabelRelease()
{
    ui->pianolabel6->setPixmap(QPixmap());
    ui->musiclabel->setPixmap(QPixmap());
    ui->musiclabel2->setPixmap(QPixmap());
}

void pianowidget::on_pianolabel7_LabelClicked()
{
    ui->musiclabel->setPixmap(QPixmap(":/images/music.png"));
    ui->musiclabel2->setPixmap(QPixmap(":/images/music2.png"));
    ui->pianolabel7->setPixmap(QPixmap(":/images/7.png"));
    char send[4];
    send[0]=0x10;
    send[1]=0x20;
    send[2]=0x07;
    send[3]=0xff;
    serialport->write(send);
}

void pianowidget::on_pianolabel7_LabelRelease()
{
    ui->pianolabel7->setPixmap(QPixmap());
    ui->musiclabel->setPixmap(QPixmap());
    ui->musiclabel2->setPixmap(QPixmap());
}
void pianowidget::closeport(){
    serialport->close();
}
