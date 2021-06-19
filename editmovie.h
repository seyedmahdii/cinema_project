#ifndef EDITMOVIE_H
#define EDITMOVIE_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class EditMovie;
}

class EditMovie : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditMovie(QWidget *parent = nullptr, QMainWindow * mainWindowPage = nullptr
            , QVector<QMap<QString, QString>> * movies = nullptr, QString * movieName = nullptr);
    ~EditMovie();

private slots:
    void on_submit_btn_clicked();

    void on_back_btn_clicked();

private:
    Ui::EditMovie *ui;

    QMainWindow * mainWindowPage;

    QVector<QMap<QString, QString>> * movies;
    QString * movieName;
    QString theMovieName;
};

#endif // EDITMOVIE_H
