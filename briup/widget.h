#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QPixmap>
#include "ledsimulation.h"
#include "grapwidget.h"
#include "infarredsimulation.h"
#include "interinstruction.h"
#include "lcdsimlation.h"
#include "buttondemonstrate.h"
#include "timersimalation.h"
#include "temperaturemainwindow.h"
#include "humiditywindow.h"
#include "lightdemonstrate.h"

class TemperatureMainWindow;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
     Widget(int id=0, QWidget *parent = 0);
    ~Widget();

private slots:
    void on_closeBtn_clicked();

private:
    Ui::Widget        *ui;
    QPixmap    background;
};

#endif // WIDGET_H
