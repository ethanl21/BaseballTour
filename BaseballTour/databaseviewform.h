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
    //!
    //! \brief on_allTeamsButton_clicked
    //!
    //! change to window all view all teams
    //!
    void on_allTeamsButton_clicked();

    //!
    //! \brief on_leagueButton_clicked
    //!
    //! change window to view teams by league
    //!
    void on_leagueButton_clicked();

    //!
    //! \brief on_distCtrButton_clicked
    //!
    //! change window to view by distance to center field
    //!
    void on_distCtrButton_clicked();

    //!
    //! \brief on_roofTypeButton_clicked view stadiums by roof type
    //!
    void on_roofTypeButton_clicked();

private:
    Ui::databaseviewform *ui;

    // !! DO NOT delete in destructor
    dbManager* database;

    //!
    //! \brief populateAllTeamsTable
    //! \param model model of all teams, unsorted
    //!
    void populateAllTeamsTable(QSqlTableModel* model) const;

    //!
    //! \brief populateLeaguesTables
    //! \param americanTeams vector of american league teams, unsorted
    //! \param nationalTeams vector of national league teams, unsorted
    //!
    void populateLeaguesTables(const vector<teamData>& americanTeams, const vector<teamData>& nationalTeams) const;

    //!
    //! \brief populateCtrFldTables
    //! \param greatest vector of team(s) with the greatest distance to center field
    //! \param least vector of team(s) with the least distance to center field
    //!
    void populateCtrFldTables(const vector<teamData>& greatest, const vector<teamData>& least) const;

    //!
    //! \brief populateOpenRoofTeamsTable
    //! \param openRoofTeams vector of team(s) with an open roof type
    //!
    void populateOpenRoofTeamsTable(const vector<teamData>& openRoofTeams) const;
};

#endif // DATABASEVIEWFORM_H
