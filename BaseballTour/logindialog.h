#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>

#include <dbmanager.h>

namespace Ui {
class logindialog;
}

class logindialog : public QDialog
{
    Q_OBJECT

public:
    explicit logindialog(dbManager* db = nullptr, QWidget *parent = nullptr);
    ~logindialog();

    // used outside the logindialog window
    bool userIsAdmin() const { return isAdmin;}

private slots:
    void on_logInButton_clicked();

private:
    Ui::logindialog *ui;

    // DO NOT delete in destructor
    dbManager* db;

    // true if user has authenticated successfully
    bool isAdmin;
};

#endif // LOGINDIALOG_H
