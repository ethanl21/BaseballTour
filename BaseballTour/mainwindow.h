#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QStandardPaths>

#include "dbmanager.h"
#include "databaseviewform.h"
#include "databasenameview.h"
#include "logindialog.h"
#include "tripplanner.h"

#include "csvparser.h"
#include "graph.h"

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
    
    void on_actionImport_Teams_triggered();

    void on_actionImport_Distances_triggered();

    void on_DFSpushButton_clicked();

    void on_BFSpushButton_clicked();

    void on_MSTpushButton_clicked();

    void on_startPushButton_clicked();

private:

    //!
    //! \brief rebuildGraph recreates the graph
    //!
    void rebuildGraph();

    Ui::MainWindow *ui;

    // forms
    dbManager* database;
    databaseviewform* dbView;
    databaseNameView* dbNameView;
    logindialog* lDialog;
    Admin* adminWindow;
    tripPlanner* tripWindow;

    // contains list of team names for combo boxes
    vector<QString> nameList;
    vector<QString> tempList;
    vector<QString> selectedList;

    bool isAdmin;

    Graph<QString>* graph;
};
#endif // MAINWINDOW_H
