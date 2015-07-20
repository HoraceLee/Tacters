#include "grapwidget.h"
#include "ui_grapwidget.h"
#include <math.h>

#include <QKeyEvent>
#include <QGraphicsView>
#include <QPixmap>
#include <QPainter>
#include <QWheelEvent>
#include <QBitmap>


grapWidget::grapWidget(QWidget *parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    setScene(scene);

    scale(qreal(0.8), qreal(0.8));//比例
    setMinimumSize(1000, 618);
   // setMaximumSize(1000,618);
    setWindowTitle(tr("实验电路图"));
    QPixmap pixmap(":/images/circuitLed.png");

    scene->addPixmap(pixmap);
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
    }
//! [0]

grapWidget::~grapWidget(){
    delete ui;
}

#ifndef QT_NO_WHEELEVENT
//! [5]
//!
//!
//滚轮事件
void grapWidget::wheelEvent(QWheelEvent *event){
    scaleView(pow((double)2, event->delta() / 240.0));
}

//! [5]
#endif
//重绘事件
void grapWidget::scaleView(qreal scaleFactor){
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 10)
        return;
    scale(scaleFactor,scaleFactor);
}


void grapWidget::on_closeBtn_clicked()
{
    this->close();
}
