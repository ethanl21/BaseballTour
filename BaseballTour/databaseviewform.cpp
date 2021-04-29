#include "databaseviewform.h"
#include "ui_databaseviewform.h"

databaseviewform::databaseviewform(dbManager* db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::databaseviewform)
{
    ui->setupUi(this);
    database = db;

    // start on all teams
    ui->dbViewStack->setCurrentIndex(0);

    // view all teams
    populateAllTeamsTable(db->getTeams());

    // view by league
    populateLeaguesTables(db->getTeamsByLeague("American"), db->getTeamsByLeague("National"));


}

databaseviewform::~databaseviewform()
{
    delete ui;
}

void databaseviewform::populateAllTeamsTable(QSqlTableModel* model) const
{
    QString columnNames[] = {"Team", "Stadium", "Stadium Capacity", "Stadium Location",
                           "Playing Surface", "League", "Stadium Date Opened", "Distance to Center Field",
                           "Stadium Typology", "Stadium Roof Type"};

    for(int i = 0; i < 10; i++) {
        model->setHeaderData(i, Qt::Horizontal, columnNames[i]);
    }

    ui->teamviewModel->setModel(model);
}

void databaseviewform::populateLeaguesTables(const vector<teamData>& americanTeams, const vector<teamData>& nationalTeams) const
{
    // table headers
    QStringList headerLabels;
    headerLabels.append("Team");
    headerLabels.append("Stadium");

    // set up table ui parameters
    ui->americanTeamsTableWidget->setColumnCount(2);
    ui->americanTeamsTableWidget->setHorizontalHeaderLabels(headerLabels);
    ui->americanTeamsTableWidget->setColumnWidth(0, 220);
    ui->americanTeamsTableWidget->setColumnWidth(1, 255);

    ui->nationalTeamsTableWidget->setColumnCount(2);
    ui->nationalTeamsTableWidget->setHorizontalHeaderLabels(headerLabels);
    ui->nationalTeamsTableWidget->setColumnWidth(0, 220);
    ui->nationalTeamsTableWidget->setColumnWidth(1, 255);

    // populate the tables
    for(const auto &i : americanTeams) {
        ui->americanTeamsTableWidget->insertRow(ui->americanTeamsTableWidget->rowCount());

        // row, column, item
        ui->americanTeamsTableWidget->setItem(ui->americanTeamsTableWidget->rowCount()-1, 0, new QTableWidgetItem(i.team_name));
        ui->americanTeamsTableWidget->setItem(ui->americanTeamsTableWidget->rowCount()-1, 1, new QTableWidgetItem(i.stadium_name));
    }

    for(const auto &i : nationalTeams) {
        ui->nationalTeamsTableWidget->insertRow(ui->nationalTeamsTableWidget->rowCount());

        // row, column, item
        ui->nationalTeamsTableWidget->setItem(ui->nationalTeamsTableWidget->rowCount()-1, 0, new QTableWidgetItem(i.team_name));
        ui->nationalTeamsTableWidget->setItem(ui->nationalTeamsTableWidget->rowCount()-1, 1, new QTableWidgetItem(i.stadium_name));
    }

    // sort the rows by name
    ui->nationalTeamsTableWidget->sortItems(0);
    ui->americanTeamsTableWidget->sortItems(0);
}

void databaseviewform::on_allTeamsButton_clicked()
{
    // change to the all teams tab
    ui->dbViewStack->setCurrentIndex(0);
}

void databaseviewform::on_leagueButton_clicked()
{
    // change to the leagues tab
    ui->dbViewStack->setCurrentIndex(1);
}
