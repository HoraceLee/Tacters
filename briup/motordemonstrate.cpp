#include "motordemonstrate.h"
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

int roMode = -1,rooMode = -1;
int roDirection = -1;
int roAngle;
float i = 0;
float jiaodu = 0;//定义旋转度数

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
    connect(ui->ok_Btn,SIGNAL(readSlot()),this,SLOT(update()));

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
    order=(unsigned char)data.at(1);
    switch (order) {
    //正转开始
    case 17:
        if(roMode == 0)
            rooMode = 0;
        else if (roMode == 2)
            rooMode = 2;
        break;
    //正转停止
    case 18:
        rooMode = -1;
        break;
    //反转开始
    case 33:
        if(roMode == 1)
            rooMode = 1;
        else if (roMode == 2)
            rooMode = 2;
        break;
    //反转停止
    case 34:
        rooMode = -1;
        break;
    default:
        break;
    }
}

void MotorDemonstrate::paintEvent(QPaintEvent *e){
    QPainter paint(this);
    if(rooMode == 0 || rooMode == 1){
        if(rooMode == 0){
            i -= 0.5;
            ui->currentRoMode->setText("当前旋转方式为：正转");
        }
        else if(rooMode == 1){
            i += 0.5;
            ui->currentRoMode->setText("当前旋转方式为：反转");
        }

    }
    else if(rooMode == 2){
            jiaodu = roAngle;
            if(roDirection == 0){
                ui->currentRoMode->setText("当前旋转方式为：正转" + ui->rotationAngle->text() + "度");
                if(i>jiaodu)
                    i -= 0.5;
            }else if(roDirection == 1){
                ui->currentRoMode->setText("当前旋转方式为：反转" + ui->rotationAngle->text() + "度");
                if(i<jiaodu)
                    i += 0.5;
            }
    }
    else if(rooMode == -1){
        i = jiaodu;
        ui->currentRoMode->setText("STOP");
    }

    paint.translate(this->width()/2-200,this->height()/2+150);//设置原点
    paint.rotate(i);//坐标旋转
    paint.drawPixmap(-pixmap->height()/2,-pixmap->width()/2,*pixmap);//经分析，应使图片中心，对应原点
    jiaodu = i;

}

void MotorDemonstrate::on_ok_Btn_clicked()
{
    roMode = ui->rotationMode->currentIndex();
    roDirection = ui->rotationDirection->currentIndex();
    roAngle = ui->rotationAngle->text().toInt();
    //ui->rotationAngle->text().toUtf8().toHex();

    if(roMode == 0)
    {
        char writeorder[4];
        writeorder[0]=0x11;
        writeorder[1]=0x10;
        writeorder[2]=0x00;
        writeorder[3]=0xff;
        serialport->write(writeorder);
    }
    else if(roMode == 1){
        char writeorder2[4];
        writeorder2[0]=0x11;
        writeorder2[1]=0x20;
        writeorder2[2]=0x00;
        writeorder2[3]=0xff;
        serialport->write(writeorder2);
    }else if(roMode == 2){
          char writeorder3[6];
        if(roDirection == 0){          
            if(roAngle<16){
                writeorder3[0]=0x11;
                writeorder3[1]=0x10;
                writeorder3[2]=0x0;
                writeorder3[3]=roAngle;
                writeorder3[4]=0xff;
            }else if(roAngle<256){
                writeorder3[0]=0x11;
                writeorder3[1]=0x10;
                writeorder3[2]=roAngle/16;
                writeorder3[3]=roAngle%16;
                writeorder3[4]=0xff;
            }else {
                writeorder3[0]=0x11;
                writeorder3[1]=0x1;
                writeorder3[2]=roAngle/256;
                int roAngle2=roAngle%256;
                writeorder3[3]=roAngle2/16;
                writeorder3[4]=roAngle2%16;
                writeorder3[5]=0xff;
            }
            roAngle = -roAngle;
            serialport->write(writeorder3);
        }
        else if(roDirection == 1)
            {
            if(roAngle<16){
                writeorder3[0]=0x11;
                writeorder3[1]=0x20;
                writeorder3[2]=0x0;
                writeorder3[3]=roAngle;
                writeorder3[4]=0xff;
            }else if(roAngle<256){
                writeorder3[0]=0x11;
                writeorder3[1]=0x20;
                writeorder3[2]=roAngle/16;
                writeorder3[3]=roAngle%16;
                writeorder3[4]=0xff;
            }else {
                writeorder3[0]=0x11;
                writeorder3[1]=0x2;
                writeorder3[2]=roAngle/256;
                int roAngle2=roAngle%256;
                writeorder3[3]=roAngle2/16;
                writeorder3[4]=roAngle2%16;
                writeorder3[5]=0xff;
            }
            serialport->write(writeorder3);
           }
        }

    jiaodu += roAngle;
    roAngle = jiaodu;
}




void MotorDemonstrate::on_pushButton_clicked()
{
    this->close();
    this->serialport->close();
}