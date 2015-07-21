#ifndef EXPCODE_H
#define EXPCODE_H

#include <QWidget>

namespace Ui {
class expCode;
}

class expCode : public QWidget
{
    Q_OBJECT

public:
    explicit expCode(int expCodeNum = 0,QWidget *parent = 0);
    ~expCode();

private slots:
    void on_ok_Btn_clicked();

    void on_closeBtn_clicked();

private:
    Ui::expCode *ui;
};

#endif // EXPCODE_H
