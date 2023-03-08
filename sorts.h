#ifndef SORTS_H
#define SORTS_H

#include <QObject>
#include"tdata.h"
#include"spreadsheet.h"

class Sorts:public QObject
{
    Q_OBJECT

public:
    Sorts(const Spreadsheet* spreadsheet);

public slots:
    void sort();

private:
    const Spreadsheet* spreadsheet_;
    QVector<TData*> table;
    QVector<QVector<QString>> table_data_;

    void readTitle();
    void chooseSort();
    void parseData();
    void deleter();
    void readData();

signals:
    void cleare();
    void change(QVector<QVector<QString>>,int,int,int,int);
};

#endif // SORTS_H
