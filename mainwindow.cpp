#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loggedUser = new QMap<QString, QString>();
    loginPage = new Login(nullptr, this, loggedUser);
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

        loggedUser->insert("username", username);
        loggedUser->insert("password", password);
        loggedUser->insert("email", email);

        // Clearing the inputs
        this->ui->un_input->setText("");
        this->ui->pw_input->setText("");
        this->ui->email_input->setText("");

        homePage = new Home(nullptr, this, loggedUser);
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
