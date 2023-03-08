#include "edit.h"

Edit::Edit(Spreadsheet* spreadsheet)
{
    this->spreadsheet_ = spreadsheet;
    connect(this,SIGNAL(change(QVector<QVector<QString>>,int,int,int,int)),spreadsheet_,SLOT(printDate(QVector<QVector<QString>>,int,int,int,int)));
}
QTableWidgetSelectionRange Edit::selectedRange() const
{
    QList<QTableWidgetSelectionRange> ranges = spreadsheet_->selectedRanges();
    if(ranges.isEmpty())
        return QTableWidgetSelectionRange();
    return ranges.first();
}

void Edit::copy()
{
    QTableWidgetSelectionRange ranges = selectedRange();
    QString cellData;
    for(int i=0; i < ranges.rowCount();i++)
    {
        for (int j = 0; j < ranges.columnCount();++j)
        {
            QString temp = spreadsheet_->model()->data(spreadsheet_->model()->index(ranges.topRow()+i,ranges.leftColumn()+j)).toString();
            cellData += temp + '\t';
        }
        cellData.back() = '\n';
    }
    buff_data_->setText(cellData);
}

void Edit::past()
{
    QTableWidgetSelectionRange range = selectedRange();
    QVector<QVector<QString>> pastData;
    QVector<QString> rowPastDate;
    QString data = buff_data_->text();

    for (auto str:data.split("\n"))
    {
        QString temp = str;
        if(!temp.isEmpty())
        {
            for(auto str1:temp.split("\t")){
                rowPastDate.push_back(str1);
            }
            pastData.push_back(rowPastDate);
            rowPastDate.clear();
        }
    }
    if(!pastData.empty())
        emit change(pastData,pastData.size(),pastData[0].size(),range.topRow(),range.leftColumn());
}

void Edit::cut()
{
    copy();
    deleter();
}

void Edit::deleter()
{
    QTableWidgetSelectionRange range = selectedRange();
    QVector<QVector<QString>> deletData(range.rowCount(),QVector<QString>(range.columnCount(),""));
    if(!deletData.empty())
        emit change(deletData,deletData.size(),deletData[0].size(),range.topRow(),range.leftColumn());
}
