#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGridLayout>
#include<QPushButton>
#include<QSettings>
#include<QDir>
#include<QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    static QString getPath();

private slots:
    void on_creatButtons_clicked();
    void closeProcess(QString nameProcess);
    void openClass();
    void deletClass();
    void changePathSave();
    void deleteAllClass();

private:
    Ui::MainWindow* ui;
    QGridLayout* main_=new QGridLayout;

    static QString save_path_;
    QStringList button_list_;
    QSettings settings_;
    QMap<QString,QMainWindow* > running_proces_;

    int size_button_x_;
    int size_button_y_;

    void closeEvent(QCloseEvent* event);
    void contextMenu(QPushButton* creatButtons);
    void oneCreateButton(QString nameClass);
    void createButton();
    void clearGreadLeauot();
};
#endif // MAINWINDOW_H
