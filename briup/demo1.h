#ifndef DEMO1_H
#define DEMO1_H

#include <QWidget>

namespace Ui {
class Demo1;
}

class Demo1 : public QWidget
{
    Q_OBJECT

public:
    explicit Demo1(QWidget *parent = 0);
    ~Demo1();

private slots:
    void on_LED_1_clicked();

    void on_LED_2_clicked();

    void on_LED_3_clicked();

    void on_LED_4_clicked();

    void on_LED_5_clicked();

    void on_LED_6_clicked();

    void on_LED_7_clicked();

    void on_LED_8_clicked();

    void on_pushButton_clicked();

    void on_twinkleStrBtn_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Demo1 *ui;

};


#endif // DEMO1_H
