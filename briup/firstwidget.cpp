#include "firstwidget.h"
#include "ui_firstwidget.h"

firstwidget::firstwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::firstwidget)
{
    ui->setupUi(this);
}

firstwidget::~firstwidget()
{
    delete ui;
}
