#include "logindialog.h"
#include "ui_logindialog.h"

logindialog::logindialog(dbManager* database, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logindialog)
{
    ui->setupUi(this);

    db = database;
}

logindialog::~logindialog()
{
    delete ui;
}

void logindialog::on_logInButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    qDebug() << "login from ui: " << username << ' ' << password;

    if(db->authenticate(username, password)) {
        isAdmin = true;
        QMessageBox::information(this, "Success", "Logged in as Administrator.");
        hide();

    }else {
        QMessageBox::information(this, "Error", "Incorrect username or password.");
    }
}
