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

    //!
    //! \brief getTeamNames
    //! \return vector of team names from database
    //!
    vector<QString> getTeamNames() const;
  
    //!
    //! \brief getTeamData
    //! \param teamName name of team to return data from
    //! \return teamData struct with teamName's data or team_name "ERROR" if team not found
    //!
    teamData getTeamData(const QString& teamName) const;

    //!
    //! \brief getStadiumData
    //! \param stadium name of stadium to return data from
    //! \return teamData struct with stadium's data or team_name "ERROR" if team not found
    //!
    teamData getStadiumData(const QString& stadium) const;

    void addSouvenir(const QString &college, const QString &souvenirName, const QString &cost);

    //!
    //! \brief addTeam adds a new team from a teamData object
    //! \param newTeam - populated teamData object containing a team's data
    //!
    void addTeam(const teamData& newTeam);

    //!
    //! \brief addDist adds a distance between stadiums (edge)
    //! \param newDist obj containing edge information (origin, dest, dist)
    //!
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

    //!
    //! \brief getSouvenirs gets the souvenirs for a given stadium
    //! \param stadium stadium to return souvenirs from
    //! \return souvenir name, souvenir price vector
    //!
    vector<std::pair<QString, double>> getSouvenirs(const QString& stadium) const;

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

    void updateTeam(QString teamName, QString stadiumName, int capacity,
                        QString location,QString playingSurface,
                        QString teamLeague,int dateOpen,QString distCenterField,
                        QString typology,QString roofType);

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


    //! \brief getTeamsWithOpenRoof
    //! \param roof type to return
    //! \return vector containing team(s) with open roof type
    //!
    vector<teamData> getTeamsWithOpenRoof(const QString& roofType="Open") const;

    //!
    //! \brief getStadium
    //! \param teamName Name of team
    //! \return name of stadium
    //!
    QString getStadium(const QString& teamName) const;

    //!
    //! \brief getStadiumNames
    //! \return vector of stadium names from database
    //!
    vector<QString> getStadiumNames() const;

    //!
    //! \brief getDistances
    //! \return vector containing distances to other stadiums
    //!
    vector<distanceEdge> getDistances(const QString& teamName) const;

private:
    //!
    //! \brief m_db
    //! QSQLDatabase object managing the SQLite Database of campuses and souvenirs
    //!
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
