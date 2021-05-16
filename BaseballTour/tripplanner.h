#ifndef TRIPPLANNER_H
#define TRIPPLANNER_H

#include <QDialog>
#include "dbmanager.h"

namespace Ui {
class tripPlanner;
}

class tripPlanner : public QDialog
{
    Q_OBJECT

public:
    explicit tripPlanner(dbManager *db = nullptr, QWidget *parent = nullptr);
    ~tripPlanner();

private slots:
    void on_teamsroute_listWidget_currentTextChanged(const QString &currentText);

private:
    Ui::tripPlanner *ui;
    dbManager *db;
};

#endif // TRIPPLANNER_H
