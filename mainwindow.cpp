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

    users = new QVector<QMap<QString, QString>>();

    QFile usersFile("users.txt");
    usersFile.open(QFile::Text | QFile::ReadOnly);
    QTextStream qts(&usersFile);
    while(!qts.atEnd()){
        QStringList qsl = qts.readLine().split(" ");
        QMap<QString, QString> singleUser;
        singleUser.insert("username", qsl[0]);
        singleUser.insert("password", qsl[1]);
        singleUser.insert("email", qsl[2]);
        users->push_back(singleUser);
    }
    usersFile.close();
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

    if(username=="" || password=="" || email==""){
        QString title = "خطا در ثبت نام";
        QString message ="فیلد ها را تکمیل نمایید";
        QMessageBox::critical(this, title, message);
    }
    else if(username.contains(" ") || password.contains(" ") || email.contains(" ")){
        QString title = "خطا در ثبت نام";
        QString message ="فاصله مجاز نمی باشد";
        QMessageBox::critical(this, title, message);
    }
    else{
        // Checking unique usernames
        for(int i=0; i<users->length(); i++){
            if(users->value(i)["username"] == username){
                QString title = "خطا در نام کاربری";
                QString message = "این نام کاربری قبلا ثبت شده است";
                QMessageBox::critical(this, title, message);
                return;
            }
        }

        qts << username + " " + password + " " + email + "\n";

        QString title = "ثبت نام";
        QString message = "ثبت نام با موفقیت انجام شد";
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
    file.close();
}

void MainWindow::on_footer_log_btn_clicked()
{
    loginPage->showMaximized();
    this->close();
}

void MainWindow::on_pw_visibility_btn_clicked()
{
    if(isPasswordVisibile){
        this->ui->pw_input->setEchoMode(QLineEdit::Password);

        QIcon * btn_icon = new QIcon();
        btn_icon->addPixmap(QPixmap(":/images/eye-icon.png"),QIcon::Normal,QIcon::On);
        this->ui->pw_visibility_btn->setIcon(* btn_icon);
    }
    else{
        this->ui->pw_input->setEchoMode(QLineEdit::Normal);

        QIcon * btn_icon = new QIcon();
        btn_icon->addPixmap(QPixmap(":/images/closeeye-icon.png"),QIcon::Normal,QIcon::On);
        this->ui->pw_visibility_btn->setIcon(* btn_icon);
    }
    isPasswordVisibile = !isPasswordVisibile;
}
