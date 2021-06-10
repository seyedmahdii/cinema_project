#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loginPage = new Login(nullptr, this);
    homePage = new Home(nullptr, this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_submit_btn_clicked()
{
    QFile file("users.txt");
    file.open(QFile::Text | QFile::Append);
    QTextStream qts(&file);

    QString username = this->ui->un_input->text();
    QString password = this->ui->pw_input->text();
    QString email = this->ui->email_input->text();

    if(username!="" && password!="" && email!=""){
        qts << username + " " + password + " " + email + "\n";

        QString title = "اومدی داخل";
        QString message = "خوش اومدی.";
        QMessageBox::information(this, title, username + message);

        homePage->showMaximized();
        this->close();
    }
    else{
        QString title = "خطا";
        QString message ="فیلد ها را تکمیل نمایید";
        QMessageBox::warning(this, title, message);
    }
    file.close();
}

void MainWindow::on_footer_log_btn_clicked()
{
    loginPage->showMaximized();
    this->close();
}
