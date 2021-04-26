#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "dbmanager.h"
#include "databaseviewform.h"
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

private:
    Ui::MainWindow *ui;

    // forms
    dbManager* database;
    databaseviewform* dbView;
    logindialog* lDialog;

    bool isAdmin;
};
#endif // MAINWINDOW_H