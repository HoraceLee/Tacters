#include "expprinciple.h"
#include "ui_expprinciple.h"

#include <QString>
#include <QFile>
#include <qtextstream.h>
#include <qtextcodec.h>
#include <QBitmap>
#include <QPainter>
#include <QPaintEvent>

expPrinciple::expPrinciple(int expPrinNum,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::expPrinciple)
{
    ui->setupUi(this);
    ui->expPrinLabel->setWordWrap(true);
    ui->expPrinLabel->setAlignment(Qt::AlignTop);

    //生成一张位图
    QBitmap objBitmap(size());
    //QPainter用于在位图上绘画
    QPainter painter(&objBitmap);
    //填充位图矩形框(用白色填充)
    painter.fillRect(rect(),Qt::white);
    painter.setBrush(QColor(0,0,0));
    //在位图上画圆角矩形(用黑色填充)
    painter.drawRoundedRect(this->rect(),10,10);
    //使用setmask过滤即可
    setMask(objBitmap);

    QFile file;
    QString string;
    QTextStream stream(&file);
    QTextCodec *code=QTextCodec::codecForName("GB2312");
    stream.setCodec(code);
    switch(expPrinNum){
    case 0:
        file.setFileName("E:/briup_text/principal/LEDPrinciple.txt");
        break;
    case 1:
        file.setFileName("E:/briup_text/principal/timerPrincipal.txt");
        break;
    case 2:
        file.setFileName("E:/briup_text/principal/temPrincipal.txt");
        break;
    case 3:
        file.setFileName("E:/briup_text/principal/temhumPrincipal.txt");
        break;
    case 4:
        file.setFileName("E:/briup_text/principal/shockPrincipal.txt");
        break;
    case 5:
        file.setFileName("E:/briup_text/principal/RFIDPrincipal.txt");
        break;
    case 6:
        file.setFileName("E:/briup_text/principal/portPrincipal.txt");
        break;
    case 7:
        file.setFileName("E:/briup_text/principal/motorPrincipal.txt");
        break;
    case 8:
        file.setFileName("E:/briup_text/principal/lightPrincipal.txt");
        break;
    case 9:
        file.setFileName("E:/briup_text/principal/LCDPrincipal.txt");
        break;
    case 10:
        file.setFileName("E:/briup_text/principal/interruptPrincipal.txt");
        break;
    case 11:
        file.setFileName("E:/briup_text/principal/infraredPrincipal.txt");
        break;
    case 12:
        file.setFileName("E:/briup_text/principal/enterPrincipal.txt");
        break;
    case 13:
        file.setFileName("E:/briup_text/principal/buzzerPrincipal.txt");
        break;
    }
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    while(!stream.atEnd()){
       //string = stream.readLine();
        if(string != ""){
            string = string + "\n" + stream.readLine();
        }else{
            string = stream.readLine();
        }

    }
    ui->expPrinLabel->setText(string);
}

expPrinciple::~expPrinciple()
{
    delete ui;
}

void expPrinciple::on_closeBtn_clicked()
{
    this->close();
}

void expPrinciple::paintEvent(QPaintEvent *event){
    QPainter pa(this);
    QPixmap p(":/images/back_book.jpg");
    pa.drawPixmap(0,0,1000,618,p);
}
