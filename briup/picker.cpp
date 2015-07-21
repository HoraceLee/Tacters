#include "picker.h"
#include <QtWidgets>
#include <QtCore/qmath.h>
#include "item.h"
#include "QTimer"
#include "QMatrix"


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
Picker::Picker(QWidget *parent): QGraphicsView(parent), m_index(0.0), m_animation(this, "index")
{
    setBackgroundBrush(QPixmap(":/images/backGround2.png"));
    setScene(new QGraphicsScene(this));

    setupScene();
    setIndex(0);

    m_animation.setDuration(400);
    m_animation.setEasingCurve(QEasingCurve::InOutSine);

    setRenderHint(QPainter::Antialiasing, true);
    setFrameStyle(QFrame::NoFrame);
    //初始化当前图标的位置
    this->foreground = 0;

}

qreal Picker::index() const
{
    return m_index;
}

void Picker::setIndex(qreal index)
{
    m_index = index;
    for (int i = 0; i < m_icons.count(); ++i) {
        Item *icon = m_icons[i];
        qreal a = ((i + m_index) * 2 * M_PI) / m_icons.count();
        qreal xs = 370 * qSin(a);
        qreal ys = 100 * qCos(a);
        QPointF pos(xs, ys);
//        pos = QTransform().scale(0.5,0.5).map(pos);
        pos = QTransform().rotate(0).map(pos);
        pos -= QPointF(40, 40);
        icon->setPos(pos);
    }
    scene()->update();
}

void Picker::setupScene()
{
    scene()->setSceneRect(-430, -200, 1000, 618);
    QStringList names;
    names << ":/images/Fcode.png";
    names << ":/images/Fcricuit.png";
    names << ":/images/FNotes.png";
    names << ":/images/Fprinciple.png";
    names << ":/images/Fsimulation.png";
    for (int i = 0; i < names.count(); i++) {
        QPixmap pixmap(names[i]);
        Item *icon = new Item(i,QPixmap(names[i]),this);
        scene()->addItem(icon);
        // ZValue,层叠次序
        icon->setZValue(1);
        icon->setGraphicsEffect(new BlurEffect(icon));
        m_icons << icon;
    }

    QMatrix matrix1;
    QMatrix matrix2;
    QMatrix matrix3;
    matrix1.scale(1.4,1.4);
    m_icons[0]->setMatrix(matrix1);
    matrix2.scale(1.0,1.0);
    m_icons[1]->setMatrix(matrix2);
    m_icons[4]->setMatrix(matrix2);
    matrix3.scale(0.6,0.6);
    m_icons[2]->setMatrix(matrix3);
    m_icons[3]->setMatrix(matrix3);
}
void Picker::resizeEvent(QResizeEvent * /* event */)
{
}
void Picker::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton){
        if(this->itemAt(event->x(),event->y())==NULL){
            return;
        }
        QPointF pos = this->itemAt(event->x() , event->y())->pos();
        for(int i=0;i<m_icons.count();i++){
            if((m_icons[i]->pos().rx()==pos.rx() )&& (m_icons[i]->pos().ry()==pos.ry())){
                if (m_animation.state() == QAbstractAnimation::Stopped) {
                    //判断正转反转
                    if((( foreground - i ) + m_icons.count()) % m_icons.count() > 2){
                        m_animation.setEndValue(m_index + (( foreground - i ) + m_icons.count()) % m_icons.count()-5);
                    }else{
                        m_animation.setEndValue(m_index + (( foreground - i ) + m_icons.count()) % m_icons.count());
                    }
                        m_animation.start();
                        event->accept();
                        foreground = i;
                        QPointF point(m_icons[i]->x (),m_icons[i]->y ());
                        this->forepoint = point;
                }
            }
        }
        QMatrix matrix1;
        QMatrix matrix2;
        QMatrix matrix3;
        if(foreground == 0){
            matrix1.scale(1.4,1.4);
            m_icons[0]->setMatrix(matrix1);
            matrix2.scale(1.0,1.0);
            m_icons[1]->setMatrix(matrix2);
            m_icons[4]->setMatrix(matrix2);
            matrix3.scale(0.6,0.6);
            m_icons[2]->setMatrix(matrix3);
            m_icons[3]->setMatrix(matrix3);
        }
        if(foreground == 1){
            matrix1.scale(1.4,1.4);
            m_icons[1]->setMatrix(matrix1);
            matrix2.scale(1.0,1.0);
            m_icons[0]->setMatrix(matrix2);
            m_icons[2]->setMatrix(matrix2);
            matrix3.scale(0.6,0.6);
            m_icons[3]->setMatrix(matrix3);
            m_icons[4]->setMatrix(matrix3);
        }
        if(foreground == 2){
            matrix1.scale(1.4,1.4);
            m_icons[2]->setMatrix(matrix1);
            matrix2.scale(1.0,1.0);
            m_icons[1]->setMatrix(matrix2);
            m_icons[3]->setMatrix(matrix2);
            matrix3.scale(0.6,0.6);
            m_icons[0]->setMatrix(matrix3);
            m_icons[4]->setMatrix(matrix3);
        }
        if(foreground == 3){
            matrix1.scale(1.4,1.4);
            m_icons[3]->setMatrix(matrix1);
            matrix2.scale(1.0,1.0);
            m_icons[2]->setMatrix(matrix2);
            m_icons[4]->setMatrix(matrix2);
            matrix3.scale(0.6,0.6);
            m_icons[0]->setMatrix(matrix3);
            m_icons[1]->setMatrix(matrix3);
        }
        if(foreground == 4){
            matrix1.scale(1.4,1.4);
            m_icons[4]->setMatrix(matrix1);
            matrix2.scale(1.0,1.0);
            m_icons[0]->setMatrix(matrix2);
            m_icons[3]->setMatrix(matrix2);
            matrix3.scale(0.6,0.6);
            m_icons[1]->setMatrix(matrix3);
            m_icons[2]->setMatrix(matrix3);
        }
    }
}

void Picker::dispose(int mode){
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


