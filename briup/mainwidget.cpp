#include "mainwidget.h"
#include "ui_mainwidget.h"

#include "widget.h"
//#include "demo1.h"
#include<QPixmap>
#include<QPainter>
mainWidget::mainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWidget)
{
    ui->setupUi(this);
}

mainWidget::~mainWidget()
{
    delete ui;
}
void mainWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap(":/images/14 - 114.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}

void mainWidget::on_LEDBtn_clicked()
{
    widget=new Widget;
    widget->show();
}
