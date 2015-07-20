#ifndef SHAKESIMULATOR_H
#define SHAKESIMULATOR_H

#include <QWidget>
#include <Qtimer>
#include <QPoint>
#include <QSerialPort>
#include <QTimer>
//抖动的次数（移动窗口多少次）
enum {MaxLimitTimes = 30};
//抖动的幅度（每次抖动改变的窗口位置大小）
enum {MaxLimitSpace = 4};
namespace Ui {
class ShakeSimulator;
}

class ShakeSimulator : public QWidget
{
    Q_OBJECT

public:
    explicit ShakeSimulator(QWidget *parent = 0);
    ~ShakeSimulator();

private slots:

    void timerOut();
    void readSlot();

    void on_pushButton_clicked();

private:
    Ui::ShakeSimulator *ui;
    QTimer* m_timer;
    int m_nPosition;
    QPoint m_curPos;
    QTimer readTimer;
    QSerialPort *serialport;
    bool  isPortOpen;
    unsigned char order;
};

#endif // SHAKESIMULATOR_H
