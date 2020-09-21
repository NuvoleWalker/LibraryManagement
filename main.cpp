#include "mainwindow.h"
#include"to_start.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    to_Start *start=new to_Start();
    start->show();
//    MainWindow m;
//    m.show();
    return a.exec();
}
