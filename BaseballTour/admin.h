#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include <QSqlDatabase>
#include "dbmanager.h"

namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT

public:
    explicit Admin(dbManager* db = nullptr, QWidget *parent = nullptr);
    ~Admin();

    /**
    * @brief Class Method to update souvenirs
    *
    * updates query for entire Souvenirs chart and sets ui Model
    */
    void updateSouvenirs();

private slots:

    //QSqlDatabase m_db;

    /**
    * @brief Button Method to update a souvenir
    *
    * executes process for updating a souvenir in database
    */
    void on_pushButton_updateSouvenir_clicked();

    /**
    * @brief Button Method to remove a souvenir
    *
    * executes process for removing a souvenir from database
    */
    void on_pushButton_removeSouvenir_clicked();

    /**
    * @brief Table Clicked Method to update a souvenir
    *
    * executes process for making souvenir table clickable
    * sets value for UI elements based off information from souvenir table
    *
    * @param &index - model index from chart
    */
    void on_souvenir_tableView_clicked(const QModelIndex &index);

//    /**
//    * @brief Button Method to show addSouvenir UI window
//    *
//    * calls constructor for addSouvenir UI window
//    * opens addSouvenir UI window
//    */
//    void on_pushButton_addSouvenir_clicked();

    void on_pushButton_clicked();

private:
    Ui::Admin *ui;
    dbManager* database;
    dbManager *m_db;
    QString tempSouvenir;
    vector<QString> nameList;
    vector<QString> tempList;
};

#endif // ADMIN_H
