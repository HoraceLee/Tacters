/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "imageitem.h"
#include "QMouseEvent"
#include "QMessageBox"
#include "QWidget"
#include "qdebug.h"
#include "QGraphicsSceneMouseEvent"
#include "QWindow"
#include "blurpicker.h"
ImageItem::ImageItem(int id, const QPixmap &pixmap,BlurPicker *blurPicker, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent),blur(blurPicker)
{
    recordId = id;
    setAcceptHoverEvents(true);

    timeLine.setDuration(300);
    timeLine.setFrameRange(0, 300);
    connect(&timeLine, SIGNAL(frameChanged(int)), this, SLOT(setFrame(int)));
    connect(&timeLine, SIGNAL(finished()), this, SLOT(updateItemPosition()));

//    connect(this,SIGNAL(mousePressEvent (QGraphicsSceneMouseEvent *event)), blur , SLOT(BlurPicker::dispose()));
    adjust();


}
void ImageItem::mousePressEvent (QGraphicsSceneMouseEvent *event)
{

    QWindow *widget = new QWindow;
    widget->show ();
    widget->setTitle ("abcd");
    widget->resize (400,400);
    qDebug()<<"hahahahaha";
    blur->resize(100,100);
//    blur->close();
    blur->repaint();
    blur->update();
}
void ImageItem::hoverEnterEvent(QGraphicsSceneHoverEvent * /*event*/)
{
    timeLine.setDirection(QTimeLine::Forward);

    if (z != 1.0) {
        z = 1.0;
        updateItemPosition();
    }

    if (timeLine.state() == QTimeLine::NotRunning)
        timeLine.start();
}
void ImageItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * /*event*/)
{
    timeLine.setDirection(QTimeLine::Backward);
    if (z != 0.0)
        z = 0.0;

    if (timeLine.state() == QTimeLine::NotRunning)
        timeLine.start();
}

void ImageItem::setFrame(int frame)
{
    adjust();
    QPointF center = boundingRect().center();

    setTransform(QTransform::fromTranslate(center.x(), center.y()), true);
    setTransform(QTransform::fromScale(1 + frame / 500.0, 1 + frame / 500.0), true);
    setTransform(QTransform::fromTranslate(-center.x(), -center.y()), true);
}

void ImageItem::adjust()
{
    QMatrix matrix;
//    matrix.scale(120 / boundingRect().width(), 120 / boundingRect().height());
    matrix.scale(1,1);
    setMatrix(matrix);
}

int ImageItem::id()
{
    return recordId;
}

void ImageItem::updateItemPosition()
{
    setZValue(z);
}


