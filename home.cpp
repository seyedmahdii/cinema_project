#include "home.h"
#include "ui_home.h"

#include "QMessageBox"

Home::Home(QWidget *parent, QMainWindow * mainWindowPage) :
    QMainWindow(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);

    this->mainWindowPage = mainWindowPage;
    newMoviePage = new NewMovie(nullptr, this);
//    editMoviePage = new EditMovie(nullptr, nullptr);


//    QString t = logedUserData["username"];
    /*ui->loged_user_label->setText(t);

    if(t == "admin"){
        ui->add_btn->setEnabled(true);
    }*//*
    else{
        ui->add_btn->setEnabled(false);
    }*/


    // Reading movies from file
    QFile moviesFile("movies.txt");
    moviesFile.open(QFile::Text | QFile::ReadOnly);
    QTextStream qts(& moviesFile);
    int movieIndex = 0;
    QVector<QMap<QString, QString>> movies;
    QMap<QString, QString> tMap;

    while(!qts.atEnd()){
        QString line = qts.readLine();
        if(movieIndex %6 == 0){
            tMap.insert("name", line);
        }
        else if(movieIndex %6 == 1){
            tMap.insert("director", line);
        }
        else if(movieIndex %6 == 2){
            tMap.insert("cast", line);
        }
        else if(movieIndex %6 == 3){
            tMap.insert("genre", line);
        }
        else if(movieIndex %6 == 4){
            tMap.insert("desc", line);
        }
        else if(movieIndex %6 == 5){
            tMap.insert("tickets", line);
            movies.push_back(tMap);
        }
        movieIndex++;
    }
    moviesFile.close();


    for(int i=0; i<movies.length(); i++){
        addMovie(movies[i]);
    }

    movies_copy = movies;
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

void Home::addMovie(QMap<QString, QString> singleMovie){
    QVBoxLayout * upcomingLayouts_Container = qobject_cast<QVBoxLayout *>(ui->movies_container->layout());

    QVBoxLayout * newMoviesLoayout = new QVBoxLayout(ui->movies_container);

    QPushButton * deleteBtn = new QPushButton("Delete");
    newMoviesLoayout->addWidget(deleteBtn);

    QPushButton * editBtn = new QPushButton("Edit");
    newMoviesLoayout->addWidget(editBtn);

    QSpinBox * ticketInput = new QSpinBox();
    ticketInput->setMinimum(1);
    newMoviesLoayout->addWidget(ticketInput);

    QLabel * movieLabel = new QLabel(singleMovie["name"]);
    newMoviesLoayout->addWidget(movieLabel);

    QLabel * directorLabel = new QLabel(singleMovie["director"]);
    newMoviesLoayout->addWidget(directorLabel);

    QLabel * castLabel = new QLabel(singleMovie["cast"]);
    newMoviesLoayout->addWidget(castLabel);

    QLabel * genreLabel = new QLabel(singleMovie["genre"]);
    newMoviesLoayout->addWidget(genreLabel);

    QLabel * descLabel = new QLabel(singleMovie["desc"]);
    newMoviesLoayout->addWidget(descLabel);

    QLabel * ticketsLabel = new QLabel(singleMovie["tickets"]);
    newMoviesLoayout->addWidget(ticketsLabel);

    upcomingLayouts_Container->insertLayout(1, newMoviesLoayout);

    mButtonToLayoutMap.insert(deleteBtn, newMoviesLoayout);
    mButtonToMovieMap.insert(deleteBtn, singleMovie["name"]);

    QObject::connect(
                deleteBtn, &QPushButton::clicked,
                this, &Home::onRemoveMovie
                );

    QObject::connect(
                editBtn, &QPushButton::clicked,
                this, &Home::showEditMoviePage
                );

}

void Home::onRemoveMovie(){
    QPushButton * button = qobject_cast<QPushButton * >(sender());
    QVBoxLayout * layout = mButtonToLayoutMap.take(button);
    QString movieName = mButtonToMovieMap.take(button);

    for(int i=0; i<movies_copy.size(); i++){
        if(movies_copy[i]["name"] == movieName){
            movies_copy.remove(i);
            break;
        }
    }

    while(layout->count() != 0){
        QLayoutItem * item = layout->takeAt(0);
        delete item->widget();
        delete item;
    }
    delete layout;
}

void Home::closeEvent(QCloseEvent *ev){
    QMainWindow::closeEvent(ev);

//     Updating movies file
    QFile moviesFile("movies.txt");
    moviesFile.open(QFile::Append | QFile::Truncate | QFile::Text);
    QTextStream qts(&moviesFile);

    for(int i=0; i<movies_copy.length(); i++){
        qts << movies_copy[i]["name"] << "\n" << movies_copy[i]["director"] << "\n"
                                 << movies_copy[i]["cast"] << "\n" << movies_copy[i]["genre"]
                                 << "\n" << movies_copy[i]["desc"] << "\n" << movies_copy[i]["tickets"]
                                 << "\n";
    }
    moviesFile.close();
}

void Home::showEditMoviePage(){
    editMoviePage->showMaximized();
    this->close();
}
