#ifndef MUSICWIDGET_H
#define MUSICWIDGET_H

#include <QWidget>
#include <QSerialPort>

namespace Ui {
class musicwidget;
}

class musicwidget : public QWidget
{
    Q_OBJECT

public:
    explicit musicwidget(QWidget *parent = 0);
    ~musicwidget();
    void closeport();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_continueBtn_clicked();

    void on_timeoutBtn_clicked();

    void on_stopBtn_clicked();

    void on_yesButton_clicked();

private:
    Ui::musicwidget *ui;
    QSerialPort*   serialport;
    bool           isPortOpen;
};

#endif // MUSICWIDGET_H
