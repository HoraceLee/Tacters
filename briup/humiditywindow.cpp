#include "humiditywindow.h"
#include "ui_humiditywindow.h"
#include <QFrame>
#include "qcustomplot.h"
#include <QVector>
#include "fileutils.h"
#include "histroyfiledialog.h"
#include <QSerialPortInfo>
#include <QTimer>
#include <QBitmap>
#include <frame.h>
class FileUtils;

int HumidityWindow::index = 0;
qreal HumidityWindow::temp = 0;
qreal HumidityWindow::humi = 0;
QString HumidityWindow::fileName = QString();

QVector<double> HumidityWindow::x(500);
QVector<double> HumidityWindow::y(500);
QVector<double> HumidityWindow::z(500);

HumidityWindow::HumidityWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HumidityWindow)
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

    setupPlot();

    // configure scroll bars:
    // Since scroll bars only support integer values, we'll set a high default range of -500..500 and
    // divide scroll bar position values by 100 to provide a scroll range -5..5 in floating point
    // axis coordinates. if you want to dynamically grow the range accessible with the scroll bar,
    // just increase the the minimum/maximum values of the scroll bars as needed.
    ui->horizontalScrollBar->setRange(-500, 500);
    ui->verticalScrollBar->setRange(-500, 500);

    // create connection between axes and scroll bars:
    connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(horzScrollBarChanged(int)));
    connect(ui->verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(vertScrollBarChanged(int)));
    connect(ui->plot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(xAxisChanged(QCPRange)));
    connect(ui->plot->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(yAxisChanged(QCPRange)));

    // initialize axis range (and scroll bar positions via signals we just connected):
    ui->plot->xAxis->setRange(0, 6, Qt::AlignCenter);
    ui->plot->yAxis->setRange(0, 10, Qt::AlignCenter);

    ui->humi_lcdNumber->setFrameShape(QFrame::NoFrame);
    ui->humi_lcdNumber_3->display("");

    ui->temp_lcdNumber->setFrameShape(QFrame::NoFrame);
    ui->temp_lcdNumber_2->setFrameShape(QFrame::NoFrame);
    ui->temp_lcdNumber_2->display(tr("C"));
    ui->temp_lcdNumber_3->display("");

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
    char send[2]={0x10,0xff};
    serialport->write(send);
    readTimer.start(200);//每隔200ms

}
  connect(&readTimer,SIGNAL(timeout()),this,SLOT(readSlot()));


//    connect(this,SIGNAL(addDataAndShow()),this,SLOT(paintEvent()));

    //
    addDataAndShow(1,3,6);

}

HumidityWindow::~HumidityWindow()
{
    delete ui;
}
void HumidityWindow::readSolt()
{
    QByteArray data;
    data=this->serialport->readAll();//接受数据
    if(!isFrame(data,0x10)){
        return;
    }
    if(data.isEmpty())
    {
       return;
    }
    order[1]=(char)data.at(1);//温度
    order[2]=(char)data.at(2);//适度

    int minutes = FileUtils::calMinute(QDateTime::currentDateTime());
    HumidityWindow::addDataAndShow(minutes,order[1],order[2]);

}

void HumidityWindow::setupPlot()
{
    //graph(0)红色代表温度
    ui->plot->addGraph();
    ui->plot->graph()->setPen(QPen(Qt::red));
    //graph(1)蓝色代表湿度
    ui->plot->addGraph();
    ui->plot->graph()->setPen(QPen(Qt::blue));
    ui->plot->axisRect()->setupFullAxesBox(true);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void HumidityWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    //消除抖动
    painter.setRenderHint(QPainter::Antialiasing);
    QPixmap back;
    back.load(":/images/temp_background.jpg");
    QBrush brush = QBrush(back);
    painter.setBackground(brush);
    HumidityWindow::showTempAndHumiData(temp,humi);
}

void HumidityWindow::horzScrollBarChanged(int value)
{
    if (qAbs(ui->plot->xAxis->range().center()-value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
    {
        ui->plot->xAxis->setRange(value/100.0, ui->plot->xAxis->range().size(), Qt::AlignCenter);
        ui->plot->replot();
    }
}

void HumidityWindow::vertScrollBarChanged(int value)
{
    if (qAbs(ui->plot->yAxis->range().center()+value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
    {
        ui->plot->yAxis->setRange(-value/100.0, ui->plot->yAxis->range().size(), Qt::AlignCenter);
        ui->plot->replot();
    }
}

void HumidityWindow::xAxisChanged(QCPRange range)
{
    ui->horizontalScrollBar->setValue(qRound(range.center()*100.0)); // adjust position of scroll bar slider
    ui->horizontalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

void HumidityWindow::yAxisChanged(QCPRange range)
{
    ui->verticalScrollBar->setValue(qRound(-range.center()*100.0)); // adjust position of scroll bar slider
    ui->verticalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

void HumidityWindow::showTempAndHumiData(qreal temp, qreal humi){
    ui->temp_lcdNumber->display(temp);
    ui->humi_lcdNumber->display(humi);
}

void HumidityWindow::showDataVector(QList<QVector<double> > data){
    if(data.length() > 2){
        QVector<double> x,y,z;
        x = data.at(0);
        y = data.at(1);
        z = data.at(2);
        ui->plot->graph(0)->setData(x,y);
        ui->plot->graph(1)->setData(x,z);
    }
}

void HumidityWindow::addDataAndShow(qreal time,qreal temp,qreal humi){
    //p为横坐标，q为纵坐标
    x[index] = time;
    y[index] = temp;
    z[index] = humi;
    ui->plot->graph(0)->setData(x,y);
    ui->plot->graph(1)->setData(x,z);
    index ++;
    HumidityWindow::temp = temp;
    HumidityWindow::humi = humi;
    // 以下几行代码将数据添加到文件中
    QDateTime date = QDateTime::currentDateTime();
    QString dateStr = date.toString("yyyy-MM-dd");
    qDebug()<<"选中的历史数据日期："<< dateStr;
    QString fileName = "E:\\HistoryTempAndHumiData\\" + dateStr +".txt";
    FileUtils::writeTempAndHumiData(fileName,date,QString::number(temp),QString::number(humi));
}

void HumidityWindow::on_humi_Save_triggered()
{
    QDateTime date = QDateTime::currentDateTime();
    QString dateStr = date.toString("yyyy-MM-dd");
    QString fileName = "E:\\HistoryTempAndHumiData\\" + dateStr +".txt";
    FileUtils::writeTempAndHumiData(fileName,date,QString::number(temp),QString::number(humi));
}

void HumidityWindow::on_humi_Open_triggered()
{
    QDateTime date = QDateTime::currentDateTime();
    QString dateStr = date.toString("yyyy-MM-dd");
    QString fileName = "E:\\HistoryTempAndHumiData\\" + dateStr +".txt";
    FileUtils::openFile(fileName);
}

void HumidityWindow::on_humi_SourceFile_triggered()
{
    FileUtils::DIALOG_MODE = 0x02;
    HistroyFileDialog *his = new HistroyFileDialog;
    his->show();
}

void HumidityWindow::on_humi_ShowInPlot_triggered()
{
    if(HumidityWindow::fileName != NULL){
        QList<QVector<double> > tempData = FileUtils::readTempAndHumiData(HumidityWindow::fileName);
        qDebug()<<"tempData.first().length()"<<tempData.first().length();
        HumidityWindow::showDataVector(tempData);
    }
    qDebug()<<"HumidityWindow::fileName:::::"<<HumidityWindow::fileName;
}
