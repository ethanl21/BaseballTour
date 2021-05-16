#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
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

    /**
    * @brief Button Method to take input from admin and update team
    *
    * executes process for changing team data according to what
    * the admin input
    */
    void on_pushButton_clicked();

    /**
    * @brief Method to fill the input options with info
    * of team
    *
    * fills the input boxes with team info
    * of currently selected team
    *
    * @param &teamName - name of currently selected team
    * in the combo box
    */
    void populateInformation(const QString& teamName);

    /**
    * @brief Combo box option selected method to fill input
    * with team data when option selected
    *
    * calls populateInformation method in order to fill input
    * with team data
    *
    * @param &arg1 - current name of team selected that is
    * passed into populateInformation method
    */
    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::Admin *ui;
    dbManager* database;
    dbManager *m_db;
    QString tempSouvenir;
    vector<QString> nameList;
    vector<QString> tempList;
};

#endif // ADMIN_H
