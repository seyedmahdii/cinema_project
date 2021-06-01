#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include "home.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_submit_btn_clicked();

    void on_footer_sign_btn_clicked();

    signals:
        void submitSignal(QString &text);

private:
    Ui::Login *ui;
    Home homePage;
};

#endif // LOGIN_H
