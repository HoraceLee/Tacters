#ifndef BUZZERSIMULATOR_H
#define BUZZERSIMULATOR_H

#include <QWidget>
#include <QVBoxLayout>
#include <pianowidget.h>
#include <musicwidget.h>
#include <qstackedlayout.h>
#include <QPaintEvent>

namespace Ui {
class BuzzerSimulator;
}

class BuzzerSimulator : public QWidget
{
    Q_OBJECT

public:
    explicit BuzzerSimulator(QWidget *parent = 0);
    ~BuzzerSimulator();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pianoBtn_clicked();

    void on_musicBtn_clicked();

    void on_closeBtn_clicked();

private:
    Ui::BuzzerSimulator *ui;
    musicwidget *musicWidget;
    pianowidget *pianoWidget;
     QStackedLayout *layout;
};

#endif // BUZZERSIMULATOR_H
