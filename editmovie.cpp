#include "editmovie.h"
#include "ui_editmovie.h"

EditMovie::EditMovie(QWidget *parent, QMainWindow * mainWindowPage, QVector<QMap<QString, QString>> * movies, QString * movieName) :
    QMainWindow(parent),
    ui(new Ui::EditMovie)
{
    ui->setupUi(this);
    this->mainWindowPage = mainWindowPage;
    this->movies = movies;
    this->movieName = movieName;
    theMovieName = * movieName;

    for(int i=0; i<movies->length(); i++){
        if(movies->value(i)["name"] == movieName){
            ui->name_input->setText(movies->value(i)["name"]);
            ui->director_input->setText(movies->value(i)["director"]);
            ui->cast_input->setText(movies->value(i)["cast"]);
            ui->genre_input->setCurrentText(movies->value(i)["genre"]);
            ui->desc_input->setText(movies->value(i)["desc"]);
            ui->ticket_input->setValue(movies->value(i)["tickets"].toInt());
            break;
        }
    }
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
        for(int i=0; i<movies->length(); i++){
            if((*movies)[i]["name"] == theMovieName){
                (*movies)[i]["name"] = name;
                (*movies)[i]["director"] = director;
                (*movies)[i]["cast"] = cast;
                (*movies)[i]["genre"] = genre;
                (*movies)[i]["desc"] = desc;
                QString sTickets = QString::number(tickets);
                (*movies)[i]["tickets"] = sTickets;

                QString title = "ویرایش فیلم";
                QString message ="فیلم با موفقیت ویرایش شد";
                QMessageBox::information(this, title, message);
                break;
            }
        }

        mainWindowPage->showMaximized();
        this->close();
    }
    else{
        QString title = "خطا در ثبت فیلم";
        QString message ="فیلد ها را تکمیل نمایید";
        QMessageBox::critical(this, title, message);
    }
}
