#ifndef PURCHASESOUVENIRS_H
#define PURCHASESOUVENIRS_H

#include <QDialog>
#include <utility>
#include <QMessageBox>
#include <vector>
#include <tuple>

#include "dbmanager.h"

typedef std::tuple<QString, QString, int, double> shoppingCartItem;

namespace Ui {
class PurchaseSouvenirs;
}

class PurchaseSouvenirs : public QDialog
{
    Q_OBJECT

public:
    explicit PurchaseSouvenirs(const QString &team, dbManager *db = nullptr, QWidget *parent = nullptr);
    ~PurchaseSouvenirs();

    //!
    //! \brief getShoppingCart returns the shopping cart after purchasing is complete
    //! \return items purchased
    //!
    std::vector<shoppingCartItem> getShoppingCart() const {return shoppingCart;}

    //!
    //! \brief amountSpent
    //! \return amount spent after purchase is complete
    //!
    double amountSpent() const {return subtotalOut;}

private slots:
    void on_purchaseButton_clicked();

    void on_removeButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::PurchaseSouvenirs *ui;

    std::vector<shoppingCartItem> shoppingCart;

    //!
    //! \brief updateSubtotal updates the subtotal displayed in UI
    //!
    void updateSubtotal();

    dbManager *database;

    double subtotalOut;

    bool acceptPurchase;

    QString teamName;
};

#endif // PURCHASESOUVENIRS_H
