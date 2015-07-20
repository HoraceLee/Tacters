#ifndef GRAPWIDGET_H
#define GRAPWIDGET_H

#include <QWidget>
#include <QGraphicsView>

namespace Ui {
class grapWidget;
}

class grapWidget : public QGraphicsView
{
    Q_OBJECT

public:
    explicit grapWidget(QWidget *parent = 0);
   // ~grapWidget();

protected:
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
#endif
    void scaleView(qreal scaleFactor);
private slots:
    void on_closeBtn_clicked();

private:
    Ui::grapWidget *ui;

};

#endif // GRAPWIDGET_H
