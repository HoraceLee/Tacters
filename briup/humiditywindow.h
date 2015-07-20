#ifndef HUMIDITYWINDOW_H
#define HUMIDITYWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <QVector>
#include <QSerialPort>
#include <QTimer>


namespace Ui {
class HumidityWindow;
}

class HumidityWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HumidityWindow(QWidget *parent = 0);
    ~HumidityWindow();
    void setupPlot();
    static QString fileName;

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void horzScrollBarChanged(int value);
    void vertScrollBarChanged(int value);
    void xAxisChanged(QCPRange range);
    void yAxisChanged(QCPRange range);

    void on_humi_Save_triggered();
    void on_humi_Open_triggered();
    void on_humi_SourceFile_triggered();
    void on_humi_ShowInPlot_triggered();

    void readSolt();

private:
    Ui::HumidityWindow *ui;
    void showTempAndHumiData(qreal temp,qreal humi);
    void addDataAndShow(qreal time,qreal temp,qreal humi);
    void showDataVector(QList<QVector<double> >);
    static int index;
    static QVector<double> x,y,z;
    static qreal temp;
    static qreal humi;
    QSerialPort*  serialport;
    QTimer      readTimer;
    bool        isPortOpen;
    char*            order;

signals:
    addDataAndShow();
};

#endif // HUMIDITYWINDOW_H
