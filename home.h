#ifndef HOME_H
#define HOME_H

#include <QMainWindow>

#include "data.h"
#include "newmovie.h"

namespace Ui {
class Home;
}

class Home : public QMainWindow
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();

private slots:

    void on_add_btn_clicked();

private:
    Ui::Home *ui;

    NewMovie * newMoviePage;
};

#endif // HOME_H
