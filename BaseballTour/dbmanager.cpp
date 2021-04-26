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
    }
    else
    {
        qDebug() << "login not found.";
        return false;
    }
    return false;
}

void dbManager::removeSouvenir(const QString &souvenirName, const QString &college)
{
    QSqlQuery *query = new QSqlQuery(m_db);

    if(souvenirExists(souvenirName, college))
    {
        if(m_db.open())
        {
            query->prepare("DELETE FROM souvenirs WHERE (souvenirs) = (:souvenirs)");
            query->bindValue(":souvenirs", souvenirName);

            if(query->exec())
                qDebug() << "souvenir delete success!";
            else
                qDebug() << "souvenir delete failed!";
        }
    }

}

void dbManager::addSouvenir(const QString &college, const QString &souvenirName, const QString &cost)
{
    QSqlQuery *query = new QSqlQuery(m_db);

    if(!souvenirExists(souvenirName, college))
    {
        if(m_db.open())
        {
            query->prepare("INSERT INTO souvenirs(college, souvenirs, cost) VALUES(:college, :souvenirs, :cost)");
            query->bindValue(":college", college);
            query->bindValue(":souvenirs", souvenirName);
            query->bindValue(":cost", cost);

            if(query->exec())
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

void dbManager::updateSouvenir(const QString &souvenirName, const QString &college, const QString &spin, const QString &newsouvenir)
{
    QSqlQuery *query = new QSqlQuery(m_db);


    if(m_db.open())
    {
        query->prepare("UPDATE souvenirs SET (souvenirs, cost) = (:newsouvenirName, :cost) "
                       "WHERE (college, souvenirs) = (:college, :souvenirs)");
        query->bindValue(":newsouvenirName", newsouvenir);
        query->bindValue(":college", college);
        query->bindValue(":souvenirs", souvenirName);
        query->bindValue(":cost", spin);

        if(query->exec())
        {
            qDebug() << "UPDATE WORKED" << Qt::endl;
        }
        else
        {
            qDebug() << "UPDATE failed: " << query->lastError() << Qt::endl;
        }
    }
}

bool dbManager::souvenirExists(const QString &name, const QString &college)
{
    bool exists = false;

    QSqlQuery *checkQuery = new QSqlQuery(m_db);

    checkQuery->prepare("SELECT souvenirs FROM souvenirs WHERE (college, souvenirs) = (:college, :souvenirs)");
    checkQuery->bindValue(":souvenirs", name);
    checkQuery->bindValue(":college", college);


    if(checkQuery->exec())
    {
        if(checkQuery->next())
        {
            exists = true;
            QString souvenirName = checkQuery->value("souvenirs").toString();
            QString college = checkQuery->value("college").toString();
            qDebug() << souvenirName << " " << college;
        }
    }
    else
    {
        qDebug() << "souvenir exists failed: " << checkQuery->lastError();
    }

    return exists;
}
