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
    explicit EditMovie(QWidget *parent = nullptr, QMainWindow * mainWindowPage = nullptr);
    ~EditMovie();

private slots:
    void on_submit_btn_clicked();

private:
    Ui::EditMovie *ui;

    QMainWindow * mainWindowPage;
};

#endif // EDITMOVIE_H
