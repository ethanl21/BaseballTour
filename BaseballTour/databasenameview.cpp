#include "databasenameview.h"
#include "ui_databasenameview.h"
#include <QFlags>

databaseNameView::databaseNameView(dbManager* db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::databaseNameView)
{
    ui->setupUi(this);
    database = db;

    auto model = db->getTeams();

    // Populate teams combo box
    vector<QString> teamNames = db->getTeamNames();
    for(auto i : teamNames) {
        ui->teamsComboBox->addItem(i);
    }

    populateTable(model);
}

 QTableWidgetItem* databaseNameView::NewItem()
 {
    auto item = new QTableWidgetItem;
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    return item;
 }

databaseNameView::~databaseNameView()
{
    delete ui;
}

void databaseNameView::populateTable(QSqlTableModel* model) const
{
    QString columnNames[] = {"Team", "Stadium", "Stadium Capacity", "Stadium Location",
                           "Playing Surface", "League", "Stadium Date Opened", "Distance to Center Field",
                           "Stadium Typology", "Stadium Roof Type"};

    for(int i = 0; i < 10; i++) {
        model->setHeaderData(i, Qt::Horizontal, columnNames[i]);
    }


}

void databaseNameView::on_pushButton_clicked()
{
     ui->tableWidget->removeRow(0);
    QString columnNames[] = {"Team", "Stadium", "Stadium Capacity", "Stadium Location",
                           "Playing Surface", "League", "Stadium Date Opened", "Distance to Center Field",
                           "Stadium Typology", "Stadium Roof Type"};
    QString name;

    name=ui->lineEdit->text();

    QTableWidgetItem* member;


    teamData a = database->getTeamData(name);

    qDebug() << a.team_name << a.stadium_name << a.stadium_seating_capacity << a.stadium_location << a.stadium_playing_surface << a.team_league << a.stadium_date_opened << a.stadium_dist_ctrfield << a.stadium_typology << a.stadium_roof_type;


   ui->tableWidget->insertRow(0);
    member = NewItem();
    member->setData(Qt::DisplayRole,a.team_name);
    ui->tableWidget->setItem(0,0,member);
    member = NewItem();
    member->setData(Qt::DisplayRole,a.stadium_name);
    ui->tableWidget->setItem(0,1,member);
    member = NewItem();
    member->setData(Qt::DisplayRole,a.stadium_seating_capacity);
    ui->tableWidget->setItem(0,2,member);
    member = NewItem();
    member->setData(Qt::DisplayRole,a.stadium_location);
    ui->tableWidget->setItem(0,3,member);
    member = NewItem();
    member->setData(Qt::DisplayRole,a.stadium_playing_surface);
    ui->tableWidget->setItem(0,4,member);
    member = NewItem();
    member->setData(Qt::DisplayRole,a.team_league);
    ui->tableWidget->setItem(0,5,member);
    member = NewItem();
    member->setData(Qt::DisplayRole,a.stadium_date_opened);
    ui->tableWidget->setItem(0,6,member);
    member = NewItem();
    member->setData(Qt::DisplayRole,a.stadium_dist_ctrfield);
    ui->tableWidget->setItem(0,7,member);
    member = NewItem();
    member->setData(Qt::DisplayRole,a.stadium_typology);
    ui->tableWidget->setItem(0,8,member);
    member = NewItem();
    member->setData(Qt::DisplayRole,a.stadium_roof_type);
    ui->tableWidget->setItem(0,9,member);
    member = NewItem();

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    ui->lineEdit->clear();

}

void databaseNameView::on_teamsComboBox_currentIndexChanged(const QString &arg1)
{
   teamData a = database->getTeamData(arg1);

   ui->tableWidget->removeRow(0);
   QString columnNames[] = {"Team", "Stadium", "Stadium Capacity", "Stadium Location",
                          "Playing Surface", "League", "Stadium Date Opened", "Distance to Center Field",
                          "Stadium Typology", "Stadium Roof Type"};

   QTableWidgetItem* member;

   qDebug() << a.team_name << a.stadium_name << a.stadium_seating_capacity << a.stadium_location << a.stadium_playing_surface << a.team_league << a.stadium_date_opened << a.stadium_dist_ctrfield << a.stadium_typology << a.stadium_roof_type;


  ui->tableWidget->insertRow(0);
   member = NewItem();
   member->setData(Qt::DisplayRole,a.team_name);
   ui->tableWidget->setItem(0,0,member);
   member = NewItem();
   member->setData(Qt::DisplayRole,a.stadium_name);
   ui->tableWidget->setItem(0,1,member);
   member = NewItem();
   member->setData(Qt::DisplayRole,a.stadium_seating_capacity);
   ui->tableWidget->setItem(0,2,member);
   member = NewItem();
   member->setData(Qt::DisplayRole,a.stadium_location);
   ui->tableWidget->setItem(0,3,member);
   member = NewItem();
   member->setData(Qt::DisplayRole,a.stadium_playing_surface);
   ui->tableWidget->setItem(0,4,member);
   member = NewItem();
   member->setData(Qt::DisplayRole,a.team_league);
   ui->tableWidget->setItem(0,5,member);
   member = NewItem();
   member->setData(Qt::DisplayRole,a.stadium_date_opened);
   ui->tableWidget->setItem(0,6,member);
   member = NewItem();
   member->setData(Qt::DisplayRole,a.stadium_dist_ctrfield);
   ui->tableWidget->setItem(0,7,member);
   member = NewItem();
   member->setData(Qt::DisplayRole,a.stadium_typology);
   ui->tableWidget->setItem(0,8,member);
   member = NewItem();
   member->setData(Qt::DisplayRole,a.stadium_roof_type);
   ui->tableWidget->setItem(0,9,member);
   member = NewItem();

   ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}
