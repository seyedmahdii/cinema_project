#include "home.h"
#include "ui_home.h"

#include "mainwindow.h"

Home::Home(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);

//    this->ui->loged_user_label->setText("aaaa");
}

Home::~Home()
{
    delete ui;
}

void Home::usernameSlot(QString &text)
{
    this->ui->loged_user_label->setText(text);
}
