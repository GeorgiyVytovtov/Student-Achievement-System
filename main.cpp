#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w=new MainWindow;
    w->setWindowTitle("Student Achievement System");
    w->show();
    return a.exec();
}
