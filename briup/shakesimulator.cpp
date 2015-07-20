#include "shakesimulator.h"
#include "ui_shakesimulator.h"
#include "qmovie.h"
#include <QSerialPortInfo>
#include <QTimer>
#include <QBitmap>
#include <QPainter>

ShakeSimulator::ShakeSimulator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShakeSimulator),
    m_timer(new QTimer(this)),
    m_nPosition(0),
    m_curPos(QPoint())
{
    ui->setupUi(this);

    this->setWindowTitle("ShakeSimulator");
    char *Fname[2];
    Fname[0]=(char *)":/images/shock.gif";
    QMovie *m1 =new  QMovie();
    ui->label->setMovie(m1);
    m1->setFileName(Fname[0]);
    ui->label->movie()->start();
    ui->label->movie()->stop();

   // bool b = connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
   //Q_ASSERT(b);
   bool  b = connect(m_timer,SIGNAL(timeout()),this,SLOT(timerOut()));
    Q_ASSERT(b);
    m_timer->setInterval(40);
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
        readTimer.start(200);//每隔2ms
        connect(&readTimer,SIGNAL(timeout()),this,SLOT(readSlot()));
        //连接设备
    }
}

ShakeSimulator::~ShakeSimulator()
{
    delete ui;
}
void ShakeSimulator::readSlot()
{
    QByteArray data;
    data=this->serialport->readAll();//接受数据
    if(data.isEmpty()){
       return;
    }
    order=(unsigned char)data.at(1);
    if(order==1){
        ui->label->movie()->start();
        m_nPosition = 0;
        m_curPos = this->pos();
        m_timer->start();
    }
}




void ShakeSimulator::timerOut()
{
    m_timer->stop();
        if(m_nPosition < MaxLimitTimes)
        {
            ++m_nPosition;
            switch(m_nPosition%4)
            {
            case 1:
            {
                QPoint tmpPos(m_curPos.x(),m_curPos.y()-MaxLimitSpace);
                this->move(tmpPos);
            }
                break;
            case 2:
            {
                QPoint tmpPos(m_curPos.x()-MaxLimitSpace,m_curPos.y()-MaxLimitSpace);
                this->move(tmpPos);
            }
                break;
            case 3:
            {
                QPoint tmpPos(m_curPos.x()-MaxLimitSpace,m_curPos.y());
                this->move(tmpPos);
            }
                break;
            default:
            case 0:
                this->move(m_curPos);
                break;
            }
            m_timer->start();
        }
}

void ShakeSimulator::on_pushButton_clicked()
{
    this->close();
    this->serialport->close();
}
