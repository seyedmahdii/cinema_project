#include "home.h"
#include "ui_home.h"

#include "QMessageBox"

Home::Home(QWidget *parent, QMainWindow * mainWindowPage, QMap<QString, QString> * loggedUser) :
    QMainWindow(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);

    this->mainWindowPage = mainWindowPage;
    this->loggedUser = loggedUser;

    movies = new QVector<QMap<QString, QString>>();
    movieName = new QString();

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

    newMoviePage = new NewMovie(nullptr, this, movies);
    editUserInfoPage = new EditUserInfo(nullptr, this, loggedUser);
    usersPage = new Users(nullptr, this);

    // Adding "New Movie" button for admin
    if((*loggedUser)["username"] == "admin"){
        QPushButton * newMovie_btn = new QPushButton("فیلم جدید");
        ui->header_btn_wrapper->addWidget(newMovie_btn);

        newMovie_btn->setObjectName("newMovie_btn");
        newMovie_btn->setStyleSheet(QString(""
                                            "#newMovie_btn{background-color: #182848; height: 35px; width: 75px; border-radius: 5px; border: 1px solid transparent; color: white; font: 10.5pt B Yekan; cursor: pointing;}"
                                            "#newMovie_btn:hover{background-color: white; border-color: #182848; color: #182848;}"
                                            ));
        QObject::connect(
                    newMovie_btn, &QPushButton::clicked,
                    this, &Home::showNewMoviePage
                    );
    }

    // Adding "Users" button
    if((*loggedUser)["username"] == "admin"){
        QPushButton * users_btn = new QPushButton("مدیریت کاربران‌");
        ui->header_btn_wrapper->addWidget(users_btn);

        users_btn->setObjectName("users_btn");
        users_btn->setStyleSheet(QString(""
                                         "#users_btn{background-color: white; width: 95px; height: 35px; border-radius: 5px; border: 1px solid #182848; color: #182848; font: 10.5pt B Yekan;}"
                                         "#users_btn:hover{background-color: #182848; color: white; border-color: tranparent;}"
                                         ));
        QObject::connect(
                    users_btn, &QPushButton::clicked,
                    this, &Home::showUsersPage
                    );
    }
    else{
        QPushButton * info_btn = new QPushButton("ویرایش مشخصات");
        ui->header_btn_wrapper->addWidget(info_btn);

        info_btn->setObjectName("info_btn");
        info_btn->setStyleSheet(QString(""
                                        "#info_btn{background-color: white; width: 100px; height: 35px; border-radius: 5px; border: 1px solid #182848; color: #182848; font: 10.5pt B Yekan;}"
                                        "#info_btn:hover{background-color: #182848; color: white; border-color: tranparent;}"
                                        ));
        QObject::connect(
                    info_btn, &QPushButton::clicked,
                    this, &Home::showEditUserInfoPage
                    );
    }
}

Home::~Home()
{
    delete ui;
}

