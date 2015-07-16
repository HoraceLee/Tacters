#include "blurpicker.h"

#include <QtWidgets>
#include <QtCore/qmath.h>

#include "blureffect.h"
#include "imageitem.h"
#include "item.h"
#include "QTimer"


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int foreground = 0;

BlurPicker::BlurPicker(QWidget *parent): QGraphicsView(parent), m_index(0.0), m_animation(this, "index")
{
    setBackgroundBrush(QPixmap(":/images/background.jpg"));
    setScene(new QGraphicsScene(this));

    setupScene();
    setIndex(0);

    m_animation.setDuration(400);
    m_animation.setEasingCurve(QEasingCurve::InOutSine);

    setRenderHint(QPainter::Antialiasing, true);
    setFrameStyle(QFrame::NoFrame);
}

qreal BlurPicker::index() const
{
    return m_index;
}

void BlurPicker::setIndex(qreal index)
{
    m_index = index;

    qreal baseline = 0;
    for (int i = 0; i < m_icons.count(); ++i) {
        ImageItem *icon = m_icons[i];
        qreal a = ((i + m_index) * 2 * M_PI) / m_icons.count();
        qreal xs = 340 * qSin(a);
        qreal ys = 200 * qCos(a);
        QPointF pos(xs, ys);
//        pos = QTransform::scale(0.2,0.2).map(pos);
//        pos = QTransform().rotate(-20).map(pos);
        pos = QTransform().rotate(0).map(pos);
        pos -= QPointF(40, 40);
//        pos -= QPoint(10,10);
        icon->setPos(pos);
        baseline = qMax(baseline, ys);
        static_cast<BlurEffect *>(icon->graphicsEffect())->setBaseLine(baseline);
    }

    scene()->update();
}

void BlurPicker::setupScene()
{
    QSize size = BlurPicker::size();
//    scene()->setSceneRect(-size.width()/2,-size.height()/2,size.width(),size.height());
    scene()->setSceneRect(-500, -309, 1000, 618);

    QStringList names;
    names << ":/images/accessories-calculator.png";
    names << ":/images/accessories-text-editor.png";
    names << ":/images/help-browser.png";
    names << ":/images/internet-group-chat.png";
    names << ":/images/internet-mail.png";
    names << ":/images/internet-web-browser.png";
    names << ":/images/office-calendar.png";
    names << ":/images/system-users.png";
    names << ":/images/accessories-calculator.png";
    names << ":/images/accessories-text-editor.png";
    names << ":/images/help-browser.png";
    names << ":/images/internet-group-chat.png";
    names << ":/images/internet-mail.png";
    names << ":/images/internet-web-browser.png";
    names << ":/images/office-calendar.png";
    names << ":/images/system-users.png";

    for (int i = 0; i < names.count(); i++) {
        QPixmap pixmap(names[i]);
        //QGraphicsPixmapItem *icon = scene()->addPixmap(pixmap);

        // +++
        ImageItem *icon = new ImageItem(i,QPixmap(names[i]),this);
        scene()->addItem(icon);
        // ZValue,层叠次序
        icon->setZValue(1);
        icon->setGraphicsEffect(new BlurEffect(icon));
        m_icons << icon;
    }

    // ---

//    QGraphicsPixmapItem *bg = scene()->addPixmap(QPixmap(":/images/background.jpg"));
//    bg->setZValue(0);
//    bg->setPos(-200, -150);

}

void BlurPicker::keyPressEvent(QKeyEvent *event)
{
    int delta = 0;
    switch (event->key())
    {
    case Qt::Key_Left:
        delta = -1;
        break;
    case  Qt::Key_Right:
        delta = 1;
        break;
    default:
        break;
    }
    if (m_animation.state() == QAbstractAnimation::Stopped && delta) {
        m_animation.setEndValue(m_index + delta);
        m_animation.start();
        event->accept();
    }
}

void BlurPicker::resizeEvent(QResizeEvent * /* event */)
{
}
void BlurPicker::mousePressEvent(QMouseEvent *event)
{
    if (event->button () == Qt::RightButton){

    int delta = 0;
    if(event->x() > (width() / 2))
    {
        delta = 1;
    }
    else
    {
        delta = -1;
    }

    if (m_animation.state() == QAbstractAnimation::Stopped && delta) {
        m_animation.setEndValue(m_index + delta);
        m_animation.start();
        event->accept();
    }
    }
    if(event->button() == Qt::LeftButton){
        if(this->itemAt(event->x(),event->y())==NULL){
            return;
        }
        QPointF pos = this->itemAt(event->x() , event->y())->pos();
        for(int i=0;i<m_icons.count();i++){
            if((m_icons[i]->pos().rx()==pos.rx() )&& (m_icons[i]->pos().ry()==pos.ry())){
                if (m_animation.state() == QAbstractAnimation::Stopped) {
                    m_animation.setEndValue(m_index + (( foreground - i ) + m_icons.count()) % m_icons.count());
//                                m_animation.setEndValue(m_index +i);
                    m_animation.start();
                    event->accept();
                    foreground = i;
//                    m_icons[i]->big();
                }
            }
        }
    }
}

void BlurPicker::dispose(int mode){
    switch (mode) {
    case 1:
        this->resize(100,100);
//        this->hide();
        break;
    case 2:

        break;
    default:
        break;
    }
}


