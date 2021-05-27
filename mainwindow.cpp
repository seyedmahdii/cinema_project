#include "mainwindow.h"
#include "ui_mainwindow.h"
#define user_pass "user_pass.txt"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_closeBtn_clicked()
{
    this->close();
}

void MainWindow::on_reloadBtn_clicked()
{
    this->ui->unInput->clear();
    this->ui->pwInput->clear();
}

void MainWindow::on_saveBtn_clicked()
{
    QFile file(user_pass);
    file.open(QFile::Text | QFile::Append);
    QTextStream qts(&file);
    qts << "username: " + this->ui->unInput->text() + "\n";
    qts << "password: " + this->ui->pwInput->text() + "\n";
    file.close();
}

void MainWindow::on_loadBtn_clicked()
{
    QFile file(user_pass);
    file.open(QFile::Text | QFile::ReadOnly);
    QTextStream qts(&file);
    while(!qts.atEnd()){
        QStringList qsl = qts.readLine().split(":");
        this->ui->result->append(qsl[0] + qsl[1]);
    }
    file.close();
}
