#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent, QMainWindow * registerPage, QMap<QString, QString> * loggedUser) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    this->registerPage = registerPage;
    this->loggedUser = loggedUser;
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

                loggedUser->insert("username", username);
                loggedUser->insert("password", password);

                // Clearing the inputs
                this->ui->un_input->setText("");
                this->ui->pw_input->setText("");

                homePage = new Home(nullptr, this, loggedUser);
                homePage->showMaximized();
                this->close();
                break;
            }
        }
        file.close();
    }
    else{
        QString title = "خطا در ورود";
        QString message = "لطفا فیلد ها را تکمیل نمایید.";
        QMessageBox::critical(this, title, message);
    }
}

void Login::on_footer_sign_btn_clicked()
{
    registerPage->showMaximized();
    this->close();
}
