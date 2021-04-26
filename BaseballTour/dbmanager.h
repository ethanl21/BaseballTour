#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableView>
#include <QCryptographicHash>

#include <vector>
#include <algorithm>

using namespace std;

struct teamData
{
    QString team_name;
    QString stadium_name;
    int stadium_seating_capacity;
    QString stadium_location;
    QString stadium_playing_surface;
    QString team_league;
    int stadium_date_opened;
    QString stadium_dist_ctrfield;
    QString stadium_typology;
    QString stadium_roof_type;
};


class dbManager
{
public:
    //!
    //! \brief DbManager
    //! \param path - path to SQLite database
    //!
    dbManager(const QString& path);

    QSqlTableModel* getTeams() const;

    teamData getTeamData(const QString& teamName) const;

    bool authenticate(const QString& username, const QString& password) const;

    vector<QString> getTeamNames() const;

private:
    //!
    //! \brief m_db
    //! QSQLDatabase object managing the SQLite Database of campuses and souvenirs
    //!
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
