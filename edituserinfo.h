#ifndef EDITUSERINFO_H
#define EDITUSERINFO_H

#include <QMainWindow>

#include "QMainWindow"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>

namespace Ui {
class EditUserInfo;
}

class EditUserInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditUserInfo(QWidget *parent = nullptr, QMainWindow * mainWindowPage = nullptr
            , QMap<QString, QString> * toBeEditedUser = nullptr);
    ~EditUserInfo();

    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);

private slots:
    void on_submit_btn_clicked();

    void on_pw_visibility_btn_clicked();

    void on_back_btn_clicked();

private:
    Ui::EditUserInfo *ui;

    QMainWindow * mainWindowPage;

    bool isPasswordVisibile = false;

    QVector<QMap<QString, QString>> * users;
    QMap<QString, QString> * toBeEditedUser;
};

#endif // EDITUSERINFO_H
