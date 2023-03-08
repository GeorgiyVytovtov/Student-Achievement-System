#include "sorts.h"
#include "ui_table.h"

Sorts::Sorts(const Spreadsheet *spreadsheet)
{
    this->spreadsheet_=spreadsheet;
    connect(this,SIGNAL(change(QVector<QVector<QString> >,int,int,int,int)),spreadsheet_,SLOT(printDate(QVector<QVector<QString> >,int,int,int,int)));
    connect(this,SIGNAL(cleare()),spreadsheet_,SLOT(clear()));
}

void Sorts::sort()
{
    readTitle();
    readData();
    chooseSort();
    parseData();
    deleter();
    emit cleare();
    emit change(table_data_,table_data_.size(),table_data_[0].size(),0,0);
}

// Function that counts title line with dates.
void Sorts::readTitle()
{
    table_data_.clear();
    QVector<QString> title;
    for(int i = 0; i < spreadsheet_->columnCount(); i++)
    {
        QString temp = spreadsheet_->model()->data(spreadsheet_->model()->index(0,i)).toString();
        title.push_back(temp);
    }
    table_data_.push_back(title);
}

void Sorts::deleter()
{
    for(auto &el:table)
    {
        delete el;
    }
    table.clear();
}

void Sorts::parseData()
{
    for(int i=0; i < table.size(); i++)
    {
        table_data_.push_back(table[i]->getData());
    }
}

void Sorts::chooseSort()
{
    QAction *chooseSort = static_cast<QAction*>(sender());
    if(chooseSort->text() == "Sort from A to Z")
    {
        std::sort(table.begin(),table.end(),[](const TData *elem1,const TData *elem2){
            return elem1->getName()<elem2->getName();
        });
    }
    else if(chooseSort->text() == "Sort from Z to A")
    {
        std::sort(table.begin(),table.end(),[](const TData *elem1,const TData *elem2){
            return elem1->getName()>elem2->getName();
        });
    }
    else if(chooseSort->text() == "Sort by ratings (from best)")
    {
        std::sort(table.begin(),table.end(),[](const TData *elem1,const TData *elem2){
            return elem1->getCoef()>elem2->getCoef();
        });
    }
    else
    {
        std::sort(table.begin(),table.end(),[](const TData *elem1,const TData *elem2){
            return elem1->getCoef()<elem2->getCoef(); //не работает разобраться
        });
    }
}

void Sorts::readData()
{
    QString name;
    QVector<QString> rowData;

    for(int i=1; i < spreadsheet_->rowCount(); i++)
    {
        name = spreadsheet_->model()->data(spreadsheet_->model()->index(i,0)).toString();
        if(name != "")
        {
            for (int j = 0; j < spreadsheet_->columnCount(); ++j)
            {
                QString temp = spreadsheet_->model()->data(spreadsheet_->model()->index(i,j)).toString();
                rowData.push_back(temp);
            }
            TData *elem = new TData(name,rowData);
            table.push_back(elem);
            rowData.clear();
        }
    }
}
