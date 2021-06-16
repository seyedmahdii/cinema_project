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

    void removeLayoutContent(QLayout* layout);

private slots:
    void on_add_btn_clicked();

    void on_searchBtn_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_type_input_textChanged(const QString &arg1);

private:
    Ui::Home *ui;

    NewMovie * newMoviePage;
    EditMovie * editMoviePage;
    QMainWindow * mainWindowPage;

    QHash<QPushButton *, QVBoxLayout *> buttonToLayout;
    QHash<QPushButton *, QString> buttonToMovie;
    QHash<QPushButton *, QString> buttonToMovieTicket;
    QHash<QPushButton *, QString> buttonToEditMovie;
    QHash<QPushButton *, int> buttonToTicketInput;

    QVector<QMap<QString, QString>> * movies;
    QString * movieName;

    QVBoxLayout * moviesLayout_Container;
};

#endif // HOME_H
