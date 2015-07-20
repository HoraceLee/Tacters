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

#include "item.h"
#include "QMouseEvent"
#include "QMessageBox"
#include "QWidget"
#include "qdebug.h"
#include "QGraphicsSceneMouseEvent"
#include "QWindow"
#include "picker.h"
#include "fileutils.h"
#include "motordemonstrate.h"
#include "lightdemonstrate.h"
#include "portsimulation.h"
#include "shakesimulator.h"
#include "buzwidget.h"
#include "pianowidget.h"
#include "musicwidget.h"

class FileUtils;
//class BuzWidget;

Item::Item(int id, const QPixmap &pixmap,Picker *Picker, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent),picker(Picker)
{
    recordId = id;
    setAcceptHoverEvents(true);

    timeLine.setDuration(300);
    timeLine.setFrameRange(0, 300);
    connect(&timeLine, SIGNAL(frameChanged(int)), this, SLOT(setFrame(int)));
    connect(&timeLine, SIGNAL(finished()), this, SLOT(updateItemPosition()));
    adjust();
}
void Item::mousePressEvent (QGraphicsSceneMouseEvent *event)
{
    if(this->x() == picker->forepoint.rx() && this->y() == picker->forepoint.ry()){
        int mode = FileUtils::project_id;
        switch(mode){
        // Led
        case 0:
            switch(recordId){
            case 0:

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                leds=new ledsimulation;
                leds->show();
                break;
            }
            break;
        // Timer
        case 1:
            switch(recordId){
            case 0:

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                timers = new timersimalation;
                timers->show();
                break;
            }
            break;
        //Temperature
        case 2:
            switch(recordId){
            case 0:

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                temp = new TemperatureMainWindow;
                temp->show();
                break;
            }
            break;
        //Temperature and Humidity
        case 3:
            switch(recordId){
            case 0:

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                humi = new HumidityWindow;
                humi->show();
                break;
            }
            break;
        // Shake
        case 4:
            switch(recordId){
            case 0:

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                shake = new ShakeSimulator;
                shake->show();
                break;
            }
            break;
        // RFID
        case 5:
            switch(recordId){
            case 0:

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            }
            break;
        // Port Communication
        case 6:
            switch(recordId){
            case 0:

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                port =  new portsimulation;
                port->show();
                break;
            }
            break;
        // Motor
        case 7:
            switch(recordId){
            case 0:

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                motor = new MotorDemonstrate;
                motor->show();
                break;
            }
            break;
        // Light
        case 8:
            switch(recordId){
            case 0:

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                light = new lightDemonstrate;
                light->show();
                break;
            }
            break;
        // LCD
        case 9:
            switch(recordId){
            case 0:

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                lcds = new lcdsimlation;
                lcds->show();
                break;
            }
            break;
        // Interrupt
        case 10:
            switch(recordId){
            case 0:

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                inter=new interinstruction;
                inter->show();
                break;
            }
            break;
        // Infarred
        case 11:
            switch(recordId){
            case 0:

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                infarred=new infarredsimulation;
                infarred->show();
                break;
            }
            break;
        // Button
        case 12:
            switch(recordId){
            case 0:

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
                buttonD=new buttonDemonstrate;
                buttonD->show();
                break;
            }
            break;
        // Audio
        case 13:
            switch(recordId){
            case 0:

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:
//                buz = new BuzWidget;
//                buz.show();
                break;
            }
            break;
        // Comprehensive
        case 14:
            switch(recordId){
            case 0:

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            }
            break;
        case 15:
            switch(recordId){
            case 0:

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            }
            break;
        }
    }
}

void Item::setFrame(int frame)
{
    adjust();
    QPointF center = boundingRect().center();

    setTransform(QTransform::fromTranslate(center.x(), center.y()), true);
    setTransform(QTransform::fromScale(1 + frame / 500.0, 1 + frame / 500.0), true);
    setTransform(QTransform::fromTranslate(-center.x(), -center.y()), true);
}

void Item::adjust()
{
    QMatrix matrix;
    matrix.scale(1,1);
    setMatrix(matrix);
}

int Item::id()
{
    return recordId;
}

void Item::updateItemPosition()
{
    setZValue(z);
}


