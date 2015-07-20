#ifndef INTERINSTRUCTION_H
#define INTERINSTRUCTION_H

#include <QWidget>
#include <QMovie>
#include <QSerialPort>
#include <QTimer>

namespace Ui {
class interinstruction;
}

class interinstruction : public QWidget
{
    Q_OBJECT

public:
    explicit interinstruction(QWidget *parent = 0);
    ~interinstruction();
private slots:

    void readSlot();
    void on_clsoeBtn_clicked();

private:
    Ui::interinstruction         *ui;
    QMovie                    *movie;
    QSerialPort          *serialport;
    int                   isPortOpen;
    QTimer                 readTimer;
    int                        order;
};

#endif // INTERINSTRUCTION_H
