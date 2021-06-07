#include "home.h"
#include "ui_home.h"

#include "mainwindow.h"

#include "QMessageBox"

Home::Home(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);

    newMoviePage = new NewMovie();

    QString t = logedUserData["username"];

    ui->loged_user_label->setText(t);

    if(t == "admin"){
        ui->add_btn->setEnabled(true);
    }/*
    else{
        ui->add_btn->setEnabled(false);
    }*/
}

Home::~Home()
{
    delete ui;
}

void Home::on_add_btn_clicked()
{
    newMoviePage->showMaximized();
    this->close();
}
