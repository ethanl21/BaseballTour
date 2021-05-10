#include "dbmanager.h"

dbManager::dbManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if(!m_db.open()) {
        qDebug() << "Error: could not connect to database.";
    }else {
        qDebug() << "Database connection OK";
    }
}

QSqlTableModel* dbManager::getTeams() const
{
    QSqlTableModel* model = new QSqlTableModel;

    model->setTable("teams");
    model->select();

    model->removeColumn(0);

    return model;
}

teamData dbManager::getTeamData(const QString& teamName) const
{
    teamData team;
    QSqlQuery query;

    query.prepare("SELECT * FROM teams WHERE team_name=:teamname");
    query.bindValue(":teamname", teamName);

    query.exec();
    query.first();

    if(query.isValid()) { // if matching team found
        team.team_name = query.value(1).toString();
        team.stadium_name = query.value(2).toString();
        team.stadium_seating_capacity = query.value(3).toInt();
        team.stadium_location = query.value(4).toString();
        team.stadium_playing_surface = query.value(5).toString();
        team.team_league = query.value(6).toString();
        team.stadium_date_opened = query.value(7).toInt();
        team.stadium_dist_ctrfield = query.value(8).toString();
        team.stadium_typology = query.value(9).toString();
        team.stadium_roof_type = query.value(10).toString();
    }else {
        qDebug() << "team not found";
        team.team_name = "ERROR";
    }

    return team;
}

bool dbManager::authenticate(const QString& username, const QString& password) const
{
    QSqlQuery query;

    // look for username match
    query.prepare("SELECT * FROM login WHERE username=:usr");
    query.bindValue(":usr", username);
    query.exec();
    query.first();

    // if a matching username is found, compare password hash
    if(query.isValid()) {

        qDebug() << "Returned login from db: " << query.value(0).toString() << query.value(1).toString();

        auto inputHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256); // calculate sha256 hash
        QString inputHashStr = QString(inputHash.toHex());

        qDebug() << "Comparing against:" << username << inputHashStr;

        if(inputHashStr.toUpper() == (query.value(1).toString()).toUpper()) { // if passwords match (case insensitive)
            return true;
        }
    }
    else
    {
        qDebug() << "login not found.";
        return false;
    }
    return false;
}


vector<QString> dbManager::getTeamNames() const
{
    vector<QString> teams;

    // query database for campus names
    QSqlQuery query("SELECT DISTINCT team_name FROM teams");

     // add campus names to vector (unique)
    while(query.next()) {
        QString out = query.value(0).toString();
        teams.push_back(out);
    }

    return teams;
}


void dbManager::removeSouvenir(const QString &souvenirName, const QString &college)
{
    QSqlQuery query;

    if(souvenirExists(souvenirName, college))
    {
        if(m_db.open())
        {
            query.prepare("DELETE FROM souvenirs WHERE (souvenirs) = (:souvenirs)");
            query.bindValue(":souvenirs", souvenirName);

            if(query.exec())
                qDebug() << "souvenir delete success!";
            else
                qDebug() << "souvenir delete failed!";
        }
    }

}

void dbManager::addSouvenir(const QString &team, const QString &souvenirName, const QString &cost)
{
    QSqlQuery query;

    if(!souvenirExists(souvenirName, team))
    {
        if(m_db.open())
        {
            query.prepare("INSERT INTO souvenirs(college, souvenirs, cost) VALUES(:team, :souvenirs, :cost)");
            query.bindValue(":team", team);
            query.bindValue(":souvenirs", souvenirName);
            query.bindValue(":cost", cost);

            if(query.exec())
                qDebug() << "souvenir add success!";
            else
                qDebug() << "souvenir add failed!";
        }
    }
    else
    {
        qDebug() << "name exists!";
    }
}

