#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QCloseEvent>
#include "data.h"
#include "newmovie.h"

#include <QPushButton>
#include <QVBoxLayout>

#include <QFile>
#include <QTextStream>
#include <QStringList>

namespace Ui {
class Home;
}

class Home : public QMainWindow
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr, QMainWindow * mainWindowPage = nullptr);
    ~Home();
//    explicit QCloseEvent();
    void closeEvent();

    void onAddMovie();

    void onRemoveMovie();

private slots:

    void on_add_btn_clicked();

private:
    Ui::Home *ui;

    NewMovie * newMoviePage;
    QMainWindow * mainWindowPage;

    QHash<QPushButton *, QVBoxLayout *> mButtonToLayoutMap;
};

#endif // HOME_H
