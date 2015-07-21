#include "buzzersimulator.h"
#include "ui_buzzersimulator.h"
#include <QBitmap>
#include <QPainter>
BuzzerSimulator::BuzzerSimulator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuzzerSimulator)
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

    pianoWidget = new pianowidget();
    musicWidget = new musicwidget();
    this->layout = new QStackedLayout();
    layout->addWidget(pianoWidget);
    layout->addWidget(musicWidget);
    ui->mainwidget->setLayout(layout);
    pianoWidget->open();
}

BuzzerSimulator::~BuzzerSimulator()
{
    delete ui;
}

void BuzzerSimulator::on_pianoBtn_clicked()
{
    layout->setCurrentIndex(0);
    musicWidget->closeport();//关闭串口
    pianoWidget->open();
}

void BuzzerSimulator::on_musicBtn_clicked()
{
    layout->setCurrentIndex(1);
     pianoWidget->closeport();//关闭串口
     qDebug()<<"--------------";
     musicWidget->open();
}

void BuzzerSimulator::on_closeBtn_clicked()
{
    this->close();
    musicWidget->closeport();
    pianoWidget->closeport();
}
