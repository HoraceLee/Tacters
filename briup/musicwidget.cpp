#include "musicwidget.h"
#include "ui_musicwidget.h"
#include <QSerialPortInfo>
#include "frame.h"
#include <QDebug>

musicwidget::musicwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::musicwidget)
{
    ui->setupUi(this);
}

musicwidget::~musicwidget()
{
    delete ui;
}

void musicwidget::on_comboBox_currentIndexChanged(int index)
{

}

void musicwidget::on_continueBtn_clicked()
{
    char send[4];
    send[0]=0x10;
    send[1]=0x11;
    send[3]=0xff;
    if(ui->comboBox->currentIndex()==1){
      send[2]=0x01;
    }else{
      send[2]=0x02;
    }
    serialport->write(send);
}

void musicwidget::on_timeoutBtn_clicked()
{
    char send[4];
    send[0]=0x10;
    send[1]=0x13;
    send[3]=0xff;
    if(ui->comboBox->currentIndex()==1){
        send[2]=0x01;
    }else{
        send[2]=0x02;
    }
    serialport->write(send);
}

void musicwidget::on_stopBtn_clicked()
{

    char send[4];
    send[0]=0x10;
    send[1]=0x12;
    send[3]=0xff;
    if(ui->comboBox->currentIndex()==1){
        send[2] = 0x02;
    }else{
        send[2] = 0x01;
    }
    serialport->write(send);
}
void musicwidget::closeport(){
    qDebug()<<"void musicwidget::closeport(){"<<endl;
    if(serialport == NULL){
        qDebug()<<"serialport == NULL"<<endl;
        return;
    }
    qDebug()<<"1"<<endl;
    if(!serialport->isOpen()){
        qDebug()<<"!serialport->isOpen()"<<endl;
        serialport = NULL;
        return;
    }
    qDebug()<<"1"<<endl;
    serialport->close();
    serialport = NULL;
    qDebug()<<"2"<<endl;
}


void musicwidget::on_yesButton_clicked()
{
    char send[4];
    send[0]=0x10;
    send[1]=0x11;
    send[3]=0xff;
    if(ui->comboBox->currentIndex()==1){
        send[2]=0x01;
    }else{
        send[2]=0x02;
    }
    serialport->write(send);
}

void musicwidget::open()
{
    if(this->serialport!=NULL){
        return ;
    }
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
        char send[2]={0x10,0xff};
        serialport->write(send);
        //连接设备
    }
}
