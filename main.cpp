#include "mainwindow.h"
#include <QApplication>

#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Instantiating the forms
    Login login;

    MainWindow w;
    w.showMaximized();

    return a.exec();
}
