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
    }else {
        qDebug() << "login not found.";
    }

    return false;
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

        qDebug() << "returning data from team: " << query.value(0).toString();

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