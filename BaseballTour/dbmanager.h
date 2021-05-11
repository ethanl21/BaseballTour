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



struct teamData {
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

struct distanceEdge {
    QString team_name_origin;
    QString team_name_destination;
    int distance;
};

class dbManager
{
public:
    //!
    //! \brief DbManager
    //! \param path - path to SQLite database
    //!
    dbManager(const QString& path);

    //!
    //! \brief getTeams
    //! \return QSqlTableModel containing all of the teams and their data
    //!
    QSqlTableModel* getTeams() const;

    //!
    //! \brief authenticate
    //! \param username - administrator username
    //! \param password - administrator password
    //! \return true if username and password are correct
    //!
    bool authenticate(const QString& username, const QString& password) const;

    vector<QString> getTeamNames() const;
  
    //!
    //! \brief getTeamData
    //! \param teamName name of team to return data from
    //! \return teamData struct with teamName's data or team_name "ERROR" if team not found
    //!
    teamData getTeamData(const QString& teamName) const;

    void addSouvenir(const QString &college, const QString &souvenirName, const QString &cost);

    void addTeam(const teamData& newTeam);

    void addDist(const distanceEdge& newDist);

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

    //!
    //! \brief getTeamsByLeague
    //! \param league American or National
    //! \return vector of teams and stadiums according to the league given
    //!
    vector<teamData> getTeamsByLeague(const QString& league="American") const;

    //!
    //! \brief getTeamsByCtrField
    //! \return vector containing team(s) with largest dist to center field
    //!
    vector<teamData> getTeamsByMaxCtrField() const;

    //!
    //! \brief getTeamsByCtrField
    //! \return vector containing team(s) with smallest dist to center field
    //!
    vector<teamData> getTeamsByMinCtrField() const;

    //!
    //! \brief getTeamsWithOpenRoof
    //! \param roof type to return
    //! \return vector containing team(s) with open roof type
    //!
    vector<teamData> getTeamsWithOpenRoof(const QString& roofType="Open") const;

private:
    //!
    //! \brief m_db
    //! QSQLDatabase object managing the SQLite Database of campuses and souvenirs
    //!
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
