#ifndef USERS_H
#define USERS_H

#include <QMainWindow>

#include "QMainWindow"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>

namespace Ui {
class Users;
}

class Users : public QMainWindow
{
    Q_OBJECT

public:
    explicit Users(QWidget *parent = nullptr, QMainWindow * mainWindowPage = nullptr);
    ~Users();

    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);

    void onRemoveUser();

private slots:
    void on_back_btn_clicked();

private:
    Ui::Users *ui;

    QMainWindow * mainWindowPage;
    QVector<QMap<QString, QString>> * users;

    QHash<QPushButton *, int> buttonToRow;
    QHash<QPushButton *, QString> buttonToUser;
};

#endif // USERS_H
