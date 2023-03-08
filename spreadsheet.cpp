#include "spreadsheet.h"
#include<QApplication>
#include<QtGui>
#include<QFileDialog>
#include"edit.h"


Spreadsheet::Spreadsheet():change_(false)
{
}

void Spreadsheet::setChangeDel()
{
    change_ = false;
}
void Spreadsheet::changTable()
{
    if(!change_)
    {
        change_ = true;
        disconnect(this,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(changTable()));
    }
}

QString Spreadsheet::getNameClass() const
{
    return name_class_;
}
void Spreadsheet::setNameClass(QString nameClass)
{
    this->name_class_=nameClass;
}
bool Spreadsheet::isChanged()const
{
    return change_;
}

void Spreadsheet::printDate(QVector<QVector<QString>> data,int row,int column,int x,int y)
{
    for(int i=0; i < row; i++){
        for(int j=0; j < column; j++){
            QTableWidgetItem *item=new QTableWidgetItem(data[i][j]);
            setItem(i+x,j+y,item);
        }
    }
    QAction *senderActionMenu = (QAction*)sender();
    QString temp = senderActionMenu->metaObject()->className();
    if(temp == "File" || temp == "Sorts")
    {
        QTableWidgetItem *templeteItem = new QTableWidgetItem("Full Name\\Date");
        templeteItem->setFlags(Qt::ItemIsEditable);
        setItem(0,0,templeteItem);
    }
}
