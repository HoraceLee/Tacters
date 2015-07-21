#ifndef COMPLEX_H
#define COMPLEX_H

#include <QWidget>
#include <QSerialPort>
#include <QTimer>

namespace Ui {
class Complex;
}

class Complex : public QWidget
{
    Q_OBJECT

public:
    explicit Complex(QWidget *parent = 0);
    ~Complex();


private slots:
    void stopMovie();
    void readSlot();

    void on_pushButton_2_clicked();
    void on_label_LabelClicked();

private:
    Ui::Complex *ui;

    QPixmap         *pixmap;
    QMovie           *movie;
    QTimer            *time;
    QTimer        readTimer;
    unsigned char     order;
    bool         isPortOpen;
    QSerialPort* serialport;
};

#endif // COMPLEX_H
