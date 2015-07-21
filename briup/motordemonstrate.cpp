
#include "ui_motordemonstrate.h"
#include <QPixmap>
#include <QMatrix>
#include <qpainter.h>
#include <qurl.h>
#include <qdir.h>
#include <qdebug.h>
#include <QString>
#include <QSerialPortInfo>
#include <QTimer>
#include <QBitmap>
#include <QDebug>
#include "motordemonstrate.h"

int roMode = -1;
int roDirection = -1;
int roAngle;
float i = 0,tempAngle = 0;//定义旋转度数

MotorDemonstrate::MotorDemonstrate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MotorDemonstrate)
{
    ui->setupUi(this);

    pixmap = new QPixmap(":/images/Turntable.png");
    QPainter paint(this);
    paint.translate(this->width()/2+100,this->height()/2+150);//设置原点

    time = new QTimer(this);
    time->start(2);

    connect(time,SIGNAL(timeout()),this,SLOT(update()));
    //*********************************************************************************
    connect(ui->ok_Btn,SIGNAL(readSlot()),this,SLOT(update()));
    //connect(time,SIGNAL(readSlot()),this,SLOT(paintEvent(QPaintEvent*)));
    //*********************************************************************************

    QString string;
    string = "   本界面为步进电机实验演示界面。\n";
    string = string + "   在演示前先选择旋转方式，有正转、反转、自定义角度旋转三种方式，";
    string = string + "选择自定义角度后需要手动输入旋转的方向和角度，规定'+'为正方向，'-'为反方向。\n";
    string = string + "   特别说明：正转为逆时针旋转，反转为顺时针旋转。";
    ui->textBrowser->setText(string);

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
        //初始化
        char send[2]={0x11,0xff};
        serialport->write(send);
        //*******************************************************************
        readTimer.start(200);//每隔200ms
    }
    connect(&readTimer,SIGNAL(timeout()),this,SLOT(readSlot()));
}

MotorDemonstrate::~MotorDemonstrate()
{
    delete ui;
}

void MotorDemonstrate::readSlot(){
    QByteArray data;
    data=this->serialport->readAll();//接受数据
    if(data.isEmpty()){
       return;
    }
    qDebug()<<data.toHex();
}

void MotorDemonstrate::paintEvent(QPaintEvent *e){
    QPainter paint(this);
    QPixmap p(":/images/back_all.jpg");
    paint.drawPixmap(0,0,1000,618,p);
    if(roMode == 0 || roMode == 1){
        if(roMode == 0){
            i -= 0.5;
            ui->currentRoMode->setText("当前旋转方式为：正转");
        }
        else if(roMode == 1){
            i += 0.5;
            ui->currentRoMode->setText("当前旋转方式为：反转");
        }
    }else if(roMode == 2){
        tempAngle = roAngle;
        if(roDirection == 0){
            ui->currentRoMode->setText("当前旋转方式为：正转" + ui->rotationAngle->text() + "度");
            if(i>tempAngle)
                i -= 0.5;
        }else if(roDirection == 1){
            ui->currentRoMode->setText("当前旋转方式为：反转" + ui->rotationAngle->text() + "度");
            if(i<tempAngle)
                i += 0.5;
        }
    }else if(roMode == -1){
        i = tempAngle;
        ui->currentRoMode->setText("STOP");
    }

    paint.translate(this->width()/2-200,this->height()/2+150);//设置原点
    paint.rotate(i);//坐标旋转
    paint.drawPixmap(-pixmap->height()/2,-pixmap->width()/2,*pixmap);//经分析，应使图片中心，对应原点
    tempAngle = i;

}

void MotorDemonstrate::on_ok_Btn_clicked()
{
    roMode = ui->rotationMode->currentIndex();
    roDirection = ui->rotationDirection->currentIndex();
    roAngle = ui->rotationAngle->text().toInt();

    if(roMode == 0)
    {
        char writeorder[3] = {0x11,0x01,0xff};
        serialport->write(writeorder);
        qDebug()<<"11111111111";
    }
    else if(roMode == 1){
        char writeorder2[] = {0x11,0x02,0xff};
        qDebug()<<"22222222222222222";
        serialport->write(writeorder2);
    }else if(roMode == 2){
          char writeorder3[4];
        if(roDirection == 0){
            if(roAngle<256){
                writeorder3[0]=0x11;
                writeorder3[1]=0x10;
                writeorder3[2]=roAngle;
                writeorder3[3]=0xff;
            }else if(roAngle<256*16){
                writeorder3[0]=0x11;
                writeorder3[1]=0x10+(roAngle/256)%16;
                writeorder3[2]=roAngle;
                writeorder3[3]=0xff;
            }else{
                return;
            }
            serialport->write(writeorder3);
        }
        else if(roDirection == 1){
            if(roAngle<256){
                writeorder3[0]=0x11;
                writeorder3[1]=0x20;
                writeorder3[2]=roAngle;
                writeorder3[3]=0xff;
            }else if(roAngle<156*16){
                writeorder3[0]=0x11;
                writeorder3[1]=0x20+(roAngle/256)%16;
                writeorder3[2]=roAngle;
                writeorder3[3]=0xff;
            }else{
                return;
            }
            qDebug()<<"44444444444444444444";
            serialport->write(writeorder3);
           }
        }
    //*********************************

    if(roDirection == 0)
        tempAngle -= roAngle;
    else if(roDirection == 1)
        tempAngle += roAngle;
    roAngle = tempAngle;
    //*********************************

}

void MotorDemonstrate::on_pushButton_clicked()
{
    if(this->serialport==NULL){
        return ;
    }
    if(!isPortOpen){
        serialport = NULL;
        return;
    }
    readTimer.stop();
    serialport->close();
    serialport == NULL;
    this->close();
}
