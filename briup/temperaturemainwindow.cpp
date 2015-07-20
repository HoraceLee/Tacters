/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011, 2012, 2013, 2014 Emanuel Eichhammer               **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.qcustomplot.com/                          **
**             Date: 27.12.14                                             **
**          Version: 1.3.0                                                **
****************************************************************************/

#include "temperaturemainwindow.h"
#include "ui_temperaturemainwindow.h"
#include "fileutils.h"
#include <QDateTime>
#include "histroyfiledialog.h"
#include <QList>
#include <QVector>
#include <QSerialPortInfo>
#include <QTimer>
#include <QBitmap>
class FileUtils;

int TemperatureMainWindow::index = 0;
qreal TemperatureMainWindow::temperature = 0;

QVector<double> TemperatureMainWindow::q(500);
QVector<double> TemperatureMainWindow::p(500);

QString TemperatureMainWindow::hisFilePath = QString();

TemperatureMainWindow::TemperatureMainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::TemperatureMainWindow)
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

    // QLcdNumber初始化
    ui->lcdNumber->setFrameShape(QFrame::NoFrame);
    ui->lcdNumber_2->setFrameShape(QFrame::NoFrame);
    ui->lcdNumber_2->display(tr("C"));
    ui->lcdNumber_3->display("");

    // addTempDataAndShow()时，触发paintEvent()
//    connect(this,SIGNAL(addTempDataAndShow()),this,SLOT(paintEvent()));

    // 测试数据
//    TemperatureMainWindow::addTempDataAndShow(0,18.9);
//    TemperatureMainWindow::addTempDataAndShow(1,8.9);
//    TemperatureMainWindow::addTempDataAndShow(2,38.9);
//    TemperatureMainWindow::addTempDataAndShow(3,2.3);
//    TemperatureMainWindow::addTempDataAndShow(4,23);
//    TemperatureMainWindow::addTempDataAndShow(5,45);
//    TemperatureMainWindow::addTempDataAndShow(6,15);
//    TemperatureMainWindow::addTempDataAndShow(7,28.3);
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
    TemperatureMainWindow::addTempDataAndShow(1,38);
}

TemperatureMainWindow::~TemperatureMainWindow()
{
    delete ui;
}
void TemperatureMainWindow::readSlot(){
    QByteArray data;
    data=this->serialport->readAll();//接受数据
    if(data.isEmpty())
    {
       return;
    }
    order[1]=(char)data.at(1);//整数
    order[2]=(char)data.at(2);//小数
    double afterpoint;
    if(order[2]>=10){
      afterpoint=order[2]/100;
    }else{
      afterpoint=order[2]/10;
    }
    double tempvalue=order[1]+afterpoint;
    int minutes = FileUtils::calMinute(QDateTime::currentDateTime());
    TemperatureMainWindow::addTempDataAndShow(minutes,tempvalue);
}

void TemperatureMainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    //消除抖动
    painter.setRenderHint(QPainter::Antialiasing);
    QPixmap back;
    back.load(":/images/temp_background.jpg");
    QBrush brush = QBrush(back);
    painter.setBackground(brush);
    QPixmap tempPixmap;
    tempPixmap.load(":/images/tem.png");
    painter.drawPixmap(10,25,350,550,tempPixmap);
    TemperatureMainWindow::showTemp(temperature);
}

qreal TemperatureMainWindow::calTemperature(qreal temp){
    // 453.4(-25°c)
    // 464为水晶球原点
    qreal wenducha = qFabs( -25 - temp);
    // 4.44444为1度
    return 453.4 - wenducha * 4.4444444;
}

// 绘制温度计和数值
void TemperatureMainWindow::showTemp(qreal temp){
    QPainter painter(this);
    ui->lcdNumber->display(temp);
    QPen pen;
    pen.setWidth(8);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    QPointF p0 = QPointF(179,464);
    qreal y = calTemperature(temp);
    QPointF px = QPointF(179,y);
    painter.drawLine(px,p0);
}

