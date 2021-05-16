#include "purchasesouvenirs.h"
#include "ui_purchasesouvenirs.h"

PurchaseSouvenirs::PurchaseSouvenirs(const QString &stadium, dbManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PurchaseSouvenirs)
{
    ui->setupUi(this);
    database = db;
    ui->stadiumname_label->setText("Purchasing from: " + stadium);

    // populate souvenirs
    auto souvenirs = database->getSouvenirs(stadium);
    qDebug() << "getting souvenirs from" << stadium;

    ui->souvenirsListTableWidget->setHorizontalHeaderLabels(QStringList{"Souvenir", "Price"});
    ui->purchasedCartTableWidget->setHorizontalHeaderLabels(QStringList{"Souvenir", "Price"});

    ui->souvenirsListTableWidget->setCurrentCell(0,0);
    ui->purchasedCartTableWidget->setCurrentCell(0,0);


    for(const auto &i : souvenirs) {
        qDebug() << "[UNPURCHASED] adding:" << i.first << i.second;
        ui->souvenirsListTableWidget->insertRow(ui->souvenirsListTableWidget->rowCount());
        ui->souvenirsListTableWidget->setItem(ui->souvenirsListTableWidget->rowCount()-1, 0, new QTableWidgetItem(i.first));
        ui->souvenirsListTableWidget->setItem(ui->souvenirsListTableWidget->rowCount()-1, 1, new QTableWidgetItem(QString::number(i.second)));
    }

    acceptPurchase = false;
    subtotalOut = 0;
}

PurchaseSouvenirs::~PurchaseSouvenirs()
{
    delete ui;
}

void PurchaseSouvenirs::updateSubtotal()
{
    double subtotal = 0.0;

    for(int i = 0; i < ui->purchasedCartTableWidget->rowCount(); i++) {
        subtotal += ui->purchasedCartTableWidget->item(i, 1)->text().toDouble();
    }

    ui->subtotalSpinBox->setValue(subtotal);
    subtotalOut = subtotal;
}

void PurchaseSouvenirs::on_purchaseButton_clicked()
{

    auto souv = ui->souvenirsListTableWidget->item(ui->souvenirsListTableWidget->currentRow(), 0);
    auto price = ui->souvenirsListTableWidget->item(ui->souvenirsListTableWidget->currentRow(), 1);

    qDebug() << "[PURCHASED] adding:" << souv->text() << price->text();
    ui->purchasedCartTableWidget->insertRow(ui->purchasedCartTableWidget->rowCount());
    ui->purchasedCartTableWidget->setItem(ui->purchasedCartTableWidget->rowCount()-1, 0, new QTableWidgetItem(souv->text()));
    ui->purchasedCartTableWidget->setItem(ui->purchasedCartTableWidget->rowCount()-1, 1, new QTableWidgetItem(price->text()));

    updateSubtotal();

}

void PurchaseSouvenirs::on_removeButton_clicked()
{
    if(ui->purchasedCartTableWidget->currentRow() >= 0) {
        ui->purchasedCartTableWidget->removeRow(ui->purchasedCartTableWidget->currentRow());
        updateSubtotal();
    }

}
void PurchaseSouvenirs::on_buttonBox_accepted()
{
    acceptPurchase = true;

    for(int i = 0; i < ui->purchasedCartTableWidget->rowCount(); i++) {
        shoppingCart.push_back(std::pair<QString, double>{ui->purchasedCartTableWidget->item(i,0)->text(), ui->purchasedCartTableWidget->item(i,1)->text().toDouble()});
    }
}
