#include "newmovie.h"
#include "ui_newmovie.h"

#include <QMessageBox>

NewMovie::NewMovie(QWidget *parent, QMainWindow * mainWindowPage) :
    QMainWindow(parent),
    ui(new Ui::NewMovie)
{
    ui->setupUi(this);
    this->mainWindowPage = mainWindowPage;
}

NewMovie::~NewMovie()
{
    delete ui;
}

void NewMovie::on_submit_btn_clicked()
{
    QFile file("movies.txt");
    file.open(QFile::Text | QFile::Append);
    QTextStream qts(& file);

    QString name = ui->name_input->text();
    QString director = ui->director_input->text();
    QString cast = ui->cast_input->text();
    QString genre = ui->genre_input->currentText();
    QString desc = ui->desc_input->toPlainText();
    int tickets = ui->ticket_input->value();

    if(name != "" && director != "" && desc != "" && cast != ""){
        qts << name << "\n" << director << "\n" << cast << "\n" << genre << "\n" << desc << "\n" << tickets << "\n";

        QString title = "اضافه کردن فیلم جدید";
        QString message = "فیلم جدید با موفقیت اضافه شد";
        QMessageBox::information(this, title, message);

        mainWindowPage->showMaximized();
        this->close();
    }
    else{
        QString title = "خطا";
        QString message ="فیلد ها را تکمیل نمایید";
        QMessageBox::warning(this, title, message);
    }
    file.close();
}
