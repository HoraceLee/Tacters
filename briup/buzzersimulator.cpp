#include "buzzersimulator.h"
#include "ui_buzzersimulator.h"
#include <QBitmap>
#include <QPainter>
#include <QPaintEvent>

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
    qDebug()<<"on_pianoBtn_clicked()"<<endl;
    layout->setCurrentIndex(0);
    if(musicWidget == NULL){
        qDebug()<<"musicWidget == NULL"<<endl;
    }
    qDebug()<<"on_pianoBtn_clicked()完了"<<endl;
    musicWidget->closeport();//关闭串口
    qDebug()<<"musicWidget->closeport();//关闭串口"<<endl;
    pianoWidget->open();
}

void BuzzerSimulator::on_musicBtn_clicked()
{
    qDebug()<<"on_musicBtn_clicked()"<<endl;
    layout->setCurrentIndex(1);
    pianoWidget->closeport();//关闭串口
    qDebug()<<"pianoWidget->closeport();//关闭串口"<<endl;
    musicWidget->open();
}

void BuzzerSimulator::on_closeBtn_clicked()
{
    this->close();
    musicWidget->closeport();
    pianoWidget->closeport();
}

void BuzzerSimulator::paintEvent(QPaintEvent *event){
    QPainter pa(this);
    QPixmap p(":/images/back_all.jpg");
    pa.drawPixmap(0,0,1000,618,p);
}
