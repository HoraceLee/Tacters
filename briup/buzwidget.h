#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <pianowidget.h>
#include <musicwidget.h>
#include <QVBoxLayout>
#include <qstackedlayout.h>

namespace Ui {
class Widget;
}

class BuzWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BuzWidget(QWidget *parent = 0);
    ~BuzWidget();

private slots:
    void on_pianoBtn_clicked();
    void on_musicBtn_clicked();

private:
    Ui::Widget *ui;
    musicwidget *musicWidget;
    pianowidget *pianoWidget;
    QStackedLayout  *lay;
};

#endif // WIDGET_H
