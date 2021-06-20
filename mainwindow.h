#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFile>
#include <QTextStream>
#include <QStringList>

#include "login.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_submit_btn_clicked();

    void on_footer_log_btn_clicked();

private:
    Ui::MainWindow *ui;
    Login * loginPage;
    Home * homePage;

    QMap<QString, QString> * loggedUser;
    QVector<QMap<QString, QString>> * users;
};

#endif // MAINWINDOW_H
