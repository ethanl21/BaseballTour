#ifndef PURCHASESOUVENIRS_H
#define PURCHASESOUVENIRS_H

#include <QDialog>
#include <utility>
#include <QMessageBox>
#include <vector>

namespace Ui {
class PurchaseSouvenirs;
}

class PurchaseSouvenirs : public QDialog
{
    Q_OBJECT

public:
    explicit PurchaseSouvenirs(QWidget *parent = nullptr);
    ~PurchaseSouvenirs();

    std::vector<std::pair<QString, double>> getShoppingCart() const {return shoppingCart;}

private:
    Ui::PurchaseSouvenirs *ui;

    std::vector<std::pair<QString, double>> shoppingCart;

};

#endif // PURCHASESOUVENIRS_H
