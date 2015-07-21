#include "expcode.h"
#include "ui_expcode.h"

#include <QString>
#include <QFile>
#include <qtextstream.h>
#include <qtextcodec.h>
#include <QBitmap>
#include <QPainter>

expCode::expCode(int expCodeNum,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::expCode)
{
    ui->setupUi(this);
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
    switch(expCodeNum){
    case 0:
        file.setFileName("E:/briup_text/code/LEDCode.txt");
        break;
    case 1:
        file.setFileName("E:/briup_text/code/timerCode.txt");
        break;
    case 2:
        file.setFileName("E:/briup_text/code/temCode.txt");
        break;
    case 3:
        file.setFileName("E:/briup_text/code/temhuCode.txt");
        break;
    case 4:
        file.setFileName("E:/briup_text/code/shockCode.txt");
        break;
    case 5:
        file.setFileName("E:/briup_text/code/RFIDCode.txt");
        break;
    case 6:
        file.setFileName("E:/briup_text/code/portCode.txt");
        break;
    case 7:
        file.setFileName("E:/briup_text/code/motorCode.txt");
        break;
    case 8:
        file.setFileName("E:/briup_text/code/lightCode.txt");
        break;
    case 9:
        file.setFileName("E:/briup_text/code/LCDCode.txt");
        break;
    case 10:
        file.setFileName("E:/briup_text/code/interruptCode.txt");
        break;
    case 11:
        file.setFileName("E:/briup_text/code/infarredCode.txt");
        break;
    case 12:
        file.setFileName("E:/briup_text/code/enterCode.txt");
        break;
    case 13:
        file.setFileName("E:/briup_text/code/buzzerCode.txt");
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
    ui->expCodeBrowser->setText(string);
}

expCode::~expCode()
{
    delete ui;
}

void expCode::on_closeBtn_clicked()
{
    this->close();
}
