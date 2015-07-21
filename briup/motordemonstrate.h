#ifndef MOTORDEMONSTRATE_H
#define MOTORDEMONSTRATE_H

#include <QWidget>
#include <qtimer>
#include <QWidget>
#include <qpixmap.h>
#include <QPaintEvent>
#include <QSerialPort>
#include <QTimer>

namespace Ui {
class MotorDemonstrate;
}

class MotorDemonstrate : public QWidget
{
    Q_OBJECT

public:
    explicit MotorDemonstrate(QWidget *parent = 0);
    ~MotorDemonstrate();

private slots:
    void paintEvent(QPaintEvent *e);
    void on_ok_Btn_clicked();
    void readSlot();

    void on_pushButton_clicked();

private:
    Ui::MotorDemonstrate *ui;
    QPixmap         *pixmap;
    QMovie           *movie;
    QTimer            *time;
    QTimer        readTimer;
    unsigned char     order;
    bool         isPortOpen;
    QSerialPort* serialport;
};

#endif // MOTORDEMONSTRATE_H
