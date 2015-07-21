#include "blurpicker.h"

#include <QtWidgets>
#include <QtCore/qmath.h>

#include "blureffect.h"
#include "imageitem.h"
#include "QTimer"
#include "widget.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

BlurPicker::BlurPicker(QWidget *parent): QGraphicsView(parent), m_index(0.0), m_animation(this, "index")
{
//    setBackgroundBrush(QPixmap(":/images/backGround2.jpg"));
    setScene(new QGraphicsScene(this));

    setupScene();
    setIndex(0);

    m_animation.setDuration(400);
    m_animation.setEasingCurve(QEasingCurve::InOutSine);

    setRenderHint(QPainter::Antialiasing, true);
    setFrameStyle(QFrame::NoFrame);

    this->foreground = 0;
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
        qreal xs = 380 * qSin(a);
        qreal ys = 230 * qCos(a);
        QPointF pos(xs, ys);
       // pos = QTransform::scale(0,0.2).map(pos);
//        pos = QTransform().rotate(-20).map(pos);
        pos = QTransform().rotate(-5).map(pos);
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
    names << ":/images/LEDLabel.png"; //id=0  led
    names << ":/images/timerLabel.png";//id=1 定时器
    names << ":/images/ThermometerLabel.png"; //id=2 温度
    names << ":/images/temAndHumLabel.png";//id=3  温湿度
    names << ":/images/shockLabel.png";//id=4  震动
    names << ":/images/rfidLabel.png";//id=5 RFID
    names << ":/images/portLabel.png";//id=6 串口通信
    names << ":/images/motorLabel.png";//id=7 步进电机
    names << ":/images/lightLabel.png";//id=8 光线
    names << ":/images/LCDLabel.png";//id=9 LCD
    names << ":/images/interruptLabel.png";//id=10 中断
    names << ":/images/infarredLabel.png";//id=11 红外线
    names << ":/images/enterLabel.png";//id=12  按键
    names << ":/images/audioLabel.png";//id=13 蜂鸣器
    names << ":/images/compLabel.png";//id=14  综合

    for (int i = 0; i < names.count(); i++) {
        QPixmap pixmap(names[i]);
        //QGraphicsPixmapItem *icon = scene()->addPixmap(pixmap);
        ImageItem *icon = new ImageItem(i,QPixmap(names[i]),this);
        scene()->addItem(icon);
        // ZValue,层叠次序
        icon->setZValue(1);
        icon->setGraphicsEffect(new BlurEffect(icon));
        m_icons << icon;
    }
}

void BlurPicker::keyPressEvent(QKeyEvent *event)
{
//    int delta = 0;
//    switch (event->key())
//    {
//    case Qt::Key_Left:
//        delta = -1;
//        break;
//    case  Qt::Key_Right:
//        delta = 1;
//        break;
//    default:
//        break;
//    }
//    if (m_animation.state() == QAbstractAnimation::Stopped && delta) {
//        m_animation.setEndValue(m_index + delta);
//        m_animation.start();
//        event->accept();
//    }
}

void BlurPicker::resizeEvent(QResizeEvent * /* event */)
{
}
void BlurPicker::mousePressEvent(QMouseEvent *event)
{
//    if (event->button () == Qt::RightButton){
//        int delta = 0;
//        if(event->x() > (width() / 2))
//        {
//            delta = 1;
//        }
//        else
//        {
//            delta = -1;
//        }

//        if (m_animation.state() == QAbstractAnimation::Stopped && delta) {
//            m_animation.setEndValue(m_index + delta);
//            m_animation.start();
//            event->accept();
//        }
//    }
    if(event->button() == Qt::LeftButton){
        if(this->itemAt(event->x(),event->y())==NULL){
            return;
        }
        QPointF pos = this->itemAt(event->x() , event->y())->pos();
        for(int i=0;i<m_icons.count();i++){
            if((m_icons[i]->pos().rx()==pos.rx() )&& (m_icons[i]->pos().ry()==pos.ry())){
                if (m_animation.state() == QAbstractAnimation::Stopped) {
                    //判断正转反转
                    if((( foreground - i ) + m_icons.count()) % m_icons.count() > 7){
                        m_animation.setEndValue(m_index + (( foreground - i ) + m_icons.count()) % m_icons.count()-15);
                    }else{
                        m_animation.setEndValue(m_index + (( foreground - i ) + m_icons.count()) % m_icons.count());
                    }
                    m_animation.start();
                    event->accept();
                    foreground = i;
//                    m_icons[i]->big();
                    QPointF point(m_icons[i]->x(),m_icons[i]->y());
                    this->forepoint = point;
                }
            }
        }
    }
}

void BlurPicker::dispose(int mode){
    switch (mode) {
    case 1:
       // this->resize(100,100);
//        this->hide();
        break;
    case 2:

        break;
    default:
        break;
    }
}


