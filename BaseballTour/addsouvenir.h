#ifndef ADDSOUVENIR_H
#define ADDSOUVENIR_H

#include <QDialog>
#include <QSqlQuery>
#include "dbmanager.h"

namespace Ui {
class addSouvenir;
}

class addSouvenir : public QDialog
{
    Q_OBJECT

public:
    /**
    * @brief explicit default Constructor
    *
    * Constructor intializes UI for addSouvenir
    * calls fillComboBox()
    * @param *parent - for QDialog
    */
    explicit addSouvenir(dbManager* db = nullptr, QWidget *parent = nullptr);

    /**
    * @brief Destructor
    *
    * Close the addSouvenir UI
    */
    ~addSouvenir();

    /**
    * @brief Class Method to populate combo box
    *
    * updates query for starting college and sets ui Model
    */
    void fillComboBox();

private slots:
    /**
    * @brief Button Method to add new souvenir
    *
    * executes process for adding a new souvenir to database
    */
    void on_pushButton_addNewSouvenir_clicked();

    /**
    * @brief Button Method to cancel addSouvenir window
    *
    * executes process for closing addSouvenir UI window
    */
    void on_pushButton_cancelNewSouvenir_clicked();

private:
    /**
    * @brief points to addSouvenir UI
    */
    Ui::addSouvenir *ui;

    /**
    * @brief assigns DB to predefined PROJECT_PATH constant
    */
    dbManager* database;
    dbManager *m_db;
};

#endif // ADDSOUVENIR_H
