#include<mylabel.h>
#include<QMouseEvent>
#include<qdebug.h>
#include<qwidget.h>

MyLabel::MyLabel( QWidget *parent /*= 0*/ ):
    QLabel(parent)
{
    mouse_press = false;
    clicked_num = 0;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(SlotTimerOut()));
}

MyLabel::~MyLabel()
{
    delete timer;
}

void MyLabel::mousePressEvent( QMouseEvent *event )
{
//    if (event->button() == Qt::LeftButton)
//    {
//        mouse_press = true;
//    }
    emit LabelClicked();
}

void MyLabel::mouseReleaseEvent( QMouseEvent *event )
{
//    if(mouse_press  && this->rect().contains(event->pos()))
//    {
//        clicked_num++;
//        mouse_press = false;
//        timer->start(200);
//    }
     emit LabelRelease();
}

void MyLabel::SlotTimerOut()
{
//    if (clicked_num == 1)
//    {
//        emit LabelClicked();
//    }
//    if (clicked_num >= 2)
//    {
//        emit LabelDoubleClicked();
//    }
//    clicked_num = 0;
//    emit LabelClicked();
    timer->stop();
}

