#include "home.h"
#include "ui_home.h"

#include "QMessageBox"

Home::Home(QWidget *parent, QMainWindow * mainWindowPage) :
    QMainWindow(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);

    this->mainWindowPage = mainWindowPage;
//    editMoviePage = new EditMovie(nullptr, this);

    movies = new QVector<QMap<QString, QString>>();
    newMoviePage = new NewMovie(nullptr, this, movies);

    // Reading movies from file
    QFile moviesFile("movies.txt");
    moviesFile.open(QFile::Text | QFile::ReadOnly);
    QTextStream qts(& moviesFile);
    int movieIndex = 0;
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
            movies->push_back(tMap);
        }
        movieIndex++;
    }
    moviesFile.close();
}

Home::~Home()
{
    delete ui;
}

void Home::on_add_btn_clicked()
{
    newMoviePage->showMaximized();
    this->hide();
}

void Home::addMovie(QMap<QString, QString> singleMovie){
    QVBoxLayout * upcomingLayouts_Container = qobject_cast<QVBoxLayout *>(ui->movies_container->layout());

    QVBoxLayout * newMoviesLoayout = new QVBoxLayout(ui->movies_container);

    // For admins
    QPushButton * deleteBtn = new QPushButton("Delete");
    newMoviesLoayout->addWidget(deleteBtn);

    // For admins
    QPushButton * editBtn = new QPushButton("Edit");
    newMoviesLoayout->addWidget(editBtn);

    // Spingbox and button for buying ticket
    QSpinBox * ticketInput = new QSpinBox();
    ticketInput->setMinimum(1);
    newMoviesLoayout->addWidget(ticketInput);
    QPushButton * ticketBtn = new QPushButton("Buy ticket");
    if(singleMovie["tickets"].toInt() == 0){
        ticketBtn->setEnabled(false);
    }
    else{
        ticketBtn->setEnabled(true);
    }
    newMoviesLoayout->addWidget(ticketBtn);

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

    buttonToLayoutMap.insert(deleteBtn, newMoviesLoayout);
    buttonToMovieMap.insert(deleteBtn, singleMovie["name"]);
    buttonToMovieTicketMap.insert(ticketBtn, singleMovie["name"]);
    buttonToTicketInputMap.insert(ticketBtn, ticketInput->value());

    QObject::connect(
                deleteBtn, &QPushButton::clicked,
                this, &Home::onRemoveMovie
                );

    QObject::connect(
                editBtn, &QPushButton::clicked,
                this, &Home::showEditMoviePage
                );

    QObject::connect(
                ticketBtn, &QPushButton::clicked,
                this, &Home::onBuyTicket
                );
}

void Home::onRemoveMovie(){
    QPushButton * button = qobject_cast<QPushButton * >(sender());
    QVBoxLayout * layout = buttonToLayoutMap.take(button);
    QString movieName = buttonToMovieMap.take(button);

    for(int i=0; i<movies->size(); i++){
        if(movies->value(i)["name"] == movieName){
            movies->remove(i);
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

    for(int i=0; i<movies->length(); i++){
        qts << movies->value(i)["name"] << "\n" << movies->value(i)["director"] << "\n"
                                 << movies->value(i)["cast"] << "\n" << movies->value(i)["genre"]
                                 << "\n" << movies->value(i)["desc"] << "\n" << movies->value(i)["tickets"]
                                 << "\n";
    }
    moviesFile.close();
}

void Home::showEvent(QShowEvent *ev){
    QMainWindow::showEvent(ev);

    ui->loged_user_label->setText("hello world");

    for(int i=0; i<movies->length(); i++){
        addMovie(movies->value(i));
    }
}

void Home::showEditMoviePage(){
    editMoviePage->showMaximized();
    this->close();
}

void Home::onBuyTicket(){
    QPushButton * button = qobject_cast<QPushButton * >(sender());
    QString movieName = buttonToMovieTicketMap.value(button);
    int inputTicket = buttonToTicketInputMap.value(button);
    int availableTicket;

    for(int i=0; i<movies->size(); i++){
        QString x = movies->value(i)["name"];
        if(x == movieName){
            availableTicket = movies->value(i)["tickets"].toInt();

            if(inputTicket <= availableTicket){
                availableTicket -= inputTicket;
                QString sTicket = QString::number(availableTicket);
                // ************************************************** updating the vector ticket *********************
                movies->value(i)["tickets"]= sTicket;
                QVector<QMap<QString, QString>> * ttt = movies;

                QString message = "بلیط با موفقیت خریداری شد";
                QString title = "خرید بلیط";
                QMessageBox::information(this, title, message);
            }
            else{
                QString message = "تعداد بلیط خریداری شده بیشتر از موجودی فیلم می باشد";
                QString title = "خرید بلیط";
                QMessageBox::critical(this, title, message);
            }
            break;
        }
    }
}
