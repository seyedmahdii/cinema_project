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

void EditMovie::on_submit_btn_clicked()
{
    QString name = ui->name_input->text();
    QString director = ui->director_input->text();
    QString cast = ui->cast_input->text();
    QString genre = ui->genre_input->currentText();
    QString desc = ui->desc_input->toPlainText();
    int tickets = ui->ticket_input->value();

    if(name != "" && director != "" && desc != "" && cast != ""){

        mainWindowPage->showMaximized();
        this->close();
    }
    else{
        QString title = "خطا در ثبت فیلم";
        QString message ="فیلد ها را تکمیل نمایید";
        QMessageBox::critical(this, title, message);
    }
}