//温度线条
void TemperatureMainWindow::addTempDataAndShow(qreal time, qreal temp){
    //p为横坐标，q为纵坐标
    q[index] = time;
    p[index] = temp;
    ui->plot->graph(0)->setData(q,p);
    index ++;
    temperature = temp;

    // 以下几行代码将数据添加到文件中
    QDateTime date = QDateTime::currentDateTime();
    QString dateStr = date.toString("yyyy-MM-dd");
    qDebug()<<"选中的历史数据日期："<< dateStr;
    QString fileName = "E:\\HistoryTempData\\" + dateStr +".txt";
    FileUtils::writeTempData(fileName,date,QString::number(temp));
}

void TemperatureMainWindow::showTempVector(QList<QVector<double> > data){
    if(data.length() > 1){
        QVector<double> x,y;
        x = data.at(0);
        y = data.at(1);
        ui->plot->graph(0)->setData(x,y);
    }
}

void TemperatureMainWindow::setupPlot()
{
    // The following plot setup is mostly taken from the plot demos:
    ui->plot->addGraph();
    ui->plot->graph()->setPen(QPen(Qt::red));
    ui->plot->axisRect()->setupFullAxesBox(true);
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void TemperatureMainWindow::horzScrollBarChanged(int value)
{
    if (qAbs(ui->plot->xAxis->range().center()-value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
    {
        ui->plot->xAxis->setRange(value/100.0, ui->plot->xAxis->range().size(), Qt::AlignCenter);
        ui->plot->replot();
    }
}

void TemperatureMainWindow::vertScrollBarChanged(int value)
{
    if (qAbs(ui->plot->yAxis->range().center()+value/100.0) > 0.01) // if user is dragging plot, we don't want to replot twice
    {
        ui->plot->yAxis->setRange(-value/100.0, ui->plot->yAxis->range().size(), Qt::AlignCenter);
        ui->plot->replot();
    }
}

void TemperatureMainWindow::xAxisChanged(QCPRange range)
{
    ui->horizontalScrollBar->setValue(qRound(range.center()*100.0)); // adjust position of scroll bar slider
    ui->horizontalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

void TemperatureMainWindow::yAxisChanged(QCPRange range)
{
    ui->verticalScrollBar->setValue(qRound(-range.center()*100.0)); // adjust position of scroll bar slider
    ui->verticalScrollBar->setPageStep(qRound(range.size()*100.0)); // adjust size of scroll bar slider
}

void TemperatureMainWindow::on_saveFile_triggered()
{
    QDateTime date = QDateTime::currentDateTime();
    QString dateStr = date.toString("yyyy-MM-dd");
    QString fileName = "E:\\HistoryTempData\\" + dateStr +".txt";
    FileUtils::writeTempData(fileName,date,QString::number(temperature));
}

void TemperatureMainWindow::on_openFile_triggered()
{
    QDateTime date = QDateTime::currentDateTime();
    QString dateStr = date.toString("yyyy-MM-dd");
    QString fileName = "E:\\HistoryTempData\\" + dateStr +".txt";
    FileUtils::openFile(fileName);
}

// show History File
void TemperatureMainWindow::on_historyFile_triggered()
{
    FileUtils::DIALOG_MODE = 0x01;
    HistroyFileDialog *his = new HistroyFileDialog;
    his->show();
}

// show His
void TemperatureMainWindow::on_showInPlot_triggered()
{
    if(TemperatureMainWindow::hisFilePath != NULL){
        QList<QVector<double> > tempData = FileUtils::readTempData(TemperatureMainWindow::hisFilePath);
        qDebug()<<"tempData.first().length()"<<tempData.first().length();
        TemperatureMainWindow::showTempVector(tempData);
    }
    qDebug()<<"TemperatureMainWindow::hisFilePath:::::"<<TemperatureMainWindow::hisFilePath;
}

void TemperatureMainWindow::on_pushButton_clicked()
{
    this->close();
    this->serialport->close();
}
