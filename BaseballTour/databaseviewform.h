#ifndef DATABASEVIEWFORM_H
#define DATABASEVIEWFORM_H

#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlTableModel>
#include <vector>

#include "dbmanager.h"

namespace Ui {
class databaseviewform;
}

class databaseviewform : public QDialog
{
    Q_OBJECT

public:
    explicit databaseviewform(dbManager* db = nullptr, QWidget *parent = nullptr);
    ~databaseviewform();

private:
    Ui::databaseviewform *ui;

    // !! DO NOT delete in destructor
    dbManager* database;

    void populateTable(QSqlTableModel* model) const;
};

#endif // DATABASEVIEWFORM_H
