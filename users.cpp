#include "users.h"
#include "ui_users.h"

Users::Users(QWidget *parent, QMainWindow * mainWindowPage) :
    QMainWindow(parent),
    ui(new Ui::Users)
{
    ui->setupUi(this);

    this->mainWindowPage = mainWindowPage;
    users = new QVector<QMap<QString, QString>>();
}

Users::~Users()
{
    delete ui;
}

void Users::closeEvent(QCloseEvent *){
    // Updating users file
    QFile usersFile("users.txt");
    usersFile.open(QFile::Append | QFile::Truncate | QFile::Text);
    QTextStream qts(&usersFile);

    for(int i=0; i<users->length(); i++){
        qts << users->value(i)["username"] << " " << users->value(i)["password"]
                                           << " " << users->value(i)["email"] << "\n";
    }
    usersFile.close();
}

void Users::showEvent(QShowEvent *){
    // Reading users from file
    QFile file("users.txt");
    file.open(QFile::Text | QFile::ReadOnly);
    QTextStream qts(&file);
    while(!qts.atEnd()){
        QStringList qsl = qts.readLine().split(" ");
        QMap<QString, QString> tmap;
        tmap.insert("username", qsl[0]);
        tmap.insert("password", qsl[1]);
        tmap.insert("email", qsl[2]);
        users->push_back(tmap);
    }
    file.close();

    int rowsNum = users->length();
    int colsNum = 4;
    ui->users_table->clear();
    ui->users_table->setRowCount(rowsNum);
    ui->users_table->setColumnCount(colsNum);

    for(int row=0; row<rowsNum; row++){

        QTableWidgetItem * un = new QTableWidgetItem((users->value(row)["username"]));
        ui->users_table->setItem( row, 0, un);

        QTableWidgetItem * pw = new QTableWidgetItem((users->value(row)["password"]));
        ui->users_table->setItem( row, 1, pw);

        QTableWidgetItem * email = new QTableWidgetItem((users->value(row)["email"]));
        ui->users_table->setItem( row, 2, email);

        // Adding delete button
        if(users->value(row)["username"] != "admin"){
            QWidget* pWidget = new QWidget();
            QPushButton* deleteUserBtn = new QPushButton();
            deleteUserBtn->setObjectName("deleteUser_btn");
            deleteUserBtn->setStyleSheet(QString(""
                                     "#deleteUser_btn{width: 35px; height: 35px; border: none; background-color: transparent;}"
                                     ));

            QIcon * btn_icon = new QIcon();
            btn_icon->addPixmap(QPixmap(":/images/trash-black.png"),QIcon::Normal,QIcon::On);
            deleteUserBtn->setIcon(* btn_icon);

            QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
            pLayout->addWidget(deleteUserBtn);
            pLayout->setAlignment(Qt::AlignCenter);
            pLayout->setContentsMargins(0, 0, 0, 0);
            pWidget->setLayout(pLayout);
            ui->users_table->setCellWidget(row, 3, pWidget);

            QObject::connect(deleteUserBtn, &QPushButton::clicked,
                             this, &Users::onRemoveUser
                             );
            buttonToUser.insert(deleteUserBtn, users->value(row)["username"]);
        }
        else{
            QTableWidgetItem * tx = new QTableWidgetItem(":)");
            ui->users_table->setItem(row, 3, tx);
        }
    }

}

void Users::onRemoveUser(){
    QPushButton * button = qobject_cast<QPushButton * >(sender());
    int rowNum = buttonToRow.take(button);
    QString username = buttonToUser.take(button);

    for(int i=0; i<users->size(); i++){
        if(users->value(i)["username"] == username){
            users->remove(i);
            break;
        }
    }

    this->ui->users_table->removeRow(rowNum + 1);
}


void Users::on_back_btn_clicked()
{
    mainWindowPage->showMaximized();
    this->close();
}
