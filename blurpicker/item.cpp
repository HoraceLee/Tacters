#include "item.h"
#include "QMouseEvent"
#include "QMessageBox"
#include "QWidget"
#include "QGraphicsItem"
#include "QDebug"

//! [0]
Item::Item(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{

}
void Item::mousePressEvent (QMouseEvent *event)
{
    if(event->button () == Qt::LeftButton){
        //qDebug<<"hahahahahaahaha";
    }
}


