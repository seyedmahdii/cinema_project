#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QCloseEvent>
#include "newmovie.h"
#include "editmovie.h"

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
    explicit Home(QWidget *parent = nullptr, QMainWindow * mainWindowPage = nullptr);
    ~Home();

    void addMovie(QMap<QString, QString> singleMovie);

    void onRemoveMovie();

    void closeEvent(QCloseEvent *ev);
    void showEvent(QShowEvent *ev);

    void showEditMoviePage();
    void onBuyTicket();

private slots:
    void on_add_btn_clicked();

private:
    Ui::Home *ui;

    NewMovie * newMoviePage;
    EditMovie * editMoviePage;
    QMainWindow * mainWindowPage;

    QHash<QPushButton *, QVBoxLayout *> buttonToLayoutMap;
    QHash<QPushButton *, QString> buttonToMovieMap;
    QHash<QPushButton *, QString> buttonToMovieTicketMap;
    QHash<QPushButton *, int> buttonToTicketInputMap;

    QVector<QMap<QString, QString>> * movies;
};

#endif // HOME_H
