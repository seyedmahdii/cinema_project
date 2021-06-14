#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include "QMainWindow"

#include "home.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr, QMainWindow * registerPage = nullptr);
    ~Login();

private slots:
    void on_submit_btn_clicked();

    void on_footer_sign_btn_clicked();

private:
    Ui::Login *ui;
    QMainWindow * registerPage;
    Home * homePage;
};

#endif // LOGIN_H
