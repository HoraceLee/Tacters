#include "grapwidget.h"
#include "ui_grapwidget.h"
#include <math.h>

#include <QKeyEvent>
#include <QGraphicsView>
#include <QPixmap>
#include <QPainter>
#include <QWheelEvent>
#include <QBitmap>
#include <QIcon>

grapWidget::grapWidget(int circuitId,QWidget *parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    setScene(scene);
    scale(qreal(0.8), qreal(0.8));//比例
    setMinimumSize(1000, 618);
   // setMaximumSize(1000,618);
    QPixmap pixmap;
    setWindowTitle(tr("实验电路图"));
    switch (circuitId) {
    case 0:
        pixmap = QPixmap("E:\\circuit_images\\01.jpg");
        break;
    case 1:
        pixmap = QPixmap("E:\\circuit_images\\02.jpg");
        break;
    case 2:
        pixmap = QPixmap("E:\\circuit_images\\03.jpg");
        break;
    case 3:
        pixmap = QPixmap("E:\\circuit_images\\04.jpg");
        break;
    case 4:
        pixmap = QPixmap("E:\\circuit_images\\05.jpg");
        break;
    case 5:
        pixmap = QPixmap("E:\\circuit_images\\06.jpg");
        break;
    case 6:
        pixmap = QPixmap("E:\\circuit_images\\07.jpg");
        break;
    case 7:
        pixmap = QPixmap("E:\\circuit_images\\08.jpg");
        break;
    case 8:
        pixmap = QPixmap("E:\\circuit_images\\09.jpg");
        break;
    case 9:
        pixmap = QPixmap("E:\\circuit_images\\10.jpg");
        break;
    case 10:
        pixmap = QPixmap("E:\\circuit_images\\11.jpg");
        break;
    case 11:
        pixmap = QPixmap("E:\\circuit_images\\12.jpg");
        break;
    case 12:
        pixmap = QPixmap("E:\\circuit_images\\13.jpg");
        break;
    case 13:
        pixmap = QPixmap("E:\\circuit_images\\14.jpg");
        break;
    }
    scene->addPixmap(pixmap);

//    QPushButton *closeBtn = new QPushButton(this);
////    QPixmap pixmap2(":/images/close3.png");
//    closeBtn->setIcon(QIcon(":/images/close3.png"));
////    closeBtn->setSizeIncrement(40,40);
//    QSize iconSize(40,40);
//    closeBtn->setIconSize(iconSize);
//    closeBtn->setGeometry(closeBtn->width(),
////    closeBtn->

//    //生成一张位图
//    QBitmap objBitmap(size());
//    //QPainter用于在位图上绘画
//    QPainter painter(&objBitmap);
//    //填充位图矩形框(用白色填充)
//    painter.fillRect(rect(),Qt::white);
//    painter.setBrush(QColor(0,0,0));
//    //在位图上画圆角矩形(用黑色填充)
//    painter.drawRoundedRect(this->rect(),10,10);
//    //使用setmask过滤即可
//    setMask(objBitmap);
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
