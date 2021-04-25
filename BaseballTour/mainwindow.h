#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "dbmanager.h"
#include "databaseviewform.h"

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

private:
    Ui::MainWindow *ui;

    dbManager* database;
    databaseviewform* dbView;
};
#endif // MAINWINDOW_H
