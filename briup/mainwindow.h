void on_pushButton_clicked();
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include<QWidget>
#include "mainwidget.h"
#include "blurpicker.h"
//#include <QFrame>
//#include "titlebar.h"
//#include <QVBoxLayout>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    //mainWidget     *mainwidget;
//    BlurPicker     *blurpicker;
   // TitleBar      *m_pTitleBar;
//    m_pTitleBar = new TitleBar(this);
//    //创建工具栏
//    //创建状态栏
//    m_pStatuBar = new StatuBar(this);

//    //创建布局
    //QVBoxLayout    *m_pMainLayout;
//    //将部件加入到布局中
//    m_pMainLayout->addWidget(m_pTitleBar);
//    m_pMainLayout->addWidget(m_pToolBar);
//    m_pMainLayout->addWidget(m_pContentWidget);
//    m_pMainLayout->addWidget(m_pStatuBar);
//    //设置间距与边缘空白
//    m_pMainLayout->setSpacing(0);
//    m_pMainLayout->setContentsMargins(0,0,0,0);

};

#endif // MAINWINDOW_H
