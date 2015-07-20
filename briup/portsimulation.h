#ifndef PORTSIMULATION_H
#define PORTSIMULATION_H

#include <QWidget>
#include <QSerialPort>
#include <QTimer>

namespace Ui {
class portsimulation;
}

class portsimulation : public QWidget
{
    Q_OBJECT

public:
    explicit portsimulation(QWidget *parent = 0);
    ~portsimulation();

protected:
    void mousePressEvent(QMouseEvent *e);
private slots:
    void portDisplay(QString s);
    void portInit();
    void readSlot();

    void on_pushButton_clicked();

private:
    Ui::portsimulation *ui;
    QTimer       readTimer;
    QSerialPort* serialport;
    bool         isPortOpen;
    char*           order;

};

#endif // PORTSIMULATION_H
