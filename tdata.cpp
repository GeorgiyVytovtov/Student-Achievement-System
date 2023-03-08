#include "tdata.h"

TData::TData(QString name, QVector<QString> data):name_(name),data_(data),sum_of_grades_(0)
{
    sumStudentGrades(data);
}


TData::~TData()
{
    data_.clear();
}

QVector<QString> TData::getData() const
{
    return data_;
}

QString TData::getName() const
{
    return name_;
}

int TData::getCoef() const
{
    return sum_of_grades_;
}

int TData::sumStudentGrades(QVector<QString> data)
{
    for(int i = 1; i < data.size(); i++)
    {
        sum_of_grades_+=data[i].toInt();
    }
    return sum_of_grades_;
}
