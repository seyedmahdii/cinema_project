#include "editmovie.h"
#include "ui_editmovie.h"

EditMovie::EditMovie(QWidget *parent, QMainWindow * mainWindowPage) :
    QMainWindow(parent),
    ui(new Ui::EditMovie)
{
    ui->setupUi(this);
    this->mainWindowPage = mainWindowPage;
}

EditMovie::~EditMovie()
{
    delete ui;
}
