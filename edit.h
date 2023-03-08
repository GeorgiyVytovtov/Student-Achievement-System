#ifndef EDIT_H
#define EDIT_H

#include<QTableWidget>
#include<QString>
#include "ui_table.h"
#include "spreadsheet.h"

class Edit:public QObject
{
    Q_OBJECT

public:
    Edit(Spreadsheet* spreadsheet);

private slots:
    void copy();
    void past();
    void deleter();
    void cut();

private:
    QTableWidgetSelectionRange selectedRange() const;
    Spreadsheet* spreadsheet_;
    QClipboard* buff_data_=QApplication::clipboard();

signals:
    void change(QVector<QVector<QString>>,int,int,int,int);
};
#endif // EDIT_H
