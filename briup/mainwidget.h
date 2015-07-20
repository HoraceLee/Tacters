#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include"widget.h"
//#include"demo1.h"

namespace Ui {
class mainWidget;
}

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit mainWidget(QWidget *parent = 0);
    ~mainWidget();
protected:
     void paintEvent(QPaintEvent  *e);

private slots:
     void on_LEDBtn_clicked();

private:
    Ui::mainWidget *ui;

    Widget           *widget;
   // Demo1           *demo1;
};


#endif // MAINWIDGET_H
