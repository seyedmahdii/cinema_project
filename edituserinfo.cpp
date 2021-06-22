#include "edituserinfo.h"
#include "ui_edituserinfo.h"

EditUserInfo::EditUserInfo(QWidget *parent, QMainWindow * mainWindowPage, QMap<QString, QString> * toBeEditedUser) :
    QMainWindow(parent),
    ui(new Ui::EditUserInfo)
{
    ui->setupUi(this);

    this->mainWindowPage = mainWindowPage;
    this->toBeEditedUser = toBeEditedUser;

    users = new QVector<QMap<QString, QString>>();

    this->ui->un_input->setText(toBeEditedUser->value("username"));
    this->ui->pw_input->setText(toBeEditedUser->value("password"));
}

EditUserInfo::~EditUserInfo()
{
    delete ui;
}

void EditUserInfo::on_submit_btn_clicked()
{
    QString username = this->ui->un_input->text();
    QString password = this->ui->pw_input->text();

    if(username != "" && password != ""){
        for(int i=0; i<users->length(); i++){
            if(users->value(i)["username"] == toBeEditedUser->value("username")){
                (*users)[i]["username"] = username;
                (*users)[i]["password"] = password;
            }
        }

        (*toBeEditedUser)["username"] = username;
        (*toBeEditedUser)["password"] = password;

        mainWindowPage->showMaximized();
        this->close();
    }
    else{
        QString title = "خطا در ثبت اطلاعات";
        QString message = "لطفا فیلد ها را تکمیل نمایید.";
        QMessageBox::critical(this, title, message);
    }
}

void EditUserInfo::on_pw_visibility_btn_clicked()
{
    if(isPasswordVisibile){
        this->ui->pw_input->setEchoMode(QLineEdit::Password);

        QIcon * btn_icon = new QIcon();
        btn_icon->addPixmap(QPixmap(":/images/eye-icon.png"),QIcon::Normal,QIcon::On);
        this->ui->pw_visibility_btn->setIcon(* btn_icon);
    }
    else{
        this->ui->pw_input->setEchoMode(QLineEdit::Normal);

        QIcon * btn_icon = new QIcon();
        btn_icon->addPixmap(QPixmap(":/images/closeeye-icon.png"),QIcon::Normal,QIcon::On);
        this->ui->pw_visibility_btn->setIcon(* btn_icon);
    }
    isPasswordVisibile = !isPasswordVisibile;
}

void EditUserInfo::on_back_btn_clicked()
{
    mainWindowPage->showMaximized();
    this->close();
}

void EditUserInfo::closeEvent(QCloseEvent *){
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

void EditUserInfo::showEvent(QShowEvent *){
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
}
