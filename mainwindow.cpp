#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

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


//void MainWindow::on_closeBtn_clicked()
//{
//    this->close();
//}

//void MainWindow::on_reloadBtn_clicked()
//{
//    this->ui->unInput->clear();
//    this->ui->pwInput->clear();
//}

//void MainWindow::on_loadBtn_clicked()
//{
//    QFile file(user_pass);
//    file.open(QFile::Text | QFile::ReadOnly);
//    QTextStream qts(&file);
//    while(!qts.atEnd()){
//        QStringList qsl = qts.readLine().split(":");
//        this->ui->result->append(qsl[0] + qsl[1]);
//    }
//    file.close();
//}

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
    loginPage.show();
    this->hide();
}
