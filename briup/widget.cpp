
#include "ui_widget.h"
#include "widget.h"
#include <QMouseEvent>
#include <QListWidget>
#include <QPainter>
#include <QBitmap>
#include <QMessageBox>
#include "grapwidget.h"
#include "infarredsimulation.h"
#include "interinstruction.h"
#include "lcdsimlation.h"
#include "buttondemonstrate.h"
#include "timersimalation.h"
#include "temperaturemainwindow.h"
#include "humiditywindow.h"
#include "ledsimulation.h"
#include "lightdemonstrate.h"

int moduleid;

Widget::Widget(int id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    moduleid=id;
    background.load(":/images/backGround2.png");
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

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_closeBtn_clicked()
{
    this->close();
}
