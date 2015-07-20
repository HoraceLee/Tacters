#include "histroyfiledialog.h"
#include "ui_histroyfiledialog.h"
#include <QDate>
#include <QDebug>
#include "fileutils.h"
#include <QMessageBox>
#include "humiditywindow.h"
#include "temperaturemainwindow.h"

HistroyFileDialog::HistroyFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistroyFileDialog)
{
    ui->setupUi(this);
}

HistroyFileDialog::~HistroyFileDialog()
{
    delete ui;
}

void HistroyFileDialog::on_submitBtn_clicked()
{
    QDate date = ui->calendarWidget->selectedDate();
    QString dateStr = date.toString("yyyy-MM-dd");
    qDebug()<<"选中的历史数据日期："<< dateStr;
    QString fileName;
    switch(FileUtils::DIALOG_MODE){
    case 0x01:
        fileName = "E:\\HistoryData\\" + dateStr +".txt";
        if(!FileUtils::openFile(fileName))
        {
            QMessageBox::warning(this,"文件打开错误","没有该数据文件！",QMessageBox::Yes);
        }
        else
        {
            TemperatureMainWindow::hisFilePath = fileName;
        }
        this->close();
        break;
    case 0x02:
        fileName = "E:\\HistoryAndHumiData\\" + dateStr +".txt";
        if(!FileUtils::openFile(fileName))
        {
            QMessageBox::warning(this,"文件打开错误","没有该数据文件！",QMessageBox::Yes);
        }
        else
        {
            HumidityWindow::fileName = fileName;
        }
        this->close();
        break;
    }


}

void HistroyFileDialog::on_cancelBtn_clicked()
{
    this->close();
}
