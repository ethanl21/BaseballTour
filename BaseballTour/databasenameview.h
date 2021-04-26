#ifndef DATABASENAMEVIEW_H
#define DATABASENAMEVIEW_

#include <QDialog>
#include "dbmanager.h"
#include <QTableWidget>
#include <QMessageBox>
using namespace std;

namespace Ui {
class databaseNameView;
}

class databaseNameView : public QDialog
{
    Q_OBJECT

public:
    explicit databaseNameView(dbManager* db,QWidget *parent = nullptr);
    QTableWidgetItem* NewItem();
    ~databaseNameView();

private slots:

    void on_pushButton_clicked();

    void on_teamsComboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::databaseNameView *ui;
    dbManager* database;
    void populateTable(QSqlTableModel* model) const;
};

#endif // DATABASENAMEVIEW_H
