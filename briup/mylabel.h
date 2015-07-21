#ifndef MYLABEL
#define MYLABEL
#include <qlabel.h>
#include <qwidget.h>
#include "qevent.h"
#include "qtimer.h"

class MyLabel : public QLabel
{
    Q_OBJECT

public:
    explicit MyLabel(QWidget *parent = 0);
        ~MyLabel();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
//    void keyPressEvent(QKeyEvent *event);
    QTimer* timer;
signals:
    void LabelClicked();
    void LabelRelease();
//    void LabelKeyPress(QKeyEvent *event);
};

#endif // MYLABEL

