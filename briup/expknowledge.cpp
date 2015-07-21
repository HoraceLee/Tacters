#include "expknowledge.h"
#include "ui_expknowledge.h"

#include <QString>
#include <QFile>
#include <qtextstream.h>
#include <qtextcodec.h>
#include <QBitmap>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>

expKnowledge::expKnowledge(int expKnowNum,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::expKnowledge)
{
    ui->setupUi(this);
    ui->expKnowLabel->setWordWrap(true);
    ui->expKnowLabel->setAlignment(Qt::AlignTop);



    //生成一张位图
    QBitmap objBitmap(size());
    //QPainter用于在位图上绘画
    QPainter painter(&objBitmap);

//    background.load(":/images/back_book.jpg");
//    pixmap = new QPixmap(":/images/back_2.jpg");
//    painter.drawPixmap(0,0,1000,618,*pixmap);

//    填充位图矩形框(用白色填充)
    painter.fillRect(rect(),Qt::white);
    painter.setBrush(QColor(0,0,0));
//    在位图上画圆角矩形(用黑色填充)
    painter.drawRoundedRect(this->rect(),10,10);
//    使用setmask过滤即可
    setMask(objBitmap);

    QFile file;
    QString string;
    QTextStream stream(&file);
    QTextCodec *code=QTextCodec::codecForName("GB2312");
    stream.setCodec(code);
    switch(expKnowNum){
    case 0:
        //E:\briup_text\knowledge
        file.setFileName("E:/briup_text/knowledge/LEDKnowledge.txt");
        break;
    case 1:
        file.setFileName("E:/briup_text/knowledge/timerKnowledge.txt");
        break;
    case 2:
        file.setFileName("E:/briup_text/knowledge/temKnowledge.txt");
        break;
    case 3:
        file.setFileName("E:/briup_text/knowledge/temhumKnowledge.txt");
        break;
    case 4:
        file.setFileName("E:/briup_text/knowledge/shockKnowledge.txt");
        break;
    case 5:
        file.setFileName("E:/briup_text/knowledge/RFIDKnowledge.txt");
        break;
    case 6:
        file.setFileName("E:/briup_text/knowledge/portKnowledge.txt");
        break;
    case 7:
        file.setFileName("E:/briup_text/knowledge/motorKnowledge.txt");
        break;
    case 8:
        file.setFileName("E:/briup_text/knowledge/lightKnowledge.txt");
        break;
    case 9:
        file.setFileName("E:/briup_text/knowledge/LCDKnowledge.txt");
        break;
    case 10:
        file.setFileName("E:/briup_text/knowledge/interruptKnowledge.txt");
        break;
    case 11:
        file.setFileName("E:/briup_text/knowledge/infraredKnowledge.txt");
        break;
    case 12:
        file.setFileName("E:/briup_text/knowledge/enterKnowledge.txt");
        break;
    case 13:
        file.setFileName("E:/briup_text/knowledge/buzzerKnoeledge.txt");
        break;
    }
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    while(!stream.atEnd()){
        if(string != ""){
            string = string + "\n" + stream.readLine();
        }else{
            string = stream.readLine();
        }

    }
    ui->expKnowLabel->setText(string);
}

expKnowledge::~expKnowledge()
{
    delete ui;

}

void expKnowledge::on_closeBtn_clicked()
{
    this->close();
}

void expKnowledge::paintEvent(QPaintEvent *event){
    QPainter pa(this);
    QPixmap p(":/images/back_book.jpg");
    pa.drawPixmap(0,0,1000,618,p);
}
