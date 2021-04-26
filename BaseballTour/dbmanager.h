#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QtSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableView>
#include <QCryptographicHash>

#include <vector>
#include <algorithm>

using namespace std;

static const QString PROJECT_PATH = "D:/Qt Projects/CS1D/BaseballTour";         // Alan's Path

class dbManager
{
public:
    //!
    //! \brief DbManager
    //! \param path - path to SQLite database
    //!
    dbManager(const QString& path);

    QSqlTableModel* getTeams() const;

    bool authenticate(const QString& username, const QString& password) const;

    void addSouvenir(const QString &college, const QString &souvenirName, const QString &cost);

    /**
    * @brief Method to remove a Souvenir
    *
    * removes a souvenir from database
    *
    * @param &souvenirName - name of souvenir
    * @param &college - name of college
    */
    void removeSouvenir(const QString &souvenirName, const QString &college);

    /**
    * @brief Method to update a Souvenir
    *
    * updates a current souvenir in database
    *
    * @param &souvenirName - name of souvenir
    * @param &college - name of college
    * @param &spin - cost of souvenir
    * @param &newsouvenir - name of new souvenir
    */
    void updateSouvenir(const QString &souvenirName, const QString &college, const QString &spin, const QString &newsouvenir);

    /**
    * @brief Method to check if souvenir exists
    *
    * checks to see if souvenir already exists in database
    *
    * @param &name - name of souvenir
    * @param &college - name of college
    */

    bool souvenirExists(const QString &name, const QString &college);

    /**
    * @brief Method to clear all colleges
    *
    * clears all colleges from database
    */
private:
    //!
    //! \brief m_db
    //! QSQLDatabase object managing the SQLite Database of campuses and souvenirs
    //!
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
