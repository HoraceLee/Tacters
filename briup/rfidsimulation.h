#ifndef RFIDSIMULATION_H
#define RFIDSIMULATION_H

#include <QWidget>
#include <QPalette>
#include <QSerialPort>
#include <QTimer>

namespace Ui {
class RFIDsimulation;
}

class RFIDsimulation : public QWidget
{
    Q_OBJECT

public:
    explicit RFIDsimulation(QWidget *parent = 0);
    ~RFIDsimulation();
private slots:
    void readSlot();


    void on_closeBtn_clicked();

private:
    Ui::RFIDsimulation    *ui;
    QSerialPort*   serialport;
    QTimer          readTimer;
    char*               order;
    bool           isPortOpen;

};

#endif // RFIDSIMULATION_H
