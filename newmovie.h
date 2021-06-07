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
    explicit NewMovie(QWidget *parent = nullptr);
    ~NewMovie();

private slots:
    void on_submit_btn_clicked();

private:
    Ui::NewMovie *ui;
};

#endif // NEWMOVIE_H