void Home::addMovie(QMap<QString, QString> singleMovie){
    QVBoxLayout * upcomingLayouts_Container = qobject_cast<QVBoxLayout *>(ui->movies->layout());

    QVBoxLayout * newMoviesLoayout = new QVBoxLayout();
    newMoviesLoayout->setMargin(10);

    // Adding "delete" and "edit" btn accessable for admin
    if(loggedUser->value("username") == "admin"){
        QHBoxLayout * adminBtntnLoayout = new QHBoxLayout();

        QPushButton * deleteBtn = new QPushButton();
        deleteBtn->setObjectName("deleteMovie_btn");
        QIcon * deleteBtn_icon = new QIcon();
        deleteBtn_icon->addPixmap(QPixmap(":/images/trash-black.png"),QIcon::Normal,QIcon::On);
        deleteBtn->setIcon(* deleteBtn_icon);

        QPushButton * editBtn = new QPushButton();
        editBtn->setObjectName("editMovie_btn");
        QIcon * editBtn_icon = new QIcon();
        editBtn_icon->addPixmap(QPixmap(":/images/edit-black.png"),QIcon::Normal,QIcon::On);
        editBtn->setIcon(* editBtn_icon);

        QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        adminBtntnLoayout->addSpacerItem(spacer);

        adminBtntnLoayout->addWidget(deleteBtn);
        adminBtntnLoayout->addWidget(editBtn);
        newMoviesLoayout->addLayout(adminBtntnLoayout);

        deleteBtn->setStyleSheet(QString(""
                                         "#deleteMovie_btn{background-color: transparent; border: 1px solid #182848; width: 32px; height: 32px; border-radius: 7px;}"
                                         )
                                 );
        editBtn->setStyleSheet(QString(""
                                         "#editMovie_btn{background-color: transparent; border: 1px solid #182848; width: 32px; height: 32px; border-radius: 7px;}"
                                         )
                                 );

        buttonToLayout.insert(deleteBtn, newMoviesLoayout);
        buttonToMovie.insert(deleteBtn, singleMovie["name"]);
        buttonToEditMovie.insert(editBtn, singleMovie["name"]);

        QObject::connect(
                    deleteBtn, &QPushButton::clicked,
                    this, &Home::onRemoveMovie
                    );

        QObject::connect(
                    editBtn, &QPushButton::clicked,
                    this, &Home::showEditMoviePage
                    );
    }

    QHBoxLayout * ticketLoayout = new QHBoxLayout();
    // Spingbox and button for buying ticket
    QSpinBox * ticketInput = new QSpinBox();
    ticketInput->setObjectName("ticektInput_btn");
    ticketInput->setStyleSheet(QString(""
                                       "#ticektInput_btn{height: 32px; border: 1px solid #d6d6d6; background-color: ; color: #182848; border-radius: 6px; font: 14pt B Yekan;}"
                                       ));
    ticketInput->setMinimum(1);
    ticketLoayout->addWidget(ticketInput);

    QPushButton * ticketBtn = new QPushButton("خرید بلیط");
    ticketBtn->setObjectName("ticket_btn");
    ticketBtn->setStyleSheet(QString(""
                                     "#ticket_btn{background-color: white; color: #182848; border: 1px solid #d6d6d6; width: 32px; height: 32px; border-radius: 7px; font: 14pt B Yekan;}"
                                     "#ticket_btn:hover{background-color: #182848; color: white;}"
                                     )
                             );
    if(singleMovie["tickets"] == "0"){
        ticketBtn->setEnabled(false);
    }
    else{
        ticketBtn->setEnabled(true);
    }
    ticketLoayout->addWidget(ticketBtn);

    QLabel * movieLabel = new QLabel("Name: " + singleMovie["name"]);
    movieLabel->setObjectName("movieName_label");
    movieLabel->setStyleSheet(QString(""
                                      "#movieName_label{font: 11pt B Yekan; color: #182848;}"
                                      ));
    newMoviesLoayout->addWidget(movieLabel);

    QLabel * directorLabel = new QLabel("Director: " + singleMovie["director"]);
    directorLabel->setObjectName("movieDirector_label");
    directorLabel->setStyleSheet(QString(""
                                      "#movieDirector_label{font: 11pt B Yekan; color: #182848;}"
                                      ));
    newMoviesLoayout->addWidget(directorLabel);

    QLabel * castLabel = new QLabel("Cast: " + singleMovie["cast"]);
    castLabel->setObjectName("movieCast_label");
    castLabel->setStyleSheet(QString(""
                                      "#movieCast_label{font: 11pt B Yekan; color: #182848;}"
                                      ));
    newMoviesLoayout->addWidget(castLabel);

    QLabel * genreLabel = new QLabel("Genre: " + singleMovie["genre"]);
    genreLabel->setObjectName("movieGenre_label");
    genreLabel->setStyleSheet(QString(""
                                      "#movieGenre_label{font: 11pt B Yekan; color: #182848;}"
                                      ));
    newMoviesLoayout->addWidget(genreLabel);

    QLabel * descLabel = new QLabel("Description: " + singleMovie["desc"]);
    descLabel->setObjectName("movieDesc_label");
    descLabel->setStyleSheet(QString(""
                                      "#movieDesc_label{font: 11pt B Yekan; color: #182848;}"
                                      ));
    newMoviesLoayout->addWidget(descLabel);

    QLabel * ticketsLabel = new QLabel("Available Tickets: " + singleMovie["tickets"]);
    ticketsLabel->setObjectName("movieTickets_label");
    ticketsLabel->setStyleSheet(QString(""
                                      "#movieTickets_label{font: 11pt B Yekan; color: #182848;}"
                                      ));
    newMoviesLoayout->addWidget(ticketsLabel);
    buttonToMovieTicketLabel.insert(ticketBtn, ticketsLabel);

    newMoviesLoayout->addLayout(ticketLoayout);

    upcomingLayouts_Container->insertLayout(2, newMoviesLoayout);

    buttonToMovieTicket.insert(ticketBtn, singleMovie["name"]);
    buttonToTicketInput.insert(ticketBtn, ticketInput);
    QObject::connect(
                ticketBtn, &QPushButton::clicked,
                this, &Home::onBuyTicket
                );
}

void Home::onRemoveMovie(){
    QPushButton * button = qobject_cast<QPushButton * >(sender());
    QVBoxLayout * layout = buttonToLayout.take(button);
    QString movieName = buttonToMovie.take(button);

    for(int i=0; i<movies->size(); i++){
        if(movies->value(i)["name"] == movieName){
            movies->remove(i);
            break;
        }
    }

    removeLayoutContent(layout);
}

