#ifndef PURCHASESOUVENIRS_H
#define PURCHASESOUVENIRS_H

#include <QDialog>
#include <utility>
#include <QMessageBox>
#include <vector>

#include "dbmanager.h"

namespace Ui {
class PurchaseSouvenirs;
}

class PurchaseSouvenirs : public QDialog
{
    Q_OBJECT

public:
    explicit PurchaseSouvenirs(const QString &stadium, dbManager *db = nullptr, QWidget *parent = nullptr);
    ~PurchaseSouvenirs();

    std::vector<std::pair<QString, double>> getShoppingCart() const {return shoppingCart;}

    void updateSubtotal();

    double amountSpent() const {return subtotalOut;}

private slots:
    void on_purchaseButton_clicked();

    void on_removeButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::PurchaseSouvenirs *ui;

    std::vector<std::pair<QString, double>> shoppingCart;

    dbManager *database;

    double subtotalOut;

    bool acceptPurchase;

};

#endif // PURCHASESOUVENIRS_H
