#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <vector>
#include<QTableWidget>
#include<QString>
#include<QtGui>
#include"file.h"


class Spreadsheet:public QTableWidget
{
    Q_OBJECT

public:
    Spreadsheet();
    QString getNameClass() const;
    void setNameClass(QString nameClass);
    bool isChanged()const;

private slots:
    void setChangeDel();
    void changTable();
    void printDate(QVector<QVector<QString>> data,int row,int column,int x=0,int y=0);

private:
    bool change_;
    QString name_class_;
};

#endif // SPREADSHEET_H
