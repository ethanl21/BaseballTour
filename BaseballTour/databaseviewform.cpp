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
    auto model = db->getTeams();
    populateTable(model);

    // populate american teams tab
    QStringList headerLabels;
    headerLabels.append("Team");
    headerLabels.append("Stadium");

    ui->americanTeamsTableWidget->setColumnCount(2);
    ui->americanTeamsTableWidget->setHorizontalHeaderLabels(headerLabels);
    ui->americanTeamsTableWidget->setColumnWidth(0, 200);
    ui->americanTeamsTableWidget->setColumnWidth(1, 200);

    vector<teamData> americanTeams = db->getTeamsByLeague("American");
    for(auto i : americanTeams) {
        ui->americanTeamsTableWidget->insertRow(ui->americanTeamsTableWidget->rowCount());

        // row, column, item
        ui->americanTeamsTableWidget->setItem(ui->americanTeamsTableWidget->rowCount()-1, 0, new QTableWidgetItem(i.team_name));
        ui->americanTeamsTableWidget->setItem(ui->americanTeamsTableWidget->rowCount()-1, 1, new QTableWidgetItem(i.stadium_name));
    }

    // sort the rows by name
    ui->americanTeamsTableWidget->sortItems(0);

    // populate national teams tab
    ui->nationalTeamsTableWidget->setColumnCount(2);
    ui->nationalTeamsTableWidget->setHorizontalHeaderLabels(headerLabels);
    ui->nationalTeamsTableWidget->setColumnWidth(0, 200);
    ui->nationalTeamsTableWidget->setColumnWidth(1, 200);

    vector<teamData> nationalTeams = db->getTeamsByLeague("National");
    for(auto i : nationalTeams) {
        ui->nationalTeamsTableWidget->insertRow(ui->nationalTeamsTableWidget->rowCount());

        // row, column, item
        ui->nationalTeamsTableWidget->setItem(ui->nationalTeamsTableWidget->rowCount()-1, 0, new QTableWidgetItem(i.team_name));
        ui->nationalTeamsTableWidget->setItem(ui->nationalTeamsTableWidget->rowCount()-1, 1, new QTableWidgetItem(i.stadium_name));
    }

    // sort the rows by name
    ui->nationalTeamsTableWidget->sortItems(0);


}

databaseviewform::~databaseviewform()
{
    delete ui;
}

void databaseviewform::populateTable(QSqlTableModel* model) const
{
    QString columnNames[] = {"Team", "Stadium", "Stadium Capacity", "Stadium Location",
                           "Playing Surface", "League", "Stadium Date Opened", "Distance to Center Field",
                           "Stadium Typology", "Stadium Roof Type"};

    for(int i = 0; i < 10; i++) {
        model->setHeaderData(i, Qt::Horizontal, columnNames[i]);
    }

    ui->teamviewModel->setModel(model);
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
