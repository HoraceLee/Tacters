#include "demo1.h"
#include "ui_demo1.h"

#include <QPixmap>
#include <QPainter>
#include <QDebug>
//#include <QTimer>

int state[8] = {0,0,0,0,0,0,0,0};
bool twinkleFlag = false;

Demo1::Demo1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Demo1)
{
    ui->setupUi(this);


       // QTimer *timer = new QTimer(this);
        //connect(timer, SIGNAL(timeout()), this, SLOT(on_twinkleStrBtn_clicked()));
        //timer->start(1000); // 每隔1s

}

Demo1::~Demo1()
{
    delete ui;
}

void Demo1::on_LED_1_clicked()
{
    QPixmap     pixmap_ON(":/images/LED_ON.png");
    QPixmap     pixmap_OFF(":/images/LED_OFF.png");

    if(state[0] == 0){
        ui->LED_1->setIcon(pixmap_ON);
        state[0] = 1;
    }else if(state[0] == 1){
        ui->LED_1->setIcon(pixmap_OFF);
        state[0] = 0;
    }
}

void Demo1::on_LED_2_clicked()
{
    QPixmap     pixmap_ON(":/images/LED_ON.png");
    QPixmap     pixmap_OFF(":/images/LED_OFF.png");

    if(state[1] == 0){
        ui->LED_2->setIcon(pixmap_ON);
        state[1] = 1;
    }else if(state[1] == 1){
        ui->LED_2->setIcon(pixmap_OFF);
        state[1] = 0;
    }
}

void Demo1::on_LED_3_clicked()
{
    QPixmap     pixmap_ON(":/images/LED_ON.png");
    QPixmap     pixmap_OFF(":/images/LED_OFF.png");

    if(state[2] == 0){
        ui->LED_3->setIcon(pixmap_ON);
        state[2] = 1;
    }else if(state[2] == 1){
        ui->LED_3->setIcon(pixmap_OFF);
        state[2] = 0;
    }
}

void Demo1::on_LED_4_clicked()
{
    QPixmap     pixmap_ON(":/images/LED_ON.png");
    QPixmap     pixmap_OFF(":/images/LED_OFF.png");

    if(state[3] == 0){
        ui->LED_4->setIcon(pixmap_ON);
        state[3] = 1;
    }else if(state[3] == 1){
        ui->LED_4->setIcon(pixmap_OFF);
        state[3] = 0;
    }
}

void Demo1::on_LED_5_clicked()
{
    QPixmap     pixmap_ON(":/images/LED_ON.png");
    QPixmap     pixmap_OFF(":/images/LED_OFF.png");

    if(state[4] == 0){
        ui->LED_5->setIcon(pixmap_ON);
        state[4] = 1;
    }else if(state[4] == 1){
        ui->LED_5->setIcon(pixmap_OFF);
        state[4] = 0;
    }
}

void Demo1::on_LED_6_clicked()
{
    QPixmap     pixmap_ON(":/images/LED_ON.png");
    QPixmap     pixmap_OFF(":/images/LED_OFF.png");

    if(state[5] == 0){
        ui->LED_6->setIcon(pixmap_ON);
        state[5] = 1;
    }else if(state[5] == 1){
        ui->LED_6->setIcon(pixmap_OFF);
        state[5] = 0;
    }
}

void Demo1::on_LED_7_clicked()
{
    QPixmap     pixmap_ON(":/images/LED_ON.png");
    QPixmap     pixmap_OFF(":/images/LED_OFF.png");

    if(state[6] == 0){
        ui->LED_7->setIcon(pixmap_ON);
        state[6] = 1;
    }else if(state[6] == 1){
        ui->LED_7->setIcon(pixmap_OFF);
        state[6] = 0;
    }
}

void Demo1::on_LED_8_clicked()
{
    QPixmap     pixmap_ON(":/images/LED_ON.png");
    QPixmap     pixmap_OFF(":/images/LED_OFF.png");

    if(state[7] == 0){
        ui->LED_8->setIcon(pixmap_ON);
        state[7] = 1;
    }else if(state[7] == 1){
        ui->LED_8->setIcon(pixmap_OFF);
        state[7] = 0;
    }
}

void Demo1::on_pushButton_clicked()
{
    close();
}

void Demo1::on_twinkleStrBtn_clicked()
{
    QPixmap     pixmap_ON(":/images/LED_ON.png");
    QPixmap     pixmap_OFF(":/images/LED_OFF.png");
    twinkleFlag = true;
    if(state[0] == 0){
        ui->LED_1->setIcon(pixmap_ON);
        ui->LED_2->setIcon(pixmap_ON);
        ui->LED_3->setIcon(pixmap_ON);
        ui->LED_4->setIcon(pixmap_ON);
        ui->LED_5->setIcon(pixmap_ON);
        ui->LED_6->setIcon(pixmap_ON);
        ui->LED_7->setIcon(pixmap_ON);
        ui->LED_8->setIcon(pixmap_ON);
        state[0] = 1;
    }
    else if(state[0] == 1){
        ui->LED_1->setIcon(pixmap_OFF);
        ui->LED_2->setIcon(pixmap_OFF);
        ui->LED_3->setIcon(pixmap_OFF);
        ui->LED_4->setIcon(pixmap_OFF);
        ui->LED_5->setIcon(pixmap_OFF);
        ui->LED_6->setIcon(pixmap_OFF);
        ui->LED_7->setIcon(pixmap_OFF);
        ui->LED_8->setIcon(pixmap_OFF);
        state[0] = 0;
    }

}

void Demo1::on_pushButton_4_clicked()
{
    twinkleFlag = false;
    state[0] = 0;
}
