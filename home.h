#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QCloseEvent>

#include "newmovie.h"
#include "editmovie.h"
#include "edituserinfo.h"
#include "users.h"

#include <QPushButton>
#include <QVBoxLayout>

#include <QFile>
#include <QTextStream>
#include <QStringList>

#include <QSpinBox>

namespace Ui {
class Home;
}

class Home : public QMainWindow
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr, QMainWindow * mainWindowPage = nullptr
            , QMap<QString, QString> * loggedUser = nullptr);
    ~Home();

    void addMovie(QMap<QString, QString> singleMovie);

    void onRemoveMovie();

    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);

    void showEditMoviePage();
    void onBuyTicket();

    void removeLayoutContent(QLayout* layout);
    void showNewMoviePage();
    void showUsersPage();
    void showEditUserInfoPage();

private slots:
    void on_genre_input_currentIndexChanged(const QString &arg1);

    void on_type_input_textChanged(const QString &arg1);

    void on_logoutBtn_clicked();

private:
    Ui::Home *ui;

    NewMovie * newMoviePage;
    EditMovie * editMoviePage;
    QMainWindow * mainWindowPage;
    EditUserInfo * editUserInfoPage;
    Users * usersPage;

    QHash<QPushButton *, QVBoxLayout *> buttonToLayout;
    QHash<QPushButton *, QString> buttonToMovie;
    QHash<QPushButton *, QString> buttonToMovieTicket;
    QHash<QPushButton *, QLabel *> buttonToMovieTicketLabel;
    QHash<QPushButton *, QString> buttonToEditMovie;
    QHash<QPushButton *, QSpinBox *> buttonToTicketInput;

    QVector<QMap<QString, QString>> * movies;
    QString * movieName;

    QVBoxLayout * moviesLayout_Container;

    QMap<QString, QString> * loggedUser;

    QString searched_genre = "all", searched_input;
};

#endif // HOME_H
