#ifndef LIGHTDEMONSTRATE_H
#define LIGHTDEMONSTRATE_H

#include <QWidget>
#include <QSerialPort>
#include <QTimer>

namespace Ui {
class lightDemonstrate;
}

class lightDemonstrate : public QWidget
{
    Q_OBJECT

public:
    explicit lightDemonstrate(QWidget *parent = 0);
    ~lightDemonstrate();
private slots:
    void stopMovie();
    void readSlot();

    void on_pushButton_clicked();

private:
    Ui::lightDemonstrate  *ui;
    QSerialPort*   serialport;
    QTimer          readTimer;
    unsigned char       order;
    bool           isPortOpen;
};

#endif // LIGHTDEMONSTRATE_H
