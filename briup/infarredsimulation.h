#ifndef INFARREDSIMULATION_H
#define INFARREDSIMULATION_H

#include <QWidget>
#include <QMovie>
#include <QSerialPort>
#include <QTimer>
#include <QPixmap>
#include <QPaintEvent>

namespace Ui {
class infarredsimulation;
}

class infarredsimulation : public QWidget
{
    Q_OBJECT

public:
    explicit infarredsimulation(QWidget *parent = 0);
    void addPeople();
    void removePeople();
    ~infarredsimulation();

protected:
    void paintEvent(QPaintEvent *e);

private slots:
    void readSlot();
    void on_closeBtn_clicked();

private:
    Ui::infarredsimulation *ui;
    QMovie    *movie;
    unsigned char     order;
    QTimer        readTimer;
    QSerialPort* serialport;
    QPixmap          *people;
    bool          isPortOpen;

};

#endif // INFARREDSIMULATION_H
