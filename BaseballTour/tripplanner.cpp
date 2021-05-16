#include "tripplanner.h"
#include "ui_tripplanner.h"

tripPlanner::tripPlanner(vector<QString> stadiums, dbManager *dbase, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tripPlanner)
{
    ui->setupUi(this);
    db = dbase;
    stadiumNames = stadiums;


    // populate the stadium information on init
    //on_teamsroute_listWidget_currentTextChanged(stadiumNames[0]);
    on_teamsroute_listWidget_currentTextChanged("Arizona Diamondbacks");

    for(const auto &stadium : stadiumNames) {
        ui->teamsroute_listWidget->addItem(stadium);
    }

    ui->teamsroute_listWidget->setCurrentRow(0);


    totalSpent = 0.0;
}

tripPlanner::~tripPlanner()
{
    delete ui;
}

void tripPlanner::on_teamsroute_listWidget_currentTextChanged(const QString &currentText)
{
    teamData a = db->getTeamData(currentText);

    //qDebug() << a.team_name << a.stadium_name << a.stadium_seating_capacity << a.stadium_location << a.stadium_playing_surface << a.team_league << a.stadium_date_opened << a.stadium_dist_ctrfield << a.stadium_typology << a.stadium_roof_type;

     ui->teamLineEdit->setText(a.team_name);
     ui->stadiumNameLineEdit->setText(a.stadium_name);
     ui->stadiumCapacityLineEdit->setText(QString::number(a.stadium_seating_capacity));
     ui->stadiumLocationLineEdit->setText(a.stadium_location);
     ui->stadiumPlayingSurfaceLineEdit->setText(a.stadium_playing_surface);
     ui->leagueLineEdit->setText(a.team_league);
     ui->dateOpenedLineEdit->setText(QString::number(a.stadium_date_opened));
     ui->distCtrFieldLineEdit->setText(a.stadium_dist_ctrfield);
     ui->typologyLineEdit->setText(a.stadium_typology);
     ui->roofTypeLineEdit->setText(a.stadium_roof_type);
}

void tripPlanner::on_pushButton_clicked()
{
    shoppingCartWindow = new PurchaseSouvenirs(ui->teamsroute_listWidget->currentItem()->text(), db);

    shoppingCartWindow->exec();

    totalSpent += shoppingCartWindow->amountSpent(); // 0 if purchase rejected

    for(const auto &i : shoppingCartWindow->getShoppingCart()) {
        shoppingCart.push_back(i);
    }

    delete shoppingCartWindow;
}

void tripPlanner::on_cancelTripButton_clicked()
{
    this->close();
}

void tripPlanner::on_endTripButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
