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
    void showEditMoviePage();

private slots:
    void on_add_btn_clicked();

private:
    Ui::Home *ui;

    NewMovie * newMoviePage;
    EditMovie * editMoviePage;
    QMainWindow * mainWindowPage;

    QHash<QPushButton *, QVBoxLayout *> mButtonToLayoutMap;
    QHash<QPushButton *, QString> mButtonToMovieMap;

    QVector<QMap<QString, QString>> movies;
    QVector<QMap<QString, QString>> movies_copy;
};

#endif // HOME_H
