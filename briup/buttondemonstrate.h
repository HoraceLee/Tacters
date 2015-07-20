#ifndef BUTTONDEMONSTRATE_H
#define BUTTONDEMONSTRATE_H

#include <QWidget>
#include <QSerialPort>
#include <QTimer>

namespace Ui {
class buttonDemonstrate;
}


class buttonDemonstrate : public QWidget//,public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    explicit buttonDemonstrate(QWidget *parent = 0);
    ~buttonDemonstrate();

private slots:
    void readSlot();

    void on_pushButton_clicked();

private:
    Ui::buttonDemonstrate     *ui;
    QSerialPort*       serialport;
    QTimer              readTimer;
    bool                isPortOpen;
    unsigned char   order;
};

#endif // BUTTONDEMONSTRATE_H
