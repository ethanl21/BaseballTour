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

    // view by center field
    populateCtrFldTables(db->getTeamsByMaxCtrField(), db->getTeamsByMinCtrField());

    // view teams with open roof
    populateOpenRoofTeamsTable(db->getTeamsWithOpenRoof("Open"));

    ui->totalCapacitySpinBox->setValue(db->calcTotalCapacity());

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

    ui->teamviewModel->setColumnWidth(0, 225);
    ui->teamviewModel->setColumnWidth(1, 200);
    ui->teamviewModel->setColumnWidth(2, 75);
    ui->teamviewModel->setColumnWidth(3, 225);
    ui->teamviewModel->setColumnWidth(6, 75);
    ui->teamviewModel->setColumnWidth(7, 150);
    ui->teamviewModel->setColumnWidth(8, 150);

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

void databaseviewform::on_roofTypeButton_clicked()
{
    // change to the roof type tab
    ui->dbViewStack->setCurrentIndex(2);
}

void databaseviewform::on_distCtrButton_clicked()
{
    // change to the dist ctr fld tab
    ui->dbViewStack->setCurrentIndex(3);
}

void databaseviewform::populateCtrFldTables(const vector<teamData>& greatest, const vector<teamData>& least) const
{
    // set table headers
    QStringList labels;
    labels.append("Team");
    labels.append("Stadium");
    labels.append("Distance to Center Field");

    qDebug() << "populateCtrFldTables";

    // set up table ui parameters
    ui->greatestCenterFldWidget->setColumnCount(3);
    ui->greatestCenterFldWidget->setHorizontalHeaderLabels(labels);
    ui->greatestCenterFldWidget->setColumnWidth(0, 350);
    ui->greatestCenterFldWidget->setColumnWidth(1, 350);
    ui->greatestCenterFldWidget->setColumnWidth(2, 340);

    ui->leastCenterFldWidget->setColumnCount(3);
    ui->leastCenterFldWidget->setHorizontalHeaderLabels(labels);
    ui->leastCenterFldWidget->setColumnWidth(0, 350);
    ui->leastCenterFldWidget->setColumnWidth(1, 350);
    ui->leastCenterFldWidget->setColumnWidth(2, 340);

    for(const auto &i : greatest) {
        ui->greatestCenterFldWidget->insertRow(ui->greatestCenterFldWidget->rowCount());

        // row, column, item
        ui->greatestCenterFldWidget->setItem(ui->greatestCenterFldWidget->rowCount()-1, 0, new QTableWidgetItem(i.team_name));
        ui->greatestCenterFldWidget->setItem(ui->greatestCenterFldWidget->rowCount()-1, 1, new QTableWidgetItem(i.stadium_name));
        ui->greatestCenterFldWidget->setItem(ui->greatestCenterFldWidget->rowCount()-1, 2, new QTableWidgetItem(i.stadium_dist_ctrfield));
    }

    for(const auto &i : least) {
        ui->leastCenterFldWidget->insertRow(ui->leastCenterFldWidget->rowCount());

        // row, column, item
        ui->leastCenterFldWidget->setItem(ui->leastCenterFldWidget->rowCount()-1, 0, new QTableWidgetItem(i.team_name));
        ui->leastCenterFldWidget->setItem(ui->leastCenterFldWidget->rowCount()-1, 1, new QTableWidgetItem(i.stadium_name));
        ui->leastCenterFldWidget->setItem(ui->leastCenterFldWidget->rowCount()-1, 2, new QTableWidgetItem(i.stadium_dist_ctrfield));
    }

    // only sort if there's more than one team for greatest or least dist to ctr fld
    if(greatest.size() > 1) {
        ui->greatestCenterFldWidget->sortItems(0);
    }

    if(least.size() > 1) {
        ui->leastCenterFldWidget->sortItems(0);
    }

}

void databaseviewform::populateOpenRoofTeamsTable(const vector<teamData>& openRoofTeams) const
{
    QStringList label;
    label.append("Teams");
    ui->openRoofTeamsTableWidget->setColumnCount(1);
    ui->openRoofTeamsTableWidget->setHorizontalHeaderLabels(label);
    ui->openRoofTeamsTableWidget->setColumnWidth(0,350);

    //qDebug() << openRoofTeams[0].team_name;
    for(const auto &i : openRoofTeams) {
        ui->openRoofTeamsTableWidget->insertRow(ui->openRoofTeamsTableWidget->rowCount());

        // row, column, item
        ui->openRoofTeamsTableWidget->setItem(ui->openRoofTeamsTableWidget->rowCount()-1, 0, new QTableWidgetItem(i.team_name));

    }

    ui->label_8->setText(QString::number(openRoofTeams.size()));
}
