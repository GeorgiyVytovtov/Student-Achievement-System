#include "file.h"

File::File(const Spreadsheet* spreadsheet)
{
    this->spreadsheet_ = spreadsheet;
    connect(this,SIGNAL(change(QVector<QVector<QString> >,int,int,int,int)),spreadsheet_,SLOT(printDate(QVector<QVector<QString> >,int,int,int,int)));
    connect(this,SIGNAL(setChangeDel()),spreadsheet_,SLOT(setChangeDel()));
}

void File::saveAsCsv()
{
    QString path = QFileDialog::getSaveFileName(0,"Save As",spreadsheet_->getNameClass(),"All file (*.*);;CSV (*.csv)");
    QFile file(path + ".csv");
    if(!file.open(QFile::WriteOnly))
    {
        return;
    }
    QTextStream streamWrite(&file);
    for(int i=0; i< spreadsheet_->rowCount();i++)
    {
        for(int j = 0; j < spreadsheet_->columnCount(); ++j)
        {
           QString temp = spreadsheet_->model()->data(spreadsheet_->model()->index(i,j)).toString();
           streamWrite<<temp + ";";
        }
        streamWrite<<"\n";
    }
    file.close();
}

void File::saveDat()
{
    QFile file(MainWindow::getPath() + "/" + spreadsheet_->getNameClass() + ".bin");
    if(!file.open(QFile::WriteOnly))
    {
        return;
    }
    else
    {
        QDataStream streamWrite(&file);
        for(int i=0; i< spreadsheet_->rowCount();i++)
        {
            for(int j = 0; j < spreadsheet_->columnCount(); ++j)
            {
               QString temp = spreadsheet_->model()->data(spreadsheet_->model()->index(i,j)).toString();
               streamWrite<<temp;
            }
        }
    }
    file.close();

    if(spreadsheet_->isChanged())
    {
        connect(spreadsheet_,SIGNAL(itemChanged(QTableWidgetItem*)),spreadsheet_,SLOT(changTable()));
        emit setChangeDel();
    }
}


void File::readDat()
{
    QFile file(MainWindow::getPath() + "/" + spreadsheet_->getNameClass() + ".bin");
    QVector<QVector<QString>> tableData(spreadsheet_->columnCount(),QVector<QString>(spreadsheet_->rowCount()));
    if(!file.open(QFile::ReadOnly))
    {
        return;
    }
    else
    {
        QDataStream streamRead(&file);
        for(int i=0; i < spreadsheet_->rowCount();i++)
        {
            for (int j = 0; j < spreadsheet_->columnCount(); ++j)
            {
                streamRead>>tableData[i][j];
            }
        }
    }
    file.close();
    emit change(tableData,tableData.size(),tableData[0].size(),0,0);
}


void File::readCsv()
{
    QVector<QVector<QString>> tableData;
    QString path = QFileDialog::getOpenFileName(0,"Open","://C","All file (*.*);;CSV (*.csv)");
    QFile file(path);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
    else
    {
        QTextStream streamRead(&file);
        QVector<QString> rowData;

        while (!streamRead.atEnd())
        {
            rowData.clear();
            QString line = streamRead.readLine();
            for (QString item : line.split(";")) {
                rowData.push_back(item);
            }
            tableData.push_back(rowData);
        }
        file.close();
    }
    emit change(tableData,tableData.size(),tableData[0].size(),0,0);
}








