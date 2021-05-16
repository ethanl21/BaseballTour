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
        team.team_name = query.value(0).toString();
        team.stadium_name = query.value(1).toString();
        team.stadium_seating_capacity = query.value(2).toInt();
        team.stadium_location = query.value(3).toString();
        team.stadium_playing_surface = query.value(4).toString();
        team.team_league = query.value(5).toString();
        team.stadium_date_opened = query.value(6).toInt();
        team.stadium_dist_ctrfield = query.value(7).toString();
        team.stadium_typology = query.value(8).toString();
        team.stadium_roof_type = query.value(9).toString();
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

    // query database for team names
    QSqlQuery query("SELECT DISTINCT team_name FROM teams");

     // add campus names to vector (unique)
    while(query.next()) {
        QString out = query.value(0).toString();
        teams.push_back(out);
    }

    return teams;
}


void dbManager::removeSouvenir(const QString &souvenirName, const QString &teamName)
{
    QSqlQuery query;

    if(souvenirExists(souvenirName, teamName))
    {
        if(m_db.open())
        {
            query.prepare("DELETE FROM Souvenirs WHERE (Souvenirs, Teams) = (:souvenirs, :teamName)");
            query.bindValue(":souvenirs", souvenirName);
            query.bindValue(":teamName", teamName);

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
    qDebug() << "Adding souvenir debug";

    if(!souvenirExists(souvenirName, team))
    {
        qDebug() << "Souvenir doesn't exist.";

        qDebug() << "Database is open";
        qDebug() << "Team: " << team << " Souvenir: " << souvenirName << " Cost: " << cost;

        query.prepare("INSERT INTO Souvenirs(Teams, Souvenirs, Cost) VALUES(:team, :souvenirs, :cost)");
        query.bindValue(":team", team);
        query.bindValue(":souvenirs", souvenirName);
        query.bindValue(":cost", cost);

        if(query.exec())
            qDebug() << "souvenir add success!";
        else
            qDebug() << "souvenir add failed!";
    }
    else
    {
        qDebug() << "name exists!";
    }
}

void dbManager::updateSouvenir(const QString &souvenirName, const QString &team, const QString &newCost, const QString &newsouvenir)
{
    QSqlQuery query;


    if(m_db.open())
    {
        query.prepare("UPDATE Souvenirs SET (Souvenirs, Cost) = (:newSouvenir, :newCost)"
            "WHERE (teams, souvenirs) = (:team, :souvenirs)");
        query.bindValue(":souvenirs", souvenirName);
        query.bindValue(":team", team);
        query.bindValue(":newSouvenir", newsouvenir);
        query.bindValue(":newCost", newCost);

        qDebug() << souvenirName;
        qDebug() << newCost;
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

void dbManager::addTeam(const teamData &newTeam)
{
    QSqlQuery query;

    query.prepare("INSERT INTO teams VALUES(:teamname, :stadname, :stadiumcap, :location, :playsurface, :league, :dateopened, :distctr, :typology, :rooftype)");
    query.bindValue(":teamname", newTeam.team_name);
    query.bindValue(":stadname", newTeam.stadium_name);
    query.bindValue(":stadiumcap", newTeam.stadium_seating_capacity);
    query.bindValue(":location", newTeam.stadium_location);
    query.bindValue(":playsurface", newTeam.stadium_playing_surface);
    query.bindValue(":league", newTeam.team_league);
    query.bindValue(":dateopened", newTeam.stadium_date_opened);
    query.bindValue(":distctr", newTeam.stadium_dist_ctrfield);
    query.bindValue(":typology", newTeam.stadium_typology);
    query.bindValue(":rooftype", newTeam.stadium_roof_type);

    if(query.exec()) {
        qDebug() << "added:" << newTeam.team_name;
    } else {
        qDebug() << "could not add:" << newTeam.team_name;
    }

}

void dbManager::addDist(const distanceEdge &newDist)
{
    QSqlQuery query;
    int rowCount;

    query.prepare("SELECT Count(*) FROM distances");

    if(query.exec()) {
        query.first();
        qDebug() << "row count:" << query.value(0).toInt();
    }else {
        qDebug() << "could not get count:" << query.lastError();
    }
    rowCount = query.value(0).toInt();

    query.prepare("INSERT INTO distances VALUES(:id, :origin, :dest, :dist)");
    query.bindValue(":id", rowCount);
    query.bindValue(":origin", newDist.team_name_origin);
    query.bindValue(":dest", newDist.team_name_destination);
    query.bindValue(":dist", newDist.distance);

    if(query.exec()) {
        qDebug() << "added:" << newDist.team_name_origin << "to" << newDist.team_name_destination;
    } else {
        qDebug() << "could not add:" << newDist.team_name_origin << "to" << newDist.team_name_destination;
        qDebug() << "reason:" << query.lastError();
    }
}

void dbManager::updateTeam(QString teamName, QString stadiumName, int capacity,
                           QString location,QString playingSurface,
                           QString teamLeague,int dateOpen,QString distCenterField,
                           QString typology,QString roofType)
{

    QSqlQuery query;

    query.prepare("UPDATE teams SET stadium_name=:stadiumName WHERE team_name=:teamName");
    query.bindValue(":teamName",teamName);
    query.bindValue(":stadiumName",stadiumName);
    query.exec();

    query.prepare("UPDATE teams SET stadium_seating_capacity=:stadiumSeatingCapacity WHERE team_name=:teamName");
    query.bindValue(":teamName",teamName);
    query.bindValue(":stadiumSeatingCapacity",capacity);
    query.exec();

    query.prepare("UPDATE teams SET stadium_location=:stadiumLocation WHERE team_name=:teamName");
    query.bindValue(":teamName",teamName);
    query.bindValue(":stadiumLocation",location);
    query.exec();

    query.prepare("UPDATE teams SET stadium_playing_surface=:stadiumPlayingSurface WHERE team_name=:teamName");
    query.bindValue(":teamName",teamName);
    query.bindValue(":stadiumPlayingSurface",playingSurface);
    query.exec();

    query.prepare("UPDATE teams SET team_league=:teamLeague WHERE team_name=:teamName");
    query.bindValue(":teamName",teamName);
    query.bindValue(":teamLeague",teamLeague);
    query.exec();

    query.prepare("UPDATE teams SET stadium_date_opened=:dateOpen WHERE team_name=:teamName");
    query.bindValue(":teamName",teamName);
    query.bindValue(":dateOpen",dateOpen);
    query.exec();

    query.prepare("UPDATE teams SET stadium_dist_ctrfield=:distCenterField WHERE team_name=:teamName");
    query.bindValue(":teamName",teamName);
    query.bindValue(":distCenterField",distCenterField);
    query.exec();

    query.prepare("UPDATE teams SET stadium_typology=:typology WHERE team_name=:teamName");
    query.bindValue(":teamName",teamName);
    query.bindValue(":typology",typology);
    query.exec();

    query.prepare("UPDATE teams SET stadium_rooftype=:roofType WHERE team_name=:teamName");
    query.bindValue(":teamName",teamName);
    query.bindValue(":roofType",roofType);
    query.exec();


    if(query.exec())
    {
        qDebug() << "UPDATE WORKED" << Qt::endl;
    }
    else
    {
        qDebug() << "UPDATE failed: " << query.lastError() << Qt::endl;
        qDebug() << query.executedQuery();
        qDebug() << query.boundValues();
    }
}

bool dbManager::souvenirExists(const QString &name, const QString &teams)
{
    bool exists = false;

    QSqlQuery checkQuery;

    checkQuery.prepare("SELECT souvenirs FROM souvenirs WHERE (teams, souvenirs) = (:teams, :souvenirs)");
    checkQuery.bindValue(":souvenirs", name);
    checkQuery.bindValue(":teams", teams);


    if(checkQuery.exec())
    {
        if(checkQuery.next())
        {
            exists = true;
            QString souvenirName = checkQuery.value("souvenirs").toString();
            QString teamName = checkQuery.value("teams").toString();
            qDebug() << souvenirName << " " << teamName;
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

QString dbManager::getStadium(const QString& teamName) const
{
    QString stadiumName;
    QSqlQuery query;
    query.prepare("SELECT stadium_name FROM teams WHERE team_name=:teamName");
    query.bindValue(":teamName", teamName);
    query.exec();

    query.first();

    return query.value(0).toString();
}

vector<QString> dbManager::getStadiumNames() const
{
    vector<QString> stadiums;

    // query database for names
    QSqlQuery query("SELECT DISTINCT origin FROM distances");

    while(query.next()) {
        QString out = query.value(0).toString();
        stadiums.push_back(out);
    }

    return stadiums;
}

vector<distanceEdge> dbManager::getDistances(const QString& teamName) const
{
    QSqlQuery query;
    vector<distanceEdge> distances;
    distanceEdge edge;
    query.prepare("SELECT destination, distance FROM distances WHERE origin=:origin");
    query.bindValue(":origin", teamName);
    query.exec();

    query.first();
    edge.team_name_origin = teamName;
    while (query.isValid()) {
        edge.team_name_destination = query.value(0).toString();
        edge.distance = query.value(1).toInt();
        distances.push_back(edge);

        query.next();
    }

    return distances;
}
