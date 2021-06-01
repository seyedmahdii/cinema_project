#include "home.h"
#include "ui_home.h"

#include "mainwindow.h"

Home::Home(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);
}

Home::~Home()
{
    delete ui;
}

// **************** Signal ****************
void Home::usernameSlot(QString &text)
{
    this->ui->loged_user_label->setText(text);
}
