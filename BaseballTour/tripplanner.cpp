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
        ui->stadiumComboBox->addItem(stadium);
    }

    ui->teamsroute_listWidget->setCurrentRow(0);
    ui->souvenirsPurchasedTableWidget->setHorizontalHeaderLabels(QStringList{"Stadium", "Souvenir", "Qty", "Price"});
    ui->souvenirsPurchasedTableWidget_2->setHorizontalHeaderLabels(QStringList{"Souvenir", "Qty", "Price"});

    ui->souvenirsPurchasedTableWidget->setColumnWidth(0, 250);
    ui->souvenirsPurchasedTableWidget->setColumnWidth(1, 200);

    ui->souvenirsPurchasedTableWidget_2->setColumnWidth(1, 200);
    ui->souvenirsPurchasedTableWidget_2->setColumnWidth(0, 250);

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
    ui->totalPriceSpinBox->setValue(totalSpent);

    for(const auto&i : shoppingCart) {

        ui->souvenirsPurchasedTableWidget->insertRow(ui->souvenirsPurchasedTableWidget->rowCount());
        ui->souvenirsPurchasedTableWidget->setItem(ui->souvenirsPurchasedTableWidget->rowCount()-1, 0, new QTableWidgetItem(std::get<0>(i)));
        ui->souvenirsPurchasedTableWidget->setItem(ui->souvenirsPurchasedTableWidget->rowCount()-1, 1, new QTableWidgetItem(std::get<1>(i)));
        ui->souvenirsPurchasedTableWidget->setItem(ui->souvenirsPurchasedTableWidget->rowCount()-1, 2, new QTableWidgetItem(QString::number(std::get<2>(i))));
        ui->souvenirsPurchasedTableWidget->setItem(ui->souvenirsPurchasedTableWidget->rowCount()-1, 3, new QTableWidgetItem(QString::number(std::get<3>(i))));

    }

    on_stadiumComboBox_currentIndexChanged(ui->stadiumComboBox->currentText());

}

void tripPlanner::on_tabWidget_currentChanged(int index)
{
    switch(index) {
    case 0: // all souvenirs
        ui->totalPriceSpinBox->setValue(totalSpent);
        break;
//    case 1: // by stadium

//        break;
    }
}

void tripPlanner::on_stadiumComboBox_currentIndexChanged(const QString &arg1)
{
    double subtotal = 0.0;

    qDebug() << "arg1:" << arg1;

    ui->souvenirsPurchasedTableWidget_2->setRowCount(0);
    ui->souvenirsPurchasedTableWidget_2->setColumnCount(3);
    ui->souvenirsPurchasedTableWidget_2->setColumnWidth(1, 200);
    ui->souvenirsPurchasedTableWidget_2->setColumnWidth(0, 250);
    ui->souvenirsPurchasedTableWidget_2->setHorizontalHeaderLabels(QStringList{"Souvenir", "Qty", "Price"});


    for(const auto &i : shoppingCart) {
        qDebug() << "Souvenir in cart: " << std::get<0>(i) << std::get<1>(i) << std::get<2>(i) << std::get<3>(i);

        if(std::get<0>(i) == arg1) {
            qDebug() << "adding" << std::get<1>(i);
            ui->souvenirsPurchasedTableWidget_2->insertRow(ui->souvenirsPurchasedTableWidget_2->rowCount());
            ui->souvenirsPurchasedTableWidget_2->setItem(ui->souvenirsPurchasedTableWidget_2->rowCount()-1, 0, new QTableWidgetItem(std::get<1>(i)));
            ui->souvenirsPurchasedTableWidget_2->setItem(ui->souvenirsPurchasedTableWidget_2->rowCount()-1, 1, new QTableWidgetItem(QString::number(std::get<2>(i))));
            ui->souvenirsPurchasedTableWidget_2->setItem(ui->souvenirsPurchasedTableWidget_2->rowCount()-1, 2, new QTableWidgetItem(QString::number(std::get<3>(i))));

        }else {
            qDebug() << "NOT adding" << std::get<0>(i) << std::get<1>(i);
        }
    }

    // recount subtotal for just one stadium
    qDebug() << "counting subtotal, rowCount:" << ui->souvenirsPurchasedTableWidget_2->rowCount();
    for(int i = 0; i < ui->souvenirsPurchasedTableWidget_2->rowCount()-1; i++) {
        qDebug() << i << subtotal << "+" << ui->souvenirsPurchasedTableWidget_2->item(i, 2)->text().toDouble();
        subtotal += ui->souvenirsPurchasedTableWidget_2->item(i, 2)->text().toDouble();
        qDebug() << i << subtotal;
    }

    qDebug() << "setting spinbox";
    ui->totalPriceSpinBox->setValue(subtotal);
}

void tripPlanner::on_tripDoneButton_clicked()
{
    this->close();
}
