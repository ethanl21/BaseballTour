#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // get expected path of database
    const QString FILE_NAME = "mlb_data.db";
    QString dbPath = qApp->applicationDirPath();
    dbPath.append('/' + FILE_NAME);

    // open database with file path
    database = new dbManager(dbPath);
    qDebug() << "Database should be located at: " << dbPath;

    // user is not admin on program start
    isAdmin = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionView_Database_triggered()
{
    dbView = new databaseviewform(database);
    dbView->exec();
    delete dbView;
}

void MainWindow::on_actionLog_In_triggered()
{
    lDialog = new logindialog(database);
    lDialog->exec();
    isAdmin = lDialog->userIsAdmin();
    delete lDialog;
}

void MainWindow::on_actionDBG_Is_User_Admin_triggered()
{
    if(isAdmin) {
        QMessageBox::information(this, "Success", "User is admin.");
    }else {
        QMessageBox::information(this, "Error", "User is NOT admin.");
    }
}

void MainWindow::on_actionLog_Out_triggered()
{
    if(isAdmin) {
        isAdmin = false;
        QMessageBox::information(this, "Success", "Logged out.");
    }else {
        QMessageBox::information(this, "Error", "User is not logged in.");
    }
}

void MainWindow::on_actionView_Database_by_Name_triggered()
{
    dbNameView = new databaseNameView(database);
    dbNameView->exec();
    delete dbNameView;
}
