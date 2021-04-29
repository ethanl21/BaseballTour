#ifndef DATABASEVIEWFORM_H
#define DATABASEVIEWFORM_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlTableModel>
#include <vector>

#include "dbmanager.h"

namespace Ui {
class databaseviewform;
}

class databaseviewform : public QDialog
{
    Q_OBJECT

public:
    explicit databaseviewform(dbManager* db = nullptr, QWidget *parent = nullptr);
    ~databaseviewform();

private slots:
    void on_allTeamsButton_clicked();

    void on_leagueButton_clicked();

    void on_distCtrButton_clicked();

private:
    Ui::databaseviewform *ui;

    // !! DO NOT delete in destructor
    dbManager* database;

    void populateAllTeamsTable(QSqlTableModel* model) const;

    void populateLeaguesTables(const vector<teamData>& americanTeams, const vector<teamData>& nationalTeams) const;

    void populateCtrFldTables(const vector<teamData>& greatest, const vector<teamData>& least) const;
};

#endif // DATABASEVIEWFORM_H
