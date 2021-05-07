#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "dbmanager.h"
#include "databaseviewform.h"
#include "databasenameview.h"
#include "logindialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionView_Database_triggered();

    void on_actionLog_In_triggered();

    void on_actionDBG_Is_User_Admin_triggered();

    void on_actionLog_Out_triggered();

    void on_actionView_Database_by_Name_triggered();

    void on_addPushButton_clicked();

    void on_removePushButton_clicked();

    void on_simpleStartButton_clicked();

    void on_actionModify_Database_triggered();

private:
    Ui::MainWindow *ui;

    // forms
    dbManager* database;
    databaseviewform* dbView;
    databaseNameView* dbNameView;
    logindialog* lDialog;
    Admin* adminWindow;

    // contains list of team names for combo boxes
    vector<QString> nameList;
    vector<QString> tempList;
    vector<QString> selectedList;

    bool isAdmin;
};
#endif // MAINWINDOW_H
