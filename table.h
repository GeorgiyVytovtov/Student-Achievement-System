#ifndef TABLE_H
#define TABLE_H

#include <QMainWindow>
#include<QCloseEvent>
#include "edit.h"
#include"file.h"
#include "ui_table.h"
#include"sorts.h"


namespace Ui {
class Table;
}

class Table : public QMainWindow
{
    Q_OBJECT

public:
    explicit Table(QString name,QWidget* parent = nullptr);
    ~Table();

private slots:
    void on_actionAbout_triggered();

private:
    Ui::Table* ui;
    Sorts* sorts_;
    File* file_;
    Edit* edit_;
    Spreadsheet* spreadsheet_;

    void closeEvent(QCloseEvent* event);
    void creatActions();
    void creatContextMenu();

signals:
    void closeTable(QString nameTable);
};

#endif // TABLE_H
