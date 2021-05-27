#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qfile>
#include <QTextStream>
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_closeBtn_clicked();

    void on_reloadBtn_clicked();

    void on_saveBtn_clicked();

    void on_loadBtn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
