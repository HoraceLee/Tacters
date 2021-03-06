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

#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <QtCore>
#include <QMouseEvent>
#include <QEvent>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include "infarredsimulation.h"
#include "interinstruction.h"
#include "lcdsimlation.h"
#include "buttondemonstrate.h"
#include "timersimalation.h"
#include "temperaturemainwindow.h"
#include "humiditywindow.h"
#include "ledsimulation.h"
#include "widget.h"
#include "lightdemonstrate.h"
#include "motordemonstrate.h"
#include "portsimulation.h"
#include "shakesimulator.h"
#include "grapwidget.h"
#include "rfidsimulation.h"
#include "buzzersimulator.h"
#include "expcode.h"
#include "expprinciple.h"
#include "expknowledge.h"
#include "complex.h"

class Picker;
//class BuzWidget;

class Item : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Item(int id, const QPixmap &pixmap,Picker * Picker, QGraphicsItem *parent = 0);
    int id();
    void adjust();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private slots:
    // 放大缩小
    void setFrame(int frame);
    // setZValue
    void updateItemPosition();

private:
    QTimeLine timeLine;
    int recordId;
    double z;
    Picker *picker;
    ledsimulation   *leds;
    infarredsimulation *infarred;
    interinstruction   *inter;
    lcdsimlation       *lcds;
    buttonDemonstrate  *buttonD;
    timersimalation    *timers;
    HumidityWindow *humi;
    TemperatureMainWindow *temp;
    lightDemonstrate *light;
    MotorDemonstrate *motor;
    portsimulation *port;
    ShakeSimulator *shake;
    RFIDsimulation *rfid;
    BuzzerSimulator *buzzer;
    grapWidget *grapLed;
    expPrinciple *principle;
    expKnowledge *knowledge;
    expCode *code;
    Complex *com;
};
#endif
