#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

#include "QMainWindow"
#include "home.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr, QMainWindow * registerPage = nullptr
            , QMap<QString, QString> * loggedUser = nullptr);
    ~Login();

private slots:
    void on_submit_btn_clicked();

    void on_footer_sign_btn_clicked();

private:
    Ui::Login *ui;

    QMainWindow * registerPage;
    Home * homePage;

    QMap<QString, QString> * loggedUser;
};

#endif // LOGIN_H