void Home::closeEvent(QCloseEvent *){
    // Updating movies file
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

void Home::removeLayoutContent(QLayout * layout){
    QLayoutItem * child;
    while(layout->count() != 0){
        child = layout->takeAt(0);
        // if child is not empty
        if(child->layout() != nullptr){
            removeLayoutContent(child->layout());
        }
        else if(child->widget() != nullptr){
            delete child->widget();
        }

        delete child;
    }
}

void Home::showEvent(QShowEvent *){
    // Clearing the movies container before adding items
    QVBoxLayout * moviesLayout_Container = qobject_cast<QVBoxLayout *>(ui->movies->layout());
    removeLayoutContent(moviesLayout_Container);
    // Adding movies
    for(int i=0; i<movies->length(); i++){
        addMovie(movies->value(i));
    }

    // Updating the user's name
    ui->loged_user_label->setText(loggedUser->value("username"));
}

void Home::showEditMoviePage(){
    QPushButton * button = qobject_cast<QPushButton * >(sender());
    QString movieNameee = buttonToEditMovie.value(button);

    movieName = & movieNameee;
    editMoviePage = new EditMovie(nullptr, this, movies, movieName);

    editMoviePage->showMaximized();
    this->close();
}

void Home::onBuyTicket(){
    QPushButton * button = qobject_cast<QPushButton * >(sender());
    QLabel * ticketLabel = buttonToMovieTicketLabel.value(button);
    QString movieName = buttonToMovieTicket.value(button);
    int inputTicket = buttonToTicketInput.value(button)->value();
    int availableTicket;

    for(int i=0; i<movies->size(); i++){
        QString x = movies->value(i)["name"];
        if(x == movieName){
            availableTicket = movies->value(i)["tickets"].toInt();

            if(inputTicket <= availableTicket){
                availableTicket -= inputTicket;
                QString sTicket = QString::number(availableTicket);
                (*movies)[i]["tickets"] = sTicket;
                ticketLabel->setText("Available Tickets: " + sTicket);
                if(availableTicket == 0){
                    button->setEnabled(false);
                }

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

void Home::on_genre_input_currentIndexChanged(const QString &genre)
{
    QVBoxLayout * moviesLayout_Container = qobject_cast<QVBoxLayout *>(ui->movies->layout());
    removeLayoutContent(moviesLayout_Container);

    for(int i=0; i<movies->length(); i++){
        bool condition = ( movies->value(i)["name"].contains(searched_input) ||
                movies->value(i)["director"].contains(searched_input) ||
                movies->value(i)["cast"].contains(searched_input) ||
                movies->value(i)["genre"].contains(searched_input) ||
                movies->value(i)["desc"].contains(searched_input) )
                ;

        if(genre == "all"){
            addMovie(movies->value(i));
            this->ui->type_input->setText("");
        }
        else if(movies->value(i)["genre"] == genre && condition){
            addMovie(movies->value(i));
        }
    }

    int no_movie = moviesLayout_Container->count();

    if(no_movie == 0){
        QVBoxLayout * upcomingLayouts_Container = qobject_cast<QVBoxLayout *>(ui->movies->layout());
        QVBoxLayout * noMoviesLabelLoayout = new QVBoxLayout();

        QLabel * lbl = new QLabel();
        lbl->setObjectName("no_movie_label");
        lbl->setStyleSheet(QString("#no_movie_label{color: #182848; font: 20pt B Yekan;}"));
        QString message = "چنین فیلمی یافت نشد";
        lbl->setText(message);
        noMoviesLabelLoayout->addWidget(lbl);
        upcomingLayouts_Container->insertLayout(0, noMoviesLabelLoayout);
    }

    searched_genre = genre;
}

void Home::on_type_input_textChanged(const QString &inputValue)
{
    QVBoxLayout * moviesLayout_Container = qobject_cast<QVBoxLayout *>(ui->movies->layout());
    removeLayoutContent(moviesLayout_Container);

    bool no_movie = true;

    for(int i=0; i<movies->length(); i++){
        bool condition = ( movies->value(i)["name"].contains(inputValue) ||
                movies->value(i)["director"].contains(inputValue) ||
                movies->value(i)["cast"].contains(inputValue) ||
                movies->value(i)["genre"].contains(inputValue) ||
                movies->value(i)["desc"].contains(inputValue) )
                ;
        if(condition){
            if(searched_genre == "all"){
                addMovie(movies->value(i));
                no_movie = false;
            }
            else if(movies->value(i)["genre"] == searched_genre){
                addMovie(movies->value(i));
                no_movie = false;
            }
        }
    }

    if(no_movie){
        QVBoxLayout * upcomingLayouts_Container = qobject_cast<QVBoxLayout *>(ui->movies->layout());
        QVBoxLayout * noMoviesLabelLoayout = new QVBoxLayout();

        QLabel * lbl = new QLabel();
        lbl->setObjectName("no_movie_label");
        lbl->setStyleSheet(QString("#no_movie_label{color: #182848; font: 20pt B Yekan;}"));
        QString message = "چنین فیلمی یافت نشد";
        lbl->setText(message);
        noMoviesLabelLoayout->addWidget(lbl);
        upcomingLayouts_Container->insertLayout(0, noMoviesLabelLoayout);
    }

    searched_input = inputValue;
}

void Home::on_logoutBtn_clicked()
{
    mainWindowPage->showMaximized();
    this->close();
}

void Home::showNewMoviePage()
{
    newMoviePage->showMaximized();
    this->close();
}

void Home::showUsersPage(){
    this->close();
    usersPage->showMaximized();
}

void Home::showEditUserInfoPage(){
    editUserInfoPage->showMaximized();
    this->close();
}
