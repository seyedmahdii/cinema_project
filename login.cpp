#include "login.h"
#include "ui_login.h"

#include "mainwindow.h"
#include <QMessageBox>

Login::Login(QWidget *parent, QMainWindow * registerPage) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->registerPage = registerPage;

    homePage = new Home();
}

Login::~Login()
{
    delete ui;
}

void Login::on_submit_btn_clicked()
{
    QString username = this->ui->un_input->text();
    QString password = this->ui->pw_input->text();

    if(username != "" && password != ""){
        QFile file("users.txt");
        file.open(QFile::Text | QFile::ReadOnly);
        QTextStream qts(&file);
        while(!qts.atEnd()){
            QStringList qsl = qts.readLine().split(" ");
            if(qsl[0] == username && qsl[1] == password){
                QString title = "اومدی داخل";
                QString message = "خوش اومدی.";
                QMessageBox::information(this, title, qsl[0] + message);

                logedUserData["username"] = username;
                logedUserData["password"] = password;

                homePage->showMaximized();
                this->close();
                break;
            }
        }
        file.close();
    }
    else{
        QString title = "خطا";
        QString message = "لطفا فیلد ها را تکمیل نمایید.";
        QMessageBox::warning(this, title, message);
    }
}

void Login::on_footer_sign_btn_clicked()
{
    registerPage->showMaximized();
    this->close();
}
