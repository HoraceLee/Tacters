#ifndef TIMERSIMALATION_H
#define TIMERSIMALATION_H

#include <QWidget>
#include <QSerialPort>
#include <QTimer>
#include <QPaintEvent>

namespace Ui {
class timersimalation;
}

class timersimalation : public QWidget
{
    Q_OBJECT

public:
    explicit timersimalation(QWidget *parent = 0);
    ~timersimalation();

private slots:
    void on_pushButton_clicked();
    void closel();
    void readSlot();
    void on_closeBtn_clicked();

private:
    Ui::timersimalation *ui;
    QSerialPort* serialport;
    QTimer        readTimer;
    unsigned char     order;
    bool         isPortOpen;
};

#endif // TIMERSIMALATION_H
