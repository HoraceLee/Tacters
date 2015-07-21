#ifndef PIANOWIDGET_H
#define PIANOWIDGET_H

#include <QWidget>
#include <QtSerialPort>
namespace Ui {
class pianowidget;
}

class pianowidget : public QWidget
{
    Q_OBJECT

public:
    explicit pianowidget(QWidget *parent = 0);
    ~pianowidget();
     void closeport();
     void open();

private slots:
    void on_pianolabel1_LabelClicked();

    void on_pianolabel1_LabelRelease();

    void on_pianolabel2_LabelClicked();

    void on_pianolabel2_LabelRelease();

    void on_pianolabel3_LabelClicked();

    void on_pianolabel3_LabelRelease();

    void on_pianolabel4_LabelClicked();

    void on_pianolabel4_LabelRelease();

    void on_pianolabel5_LabelClicked();

    void on_pianolabel5_LabelRelease();

    void on_pianolabel6_LabelClicked();

    void on_pianolabel6_LabelRelease();

    void on_pianolabel7_LabelClicked();

    void on_pianolabel7_LabelRelease();

private:
    Ui::pianowidget *ui;
    QSerialPort*    serialport;
    bool            isPortOpen;
};

#endif // PIANOWIDGET_H
