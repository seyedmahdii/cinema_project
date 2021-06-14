#include "test.h"
#include "ui_test.h"

Test::Test(QWidget *parent, QMainWindow * mainWindowPage) :
    QMainWindow(parent),
    ui(new Ui::Test)
{
    ui->setupUi(this);

    this->mainWindowPage = mainWindowPage;
}

Test::~Test()
{
    delete ui;
}

void Test::on_pushButton_clicked()
{
    mainWindowPage->show();
    this->close();
}
