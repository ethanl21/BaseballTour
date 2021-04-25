#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableView>

#include <vector>
#include <algorithm>

using namespace std;


class dbManager
{
public:
    //!
    //! \brief DbManager
    //! \param path - path to SQLite database
    //!
    dbManager(const QString& path);

    QSqlTableModel* getTeams() const;

private:
    //!
    //! \brief m_db
    //! QSQLDatabase object managing the SQLite Database of campuses and souvenirs
    //!
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
