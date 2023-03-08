#include<QFile>
#include<QFileDialog>
#include<QMessageBox>
#include<QtGui>
#include "mainwindow.h"
#include"createnameclass.h"
#include "ui_mainwindow.h"
#include "table.h"


QString MainWindow::save_path_ = QDir::homePath();

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow),size_button_x_(0),size_button_y_(0)
{
    ui->setupUi(this);
    ui->creatButtons->setFixedSize(90,90);

    main_->addWidget(ui->creatButtons,0,0);
    ui->centralwidget->setLayout(main_);

    connect(ui->actionDelete_all_class,SIGNAL(triggered(bool)),this,SLOT(deleteAllClass()));
    connect(ui->actionChange_path_to_save,SIGNAL(triggered(bool)),this,SLOT(changePathSave()));
    connect(ui->actionExit,SIGNAL(triggered(bool)),SLOT(close()));
    ui->actionChange_path_to_save->setStatusTip("Changing the save class path and moving all classes to the new path");

    button_list_ = settings_.value("/Settings/classes").toStringList();
    createButton();

    QString pathSettings = settings_.value("/Settings/path","").toString();
    if(!pathSettings.isEmpty())
            save_path_ = pathSettings;
    else
    {
        QDir saveDir(save_path_);
        saveDir.mkdir("SaveDir");
        save_path_ += "/SaveDir";
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QMap<QString,QMainWindow* >::iterator currentIterator = running_proces_.begin();
    QMap<QString,QMainWindow* >::iterator nextIterator;
    int counterProcess=running_proces_.size();

    while(counterProcess){
        nextIterator=currentIterator+1;
        currentIterator.value()->close();
        currentIterator=nextIterator;
        counterProcess--;
    }

    settings_.beginGroup("/Settings");
    settings_.setValue("/path",save_path_);
    settings_.setValue("/classes",button_list_);
    settings_.endGroup();
    event->accept();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::deleteAllClass()
{
    for (int i = 1; i < main_->count(); ++i) {
        QPushButton *button = qobject_cast<QPushButton*>(main_->itemAt(i)->widget());
        QFile file(save_path_ + "/" + button->text() + ".bin");
        file.remove();
        button->deleteLater();
    }

    QMap<QString,QMainWindow* >::iterator current = running_proces_.begin();
    for(;current!=running_proces_.end(); current++){
        current.value()->deleteLater();
    }

    size_button_x_ = 0;
    size_button_y_ = 0;
    clearGreadLeauot();
    button_list_.clear();
    running_proces_.clear();
}

void MainWindow::changePathSave()
{
    QString newPath = QFileDialog::getExistingDirectory(0,"Select a Directory",QCoreApplication::applicationDirPath());

    if(!newPath.isEmpty() && newPath != save_path_ && newPath != save_path_.mid(0,save_path_.size()-8))
    {
        QDir oldDir(save_path_);
        QStringList date = oldDir.entryList();
        QDir newDir(newPath);
        newDir.mkdir("SaveDir");
        for (auto name: date) {
            QString temp = save_path_ + "/" + name;
            QFile::copy(temp,newPath + "/SaveDir/" + name);
            oldDir.remove(temp);
        }

        oldDir.rmdir(save_path_);
        save_path_=newPath + "/SaveDir";

        settings_.beginGroup("/Settings");
        settings_.setValue("/path",save_path_);
        settings_.endGroup();
    }
    else{
        QMessageBox::warning(this,"Warning","The folder is already exist in this folder or you are trying to create a subfolder within the folder SaveDir. Chack save path again!");
    }
}


void MainWindow::clearGreadLeauot()
{
    for (int i = 1; i < main_->count(); ++i) {
        QPushButton* button = qobject_cast<QPushButton*>(main_->itemAt(i)->widget());
        button->deleteLater();
    }
}

void MainWindow::on_creatButtons_clicked()
{
    CreateNameClass* setNameDialog = new CreateNameClass;
    setNameDialog->setWindowTitle("Class name creation dialog");
    setNameDialog->show();

    if(setNameDialog->exec() == QDialog::Accepted)
    {
        QStringList::iterator it = qFind(button_list_.begin(),button_list_.end(),setNameDialog->nameClass());
        if(it==button_list_.end())
        {
            oneCreateButton(setNameDialog->nameClass());

            button_list_.push_back(setNameDialog->nameClass());
        }
        else
            QMessageBox::warning(this,"Warning","Class with this name already created");
    }
    delete setNameDialog;
}

QString MainWindow::getPath(){
    return save_path_;
}

void MainWindow::deletClass()
{
    QAction* removeButton = (QAction*)sender();

    QString nameButton = removeButton->text();
    nameButton = nameButton.mid(7,nameButton.size());

    QFile file(save_path_ + "/" + nameButton + ".bin");
    file.remove();

    QStringList::iterator iteratorRemoveButton = qFind(button_list_.begin(),button_list_.end(),nameButton);
    button_list_.erase(iteratorRemoveButton);

    QMap<QString,QMainWindow* > :: iterator iteratorRemoveProcess = running_proces_.find(nameButton);
    if(iteratorRemoveProcess != running_proces_.end())
    {
        iteratorRemoveProcess.value()->deleteLater();
    }

    clearGreadLeauot();

    size_button_x_ = 0;
    size_button_y_ = 0;

    createButton();
}

void MainWindow::createButton()
{
    for (int var = 0; var < button_list_.size(); ++var)
    {
        oneCreateButton(button_list_[var]);
    }
}

void MainWindow::oneCreateButton(QString nameClass)
{
    size_button_x_++;
    QPushButton* creatButtons = new QPushButton(nameClass);
    creatButtons->setFixedSize(90,90);
    if(size_button_x_>4)
    {
        size_button_x_ = 0;
        size_button_y_++;
    }
    main_->addWidget(creatButtons,size_button_y_,size_button_x_);

    connect(creatButtons,SIGNAL(clicked(bool)),this,SLOT(openClass()));
    contextMenu(creatButtons);
}

void MainWindow::contextMenu(QPushButton *creatButtons)
{
    QAction* delet = new QAction(tr("Delete ") + creatButtons->text(),this);
    connect(delet,SIGNAL(triggered()),this,SLOT(deletClass()));
    creatButtons->addAction(delet);
    creatButtons->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::closeProcess(QString nameProcess)
{
    QMap<QString,QMainWindow* > :: iterator iteratorCloseProcess = running_proces_.find(nameProcess);
    running_proces_.erase(iteratorCloseProcess);
}

void MainWindow::openClass()
{
    QPushButton* clicedButton = (QPushButton*)sender();
    QMap<QString,QMainWindow* > :: iterator checkRunningProcess = running_proces_.find(clicedButton->text());
    if(checkRunningProcess == running_proces_.end())
    {
        Table* table = new Table(clicedButton->text(),this);
        table->setWindowTitle(clicedButton->text());
        table->show();
        running_proces_.insert(clicedButton->text(),table);
        connect(table,SIGNAL(closeTable(QString)),this,SLOT(closeProcess(QString)));
    }
    else
    {
        QApplication::setActiveWindow(checkRunningProcess.value());
    }
}
