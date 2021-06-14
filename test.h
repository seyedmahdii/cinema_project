#ifndef TEST_H
#define TEST_H

#include <QMainWindow>

namespace Ui {
class Test;
}

class Test : public QMainWindow
{
    Q_OBJECT

public:
    explicit Test(QWidget *parent = nullptr, QMainWindow * mainWindowPage = nullptr);
    ~Test();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Test *ui;

    QMainWindow * mainWindowPage;
};

#endif // TEST_H
