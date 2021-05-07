#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "admin.h"

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


    // populate vectors and comboBox
    nameList = database->getTeamNames();
    tempList = nameList;

    for (auto teamName : nameList) {
        ui->simpleFromComboBox->addItem(teamName);
        ui->simpleToComboBox->addItem(teamName);
        ui->addComboBox->addItem(teamName);
    }
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
    Admin *admin;
    lDialog = new logindialog(database);
    lDialog->exec();
    isAdmin = false;
    isAdmin = lDialog->userIsAdmin();
    qDebug() << isAdmin;
    if(isAdmin == true)
    {
        admin = new Admin(database, this);
        admin->show();
    }
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

void MainWindow::on_addPushButton_clicked()
{
    if (ui->addComboBox->count() != 0) {
        QString team = ui->addComboBox->currentText();
        selectedList.push_back(team);

        ui->teamListWidget->addItem(team);
        ui->addComboBox->removeItem(ui->addComboBox->currentIndex());
        ui->startComboBox->addItem(team);
    }
}

void MainWindow::on_removePushButton_clicked()
{
    if (ui->teamListWidget->currentItem() != NULL) {
        QListWidgetItem *item = ui->teamListWidget->currentItem();
        int index = ui->teamListWidget->row(item);
        selectedList.erase(selectedList.begin() + index);

        ui->addComboBox->addItem(item->text());
        ui->startComboBox->removeItem(index);
        ui->teamListWidget->takeItem(index);
    }
}

void MainWindow::on_simpleStartButton_clicked()
{

}
