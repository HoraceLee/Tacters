#ifndef LEDSIMULATION_H
#define LEDSIMULATION_H

#include <QWidget>
#include <QSerialPort>
#include <QTimer>


namespace Ui {
class ledsimulation;
}

class ledsimulation : public QWidget
{
    Q_OBJECT

public:
    explicit ledsimulation(QWidget *parent = 0);
    ~ledsimulation();
protected:
    void mousePressEvent(QMouseEvent *e);
    //void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent* e);
private slots:
     void readSlot();
     void judgeSlot();

     void on_twinkleStrBtn_clicked();
     void on_twinkleStpBtn_clicked();
     void on_pushButton_3_clicked();
     void on_pushButton_4_clicked();

     void on_closeBtn_clicked();

private:
    Ui::ledsimulation *ui;
    QSerialPort*   serialport;
    bool           isPortOpen;
    QTimer          readTimer;
    QTimer          waitTimer;
    QString         orders;
    int            orderint;
    unsigned char order;
};

#endif // LEDSIMULATION_H
