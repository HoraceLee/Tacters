#include "buzwidget.h"
#include "ui_buzwidget.h"
#include "pianowidget.h"
#include "musicwidget.h"
#include "QVBoxLayout"

BuzWidget::BuzWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    pianoWidget = new pianowidget();
    musicWidget = new musicwidget();
    this->lay = new QStackedLayout;
    lay->addWidget(pianoWidget);
    lay->addWidget(musicWidget);
    ui->mainwidget->setLayout(lay);
}

BuzWidget::~BuzWidget()
{
    delete ui;
}

void BuzWidget::on_pianoBtn_clicked()
{
    lay->setCurrentIndex(0);
    musicWidget->closeport();//关闭串口
}

void BuzWidget::on_musicBtn_clicked()
{
    lay->setCurrentIndex(1);
    pianoWidget->closeport();//关闭串口
}
