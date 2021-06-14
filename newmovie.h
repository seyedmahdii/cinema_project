#ifndef NEWMOVIE_H
#define NEWMOVIE_H

#include <QMainWindow>

#include <QFile>
#include <QStringList>
#include <QTextStream>

namespace Ui {
class NewMovie;
}

class NewMovie : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewMovie(QWidget *parent = nullptr, QMainWindow * mainWindowPage = nullptr
            , QVector<QMap<QString, QString>> * movies = nullptr);
    ~NewMovie();

private slots:
    void on_submit_btn_clicked();

private:
    Ui::NewMovie *ui;

    QMainWindow * mainWindowPage;

    QVector<QMap<QString, QString>> * movies;
};

#endif // NEWMOVIE_H
