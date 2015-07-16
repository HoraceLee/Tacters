#ifndef ITEM
#define ITEM
#include <QtCore>
#include <QMouseEvent>
#include <QtWidgets/QGraphicsItem>
class Item : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
       Item(QGraphicsItem *parent = 0);
       int id();
protected:
    void mousePressEvent (QMouseEvent *event);
};
#endif // ITEM