void dbManager::updateSouvenir(const QString &souvenirName, const QString &team, const QString &spin, const QString &newsouvenir)
{
    QSqlQuery query;


    if(m_db.open())
    {
        query.prepare("UPDATE souvenirs SET (souvenirs, cost) = (:newsouvenirName, :cost) "
                       "WHERE (team, souvenirs) = (:team, :souvenirs)");
        query.bindValue(":newsouvenirName", newsouvenir);
        query.bindValue(":team", team);
        query.bindValue(":souvenirs", souvenirName);
        query.bindValue(":cost", spin);

        if(query.exec())
        {
            qDebug() << "UPDATE WORKED" << Qt::endl;
        }
        else
        {
            qDebug() << "UPDATE failed: " << query.lastError() << Qt::endl;
        }
    }
}

bool dbManager::souvenirExists(const QString &name, const QString &team)
{
    bool exists = false;

    QSqlQuery checkQuery;

    checkQuery.prepare("SELECT souvenirs FROM souvenirs WHERE (team, souvenirs) = (:team, :souvenirs)");
    checkQuery.bindValue(":souvenirs", name);
    checkQuery.bindValue(":team", team);


    if(checkQuery.exec())
    {
        if(checkQuery.next())
        {
            exists = true;
            QString souvenirName = checkQuery.value("souvenirs").toString();
            QString college = checkQuery.value("team").toString();
            qDebug() << souvenirName << " " << college;
        }
    }
    else
    {
        qDebug() << "souvenir exists failed: " << checkQuery.lastError();
    }

    return exists;
}

vector<teamData> dbManager::getTeamsByLeague(const QString& league) const
{
    QSqlQuery query;
    vector<teamData> teams;
    teamData temp;

    query.prepare("SELECT team_name, stadium_name FROM teams WHERE team_league = :league");
    query.bindValue(":league", league); // league defaults to "American"

    query.exec();
    query.first();

    while(query.isValid()) {
        temp.team_name = query.value(0).toString();
        temp.stadium_name = query.value(1).toString();

        teams.push_back(temp);

        query.next();
    }

//    // sort the teams alphabetically by name
//    sort(teams.begin(), teams.end(),
//         [] (teamData a, teamData b)
//    { return (a.team_name < b.team_name); }
//    );

    return teams;
}

vector<teamData> dbManager::getTeamsByMaxCtrField() const
{
    QSqlQuery query;
    teamData temp;
    vector<teamData> teams;

    qDebug() << "getTeamsByMaxCtrField";

    query.prepare("SELECT team_name, stadium_name, MAX(stadium_dist_ctrfield) FROM teams");
    query.exec();

    query.first();
    while(query.isValid()) {
        temp.team_name = query.value(0).toString();
        temp.stadium_name = query.value(1).toString();
        temp.stadium_dist_ctrfield = query.value(2).toString();

        teams.push_back(temp);

        query.next();
    }

    return teams;
}

vector<teamData> dbManager::getTeamsByMinCtrField() const
{
    QSqlQuery query;
    teamData temp;
    vector<teamData> teams;

    qDebug() << "getTeamsByMinCtrField";

    query.prepare("SELECT team_name, stadium_name, MIN(stadium_dist_ctrfield) FROM teams");
    query.exec();

    query.first();
    while(query.isValid()) {
        qDebug() << "Query is valid";
        temp.team_name = query.value(0).toString();
        temp.stadium_name = query.value(1).toString();
        temp.stadium_dist_ctrfield = query.value(2).toString();

        teams.push_back(temp);

        query.next();
    }

    return teams;
}

vector<teamData> dbManager::getTeamsWithOpenRoof(const QString& roofType) const
{
    QSqlQuery query;
    vector<teamData> teams;
    teamData team;
    query.prepare("SELECT team_name, stadium_name FROM teams WHERE stadium_rooftype =:roofType");
    query.bindValue(":roofType", roofType);
    query.exec();

    qDebug() << "getTeamsWithOpenRoof";

    query.first();
    while(query.isValid()) {
        team.team_name = query.value(0).toString();
        team.stadium_name = query.value(1).toString();
        teams.push_back(team);

        query.next();
    }


    return teams;
}
