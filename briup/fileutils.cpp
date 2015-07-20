#include "fileutils.h"
#include <QDebug>
#include <QIODevice>
#include <QDesktopServices>
#include <QUrl>
#include "temperaturemainwindow.h"
#include <QList>
#include <QVector>
#include <QDateTime>

// 历史数据选择框的模式。
// 判断是选择温度传感器或者温湿度传感器
int FileUtils::DIALOG_MODE = 0;
int FileUtils::project_id = 0;

FileUtils::FileUtils()
{

}

void FileUtils::deleteFile(QString path){
    QFile file(path);
    if(file.exists()){
        file.remove();
    }
}

void FileUtils::writeFile(QString path, QString str){
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
//        QMessageBox::warning(MainWindow,"Warnning","Can't open file!",QMessageBox::Yes);
        qDebug()<<"打开文件失败。"<<endl;
    }
    QTextStream in(&file);
    in<<str<<endl;
    file.close();
}

void FileUtils::appendFile(QString path, QString str){
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
//        QMessageBox::warning(MainWindow,"Warnning","Can't open file!",QMessageBox::Yes);
        qDebug()<<"打开文件失败。"<<endl;
    }
    QTextStream in(&file);
    in<<str<<endl;
    file.close();
}


void FileUtils::readFile(QString path){
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
//        QMessageBox::warning(this,"Warnning","打开文件失败。",QMessageBox::Yes);
        qDebug()<<"打开文件失败。"<<endl;
    }
    while(!file.atEnd()){
        QByteArray line = file.readLine();
        QString str(line);
        qDebug()<<str;
    }
    file.close();
}

bool FileUtils::openFile(QString path){
    //fileName:文件名,如C:/新建 Microsoft Word 文档.doc
    //QUrl::fromLocalFile()一定要用这个方法,因为文件名或路径中中文或空格,不然打不开文件
    //直接用QUrl(fileName)只能打开英文名称和没有空格路径的文件
    return QDesktopServices::openUrl ( QUrl::fromLocalFile(path));
}

void FileUtils::writeTempData(QString path, QDateTime time, QString data){
    QString str = time.toString("hh:mm:ss") + "\r\n" + data;
    FileUtils::appendFile(path,str);
}

void FileUtils::writeTempAndHumiData(QString path, QDateTime time, QString tempData, QString humiData){
    FileUtils::writeTempData(path,time,tempData + "\r\n" + humiData);
}

// 打开温度历史文件
QList<QVector<double> > FileUtils::readTempData(QString path){
    QList<QVector<double> > tempData = QList<QVector<double> >();
    QVector<double> x,y;
    int i = 0;
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"打开文件失败。"<<endl;
    }
    while(!file.atEnd()){
        QByteArray line = file.readLine();
        QString str(line);
        if(i % 2 == 0){
            // line是yyyy-MM-dd hh:mm:ss的日期,line.remove()除掉\r\n
            QDateTime time = QDateTime::fromString(str.replace("\r\n",""),"hh:mm:ss");
            //一天中第minutes分钟
            int minutes = FileUtils::calMinute(time);
            x.append(minutes);
        }else{
            double tempDou = line.replace("\n","").toDouble();
            y.append(tempDou);
        }
        i++;
    }
    tempData.append(x);
    tempData.append(y);
    file.close();
    return tempData;
}

// 打开温湿度历史文件
QList<QVector<double> > FileUtils::readTempAndHumiData(QString path){
    QList<QVector<double> > tempData = QList<QVector<double> >();
    // x-time,y-temp,z-humi
    QVector<double> x,y,z;
    int i = 0;
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"打开文件失败。"<<endl;
    }
    while(!file.atEnd()){
        QByteArray line = file.readLine();
        QString str(line);
        if(i % 3 == 0){
            // line是yyyy-MM-dd hh:mm:ss的日期,line.remove()除掉\r\n
            QDateTime time = QDateTime::fromString(str.replace("\r\n",""),"hh:mm:ss");
            //一天中第minutes分钟
            int minutes = FileUtils::calMinute(time);
            x.append(minutes);
        }
        else if(i % 3 == 1)
        {
            double tempDou = line.replace("\n","").toDouble();
            y.append(tempDou);
        }
        else
        {
            double humiDou = line.replace("\n","").toDouble();
            z.append(humiDou);
        }
        i++;
    }
    tempData.append(x);
    tempData.append(y);
    tempData.append(z);
    file.close();
    return tempData;
}

int FileUtils::calMinute(QDateTime dateTime){
    // minutes表示一天中的第多少分钟
    int minutes = 0;
    QString hourStr,minStr;
    if(!dateTime.isNull() && dateTime.isValid()){
        hourStr = dateTime.toString("hh");
        minStr = dateTime.toString("mm");
    }
    int hour = hourStr.toInt();
    int min = minStr.toInt();
    switch(hour){
    case 0:
        return min;
    case 1:
        return 60 + min;
    case 2:
        return 120 + min;
    case 3:
        return 180 + min;
    case 4:
        return 240 + min;
    case 5:
        return 300 + min;
    case 6:
        return 360 + min;
    case 7:
        return 420 + min;
    case 8:
        return 480 + min;
    case 9:
        return 540 + min;
    case 10:
        return 600 + min;
    case 11:
        return 660 + min;
    case 12:
        return 720 + min;
    case 13:
        return 780 + min;
    case 14:
        return 840 + min ;
    case 15:
        return 900 + min;
    case 16:
        return 960 + min;
    case 17:
        return 1020 + min;
    case 18:
        return 1080 + min;
    case 19:
        return 1140 + min;
    case 20:
        return 1200 + min;
    case 21:
        return 1260 + min;
    case 22:
        return 1320 + min;
    case 23:
        return 1380 + min;
    }
}
