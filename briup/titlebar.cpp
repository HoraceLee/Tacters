//#include <QWidget>
//#include <QLineEdit>
//#include <QLabel>
//#include <QPushButton>

//#include<QPixmap>
//#include <QHBoxLayout>
//#include <QVBoxLayout>
//#include<QToolBar>
//#include"titlebar.h"

//titlebar::titlebar(QWidget *parent):QWidget(parent){
//    // 不继承父组件的背景色
//           setAutoFillBackground(true);
//           // 使用 Highlight 作为背景色
//           setBackgroundRole(QPalette::Highlight);

//           minimize = new QToolButton(this);
//           maximize = new QToolButton(this);
//           close= new QToolButton(this);

//           // 设置按钮图像的样式
//           QPixmap pix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
//           close->setIcon(pix);

//           maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
//           maximize->setIcon(maxPix);

//           pix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
//           minimize->setIcon(pix);

//           restorePix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);

//           minimize->setMinimumHeight(20);
//           close->setMinimumHeight(20);
//           maximize->setMinimumHeight(20);

//           QLabel *label = new QLabel(this);
//           label->setText("Window Title");
//           parent->setWindowTitle("Window Title");

//           QHBoxLayout *hbox = new QHBoxLayout(this);

//           hbox->addWidget(label);
//           hbox->addWidget(minimize);
//           hbox->addWidget(maximize);
//           hbox->addWidget(close);

//           hbox->insertStretch(1, 500);
//           hbox->setSpacing(0);
//           setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

//           maxNormal = false;

//           connect(close, SIGNAL( clicked() ), parent, SLOT(close() ) );
//           connect(minimize, SIGNAL( clicked() ), this, SLOT(showSmall() ) );
//           connect(maximize, SIGNAL( clicked() ), this, SLOT(showMaxRestore() ) );


//}
//void titlebar::showSmall()
//    {
//        parentWidget()->showMinimized();
//    }

//void titlebar::showMaxRestore()
//    {
//        if (maxNormal) {
//            parentWidget()->showNormal();
//            maxNormal = !maxNormal;
//            maximize->setIcon(maxPix);
//        } else {
//            parentWidget()->showMaximized();
//            maxNormal = !maxNormal;
//            maximize->setIcon(restorePix);
//        }
//    }

////void TitleBar::mousePressEvent(QMouseEvent *e)
////    {
////        startPos = e->globalPos();
////        clickPos = mapToParent(e->pos());
////    }
////void TitleBar::mouseMoveEvent(QMouseEvent *e)
////    {
////        if (maxNormal)
////            return;
////        parentWidget()->move(e->globalPos() - clickPos);
////    }

