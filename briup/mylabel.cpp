#include<mylabel.h>
#include<QMouseEvent>
#include<qdebug.h>
#include<qwidget.h>

MyLabel::MyLabel( QWidget *parent /*= 0*/ ):
    QLabel(parent)
{

}

MyLabel::~MyLabel()
{
    delete timer;
}

void MyLabel::mousePressEvent( QMouseEvent *event )
{

    emit LabelClicked();
}

void MyLabel::mouseReleaseEvent( QMouseEvent *event )
{
     emit LabelRelease();
}


