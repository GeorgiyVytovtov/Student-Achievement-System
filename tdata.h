#ifndef TDATA_H
#define TDATA_H

#include<QVector>
#include<QString>

class TData
{
public:
    TData(QString name,QVector<QString> data);
    ~TData();
    QVector<QString> getData() const;
    QString getName() const;
    int getCoef() const;

private:
    int sumStudentGrades(QVector<QString> data);
    QString name_;
    QVector<QString> data_;
    int sum_of_grades_;
};

#endif // TDATA_H
