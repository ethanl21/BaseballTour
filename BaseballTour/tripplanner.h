#ifndef TRIPPLANNER_H
#define TRIPPLANNER_H

#include <QDialog>
#include <utility>
#include <vector>

#include "dbmanager.h"
#include "purchasesouvenirs.h"

namespace Ui {
class tripPlanner;
}

class tripPlanner : public QDialog
{
    Q_OBJECT

public:
    explicit tripPlanner(vector<QString> stadiums, dbManager *db = nullptr, QWidget *parent = nullptr);
    ~tripPlanner();

    void setPath(const vector<QString> &stadiums) {stadiumNames = stadiums;}

private slots:
    void on_teamsroute_listWidget_currentTextChanged(const QString &currentText);

    void on_pushButton_clicked();

    void on_cancelTripButton_clicked();

    void on_endTripButton_clicked();

private:
    Ui::tripPlanner *ui;
    dbManager *db;
    PurchaseSouvenirs *shoppingCartWindow;

    vector<QString> stadiumNames; // should be in order

    std::vector<std::pair<QString, double>> shoppingCart;

    double totalSpent;
};

#endif // TRIPPLANNER_H