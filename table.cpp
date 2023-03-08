#include<vector>
#include<QMessageBox>
#include<QtGui>
#include<QMenu>
#include<QMainWindow>
#include "table.h"
#include "ui_table.h"
#include "spreadsheet.h"


Table::Table(QString name,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Table)
{
    ui->setupUi(this);
    spreadsheet_ = new Spreadsheet();

    spreadsheet_->setRowCount(50);
    spreadsheet_->setColumnCount(50);
    setCentralWidget(spreadsheet_);

    spreadsheet_->setNameClass(name);

    file_ = new File(spreadsheet_);
    edit_ = new Edit(spreadsheet_);
    sorts_ = new Sorts(spreadsheet_);

    creatActions();
    creatContextMenu();
    file_->readDat();

    QTableWidgetItem *templeteItem = new QTableWidgetItem("Full Name\\Date");
    templeteItem->setFlags(Qt::ItemIsEditable);
    spreadsheet_->setItem(0,0,templeteItem);

    connect(spreadsheet_,SIGNAL(itemChanged(QTableWidgetItem*)),spreadsheet_,SLOT(changTable()));
    connect(ui->actionExit,SIGNAL(triggered(bool)),SLOT(close()));
}

Table::~Table()
{
    delete file_;
    delete edit_;
    delete sorts_;
    delete spreadsheet_;
    delete ui;
}

void Table::closeEvent(QCloseEvent *event)
{
    if(spreadsheet_->isChanged())
    {
        QMessageBox::StandardButton res = QMessageBox::information(this,"Close", "Save change in file " + this->windowTitle() + "?",QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
        if(res == QMessageBox::Yes)
        {
            file_->saveDat();
            emit closeTable(this->windowTitle());
            event->accept();
        }
        else if(res == QMessageBox::No)
        {
            emit closeTable(this->windowTitle());
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }
    else{
        emit closeTable(this->windowTitle());
        event->accept();
    }
}

void Table::creatActions()
{
    ui->actionCut->setStatusTip("Cut");
    ui->actionCopy->setStatusTip("Copy");
    ui->actionPast->setStatusTip("Paste");
    ui->actionDelet->setStatusTip("Delete");

    connect(ui->actionToolBar_Save_All,SIGNAL(triggered(bool)),file_,SLOT(saveDat()));
    connect(ui->actionSave_All,SIGNAL(triggered(bool)),file_,SLOT(saveDat()));
    connect(ui->actionImport_CSV,SIGNAL(triggered(bool)),file_,SLOT(readCsv()));
    connect(ui->actionToolBar_Export_CVS,SIGNAL(triggered(bool)),file_,SLOT(readCsv()));
    connect(ui->actionCut,SIGNAL(triggered(bool)),edit_,SLOT(cut()));
    connect(ui->actionToolBar_Cut,SIGNAL(triggered(bool)),edit_,SLOT(cut()));
    connect(ui->actionCopy,SIGNAL(triggered(bool)),edit_,SLOT(copy()));
    connect(ui->actionToolBar_Copy,SIGNAL(triggered(bool)),edit_,SLOT(copy()));
    connect(ui->actionPast,SIGNAL(triggered(bool)),edit_,SLOT(past()));
    connect(ui->actionToolBar_Past,SIGNAL(triggered(bool)),edit_,SLOT(past()));
    connect(ui->actionDelet,SIGNAL(triggered(bool)),edit_,SLOT(deleter()));
    connect(ui->actionToolBar_Delete,SIGNAL(triggered(bool)),edit_,SLOT(deleter()));

    connect(ui->actionSave_as_CSV,SIGNAL(triggered(bool)),file_,SLOT(saveAsCsv()));
    connect(ui->actionToolBar_Save_as_CVS,SIGNAL(triggered(bool)),file_,SLOT(saveAsCsv()));

    connect(ui->actionSort_A_to_Z,SIGNAL(triggered(bool)),sorts_,SLOT(sort()));
    connect(ui->actionSort_Z_to_A,SIGNAL(triggered(bool)),sorts_,SLOT(sort()));
    connect(ui->actionSort_to_best,SIGNAL(triggered(bool)),sorts_,SLOT(sort()));
    connect(ui->actionSort_to_worse,SIGNAL(triggered(bool)),sorts_,SLOT(sort()));
}

void Table::creatContextMenu()
{
    spreadsheet_->addAction(ui->actionCopy);
    spreadsheet_->addAction(ui->actionPast);
    spreadsheet_->addAction(ui->actionCut);
    spreadsheet_->addAction(ui->actionDelet);
    spreadsheet_->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void Table::on_actionAbout_triggered()
{
    QMessageBox::about(this,"Information about program", "This program help you on save date about academic performance students ");
}
