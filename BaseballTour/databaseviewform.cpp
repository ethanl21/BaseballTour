#include "databaseviewform.h"
#include "ui_databaseviewform.h"

databaseviewform::databaseviewform(dbManager* db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::databaseviewform)
{
    ui->setupUi(this);
    database = db;

    auto model = db->getTeams();
    populateTable(model);

    ui->dbViewStack->setCurrentIndex(0);
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
