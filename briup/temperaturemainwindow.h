/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011, 2012, 2013, 2014 Emanuel Eichhammer               **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.qcustomplot.com/                          **
**             Date: 27.12.14                                             **
**          Version: 1.3.0                                                **
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QPainter>
#include <QPaintEvent>
#include <QVector>
#include <QDateTime>
#include <QSerialPort>
#include <QTimer>


namespace Ui {
class TemperatureMainWindow;
}

class TemperatureMainWindow : public QMainWindow
{
  Q_OBJECT

public:
    explicit TemperatureMainWindow(QWidget *parent = 0);
    ~TemperatureMainWindow();
    void setupPlot();
    // 记录历史数据的文件名
    static QString hisFilePath;

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void horzScrollBarChanged(int value);
    void vertScrollBarChanged(int value);
    void xAxisChanged(QCPRange range);
    void yAxisChanged(QCPRange range);

    void on_saveFile_triggered();
    void on_openFile_triggered();
    void on_historyFile_triggered();
    void on_showInPlot_triggered();
    void readSlot();

//    void paintEvent(QPaintEvent *);

    void on_pushButton_clicked();

private:
    Ui::TemperatureMainWindow *ui;
    //传入温度数据，返回坐标y值
    qreal calTemperature(qreal temp);
    void showTemp(qreal temp);
    QPainter painter;
    void addTempDataAndShow(qreal time, qreal temp);
    void showTempVector(QList<QVector<double> >);
    static int index;
    static qreal temperature;
    static QVector<double> p,q;
    QSerialPort* serialport;
    QTimer   readTimer;
    bool    isPortOpen;
    char*    order;


signals:
    addTempDataAndShow();
};

#endif // MAINWINDOW_H
