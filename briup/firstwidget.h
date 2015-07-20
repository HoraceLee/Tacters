#ifndef FIRSTWIDGET_H
#define FIRSTWIDGET_H

#include <QWidget>

namespace Ui {
class firstwidget;
}

class firstwidget : public QWidget
{
    Q_OBJECT

public:
    explicit firstwidget(QWidget *parent = 0);
    ~firstwidget();

private:
    Ui::firstwidget *ui;
};

#endif // FIRSTWIDGET_H
