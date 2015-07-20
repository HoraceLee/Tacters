#ifndef LABELCOTROL_H
#define LABELCOTROL_H

#include <QObject>
#include <QAnimationGroup>
#include <QGraphicsRectItem>


class labelCotrol : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit labelCotrol(QObject *parent = 0);

signals:

public slots:
};

#endif // LABELCOTROL_H
