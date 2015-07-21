#ifndef EXPKNOWLEDGE_H
#define EXPKNOWLEDGE_H

#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>

namespace Ui {
class expKnowledge;
}

class expKnowledge : public QWidget
{
    Q_OBJECT

public:
    explicit expKnowledge(int expKnowNum = 0,QWidget *parent = 0);
    ~expKnowledge();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_closeBtn_clicked();

private:
    Ui::expKnowledge *ui;
    QPixmap    background;
    QPixmap *pixmap;
};

#endif // EXPKNOWLEDGE_H
