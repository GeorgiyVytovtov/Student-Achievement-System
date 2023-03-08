#ifndef FILE_H
#define FILE_H

#include<QObject>
#include<QFile>
#include<QFileDialog>
#include"spreadsheet.h"
#include"mainwindow.h"

class Spreadsheet;

class File:public QFile
{
    Q_OBJECT

public:
    File(const Spreadsheet* spreadsheet);

public slots:
    void saveAsCsv();
    void readCsv();
    void saveDat();
    void readDat();

private:
    const Spreadsheet* spreadsheet_;

signals:
    void setChangeDel();
    void change(QVector<QVector<QString>>,int,int,int,int);
};

#endif // FILE_H
