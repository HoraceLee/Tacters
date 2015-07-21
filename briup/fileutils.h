#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QFile>
#include <QDateTime>
#include <QList>
#include <QVector>

class FileUtils : public QFile {
public:
    FileUtils();

    static int DIALOG_MODE;

    static void readFile(QString path);
    // 追加写,if file not exists, create new file
    static void appendFile(QString path,QString str);
    // 覆盖写,if file not exists, create new file
    static void writeFile(QString path,QString str);

    static void deleteFile(QString path);

    static bool openFile(QString path);

    static void writeTempData(QString path,QDateTime time,QString data);

    static void writeTempAndHumiData(QString path,QDateTime time,QString tempData,QString humiData);

    //读温度传感器的历史数据
    static QList<QVector<double> > readTempData(QString path);

    // 读温度传感器
    static QList<QVector<double> > readTempAndHumiData(QString path);

    //记录所选的实验id
    static int project_id;
    static int calMinute(QDateTime dateTime);

};



#endif // FILEUTILS_H
