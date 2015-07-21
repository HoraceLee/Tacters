#ifndef EXPPRINCIPLE_H
#define EXPPRINCIPLE_H

#include <QWidget>

namespace Ui {
class expPrinciple;
}

class expPrinciple : public QWidget
{
    Q_OBJECT

public:
    expPrinciple(int expPrinNum = 0,QWidget *parent = 0);
    ~expPrinciple();

private slots:
    void on_closeBtn_clicked();

private:
    Ui::expPrinciple *ui;
};

#endif // EXPPRINCIPLE_H
