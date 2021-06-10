#include "home.h"
#include "ui_home.h"

#include "QMessageBox"
#include <QCheckBox>

Home::Home(QWidget *parent, QMainWindow * mainWindowPage) :
    QMainWindow(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);

    this->mainWindowPage = mainWindowPage;
    newMoviePage = new NewMovie(nullptr, this);

    QString t = logedUserData["username"];

    ui->loged_user_label->setText(t);

    if(t == "admin"){
        ui->add_btn->setEnabled(true);
    }/*
    else{
        ui->add_btn->setEnabled(false);
    }*/


    // Reading movies from file
    QFile moviesFile("movies.txt");
    moviesFile.open(QFile::Text | QFile::ReadOnly);
    QTextStream qts(& moviesFile);
    int i = 0;
    QVector<QMap<QString, QString>> movies;
    QMap<QString, QString> tMap;

    while(!qts.atEnd()){
        QString line = qts.readLine();
        if(i %6 == 0){
            tMap.insert("name", line);
        }
        else if(i %6 == 1){
            tMap.insert("director", line);
        }
        else if(i %6 == 2){
            tMap.insert("cast", line);
        }
        else if(i %6 == 3){
            tMap.insert("genre", line);
        }
        else if(i %6 == 4){
            tMap.insert("desc", line);
        }
        else if(i %6 == 5){
            tMap.insert("tickets", line);
            movies.push_back(tMap);
        }
        i++;
    }
    moviesFile.close();


    QObject::connect(
                this->ui->addWidget, &QPushButton::clicked,
                this, &Home::onAddMovie
                );
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

void Home::onAddMovie(){
      QHBoxLayout * layout = qobject_cast<QHBoxLayout *>(ui->my_frame->layout());

      QVBoxLayout * newLoayout = new QVBoxLayout(ui->my_frame);

      QString buttonText = tr("Button: #%1").arg(layout->count());
      QPushButton * button = new QPushButton(buttonText, ui->my_frame);

      newLoayout->addWidget(button);

      QCheckBox * checkBox = new QCheckBox("Check me!", ui->my_frame);
      newLoayout->addWidget(checkBox);

      layout->insertLayout(0, newLoayout);

      mButtonToLayoutMap.insert(button, newLoayout);

      QObject::connect(
             button, &QPushButton::clicked,
             this, &Home::onRemoveMovie
                 );
}

void Home::onRemoveMovie(){
    QPushButton * button = qobject_cast<QPushButton * >(sender());
    QVBoxLayout * layout = mButtonToLayoutMap.take(button);

    while(layout->count() != 0){
        QLayoutItem * item = layout->takeAt(0);
        delete item->widget();
        delete item;
    }
    delete layout;
}

//void Home::closeEvent(){
//    // Updating movies file
//    QFile moviesFile("movies.txt");
//    moviesFile.open(QFile::ReadWrite | QFile::Truncate | QFile::Text);
//    QTextStream qtss(&moviesFile);

//    movies[0]["name"] = "friends";

//    for(int i=0; i<movies.length(); i++){
//        qtss << movies[i]["name"] << "\n" << movies[i]["director"] << "\n"
//                                 << movies[i]["cast"] << "\n" << movies[i]["genre"]
//                                 << "\n" << movies[i]["desc"] << "\n" << movies[i]["tickets"]
//                                 << "\n";
//    }
//    moviesFile.close();
//}
