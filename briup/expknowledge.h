#ifndef EXPKNOWLEDGE_H
#define EXPKNOWLEDGE_H

#include <QWidget>

namespace Ui {
class expKnowledge;
}

class expKnowledge : public QWidget
{
    Q_OBJECT

public:
    explicit expKnowledge(int expKnowNum = 0,QWidget *parent = 0);
    ~expKnowledge();

private slots:
    void on_ok_Btn_clicked();

    void on_closeBtn_clicked();

private:
    Ui::expKnowledge *ui;
};

#endif // EXPKNOWLEDGE_H
