#include "admin.h"
#include "ui_admin.h"
#include "dbmanager.h"
//#include "fileselector.h"

Admin::Admin(dbManager* db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Admin)
{
//    m_db = QSqlDatabase::addDatabase("QSQLITE");
//    m_db.setDatabaseName(path);

    ui->setupUi(this);
    m_db = db;
    updateSouvenirs();
}

//Admin::Admin(const QString& path)
//{
//    m_db = QSqlDatabase::addDatabase("QSQLITE");
//    m_db.setDatabaseName(path);
//}

Admin::~Admin()
{
    delete ui;
}

void Admin::updateSouvenirs()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare("SELECT * FROM Souvenirs");

    if(qry.exec())
    {
        qDebug() << "Souvenirs updated";
    }

    model->setQuery(qry);

    QSortFilterProxyModel *m=new QSortFilterProxyModel(this);

    m->setDynamicSortFilter(true);
    m->setSourceModel(model);
    ui->souvenir_tableView->setModel(m);
    ui->souvenir_tableView->setColumnWidth(0,180);
}

void Admin::on_pushButton_updateSouvenir_clicked()
{
    bool success = true;

    if(ui->lineEdit_souvenirName->text() == "")
    {
        ui->lineEdit_souvenirName->setPlaceholderText("souvenir name empty!");
        success = false;
    }

    if(!m_db->souvenirExists(ui->lineEdit_souvenirName->text(), ui->label_stadiumName->text()))
    {
        if(success)
        {
            double costToString = ui->doubleSpinBox_cost->value();
            QString cost = QString::number(costToString);
            // cost = cost;
            m_db->updateSouvenir(tempSouvenir, ui->label_stadiumName->text(), cost, ui->lineEdit_souvenirName->text());
            qDebug() << "Souvenir Name: " << ui->lineEdit_souvenirName->text();
            qDebug() << "Temp: " << tempSouvenir;
        }
        else
        {
            qDebug() << "Remove error";
        }
    }
    else if(tempSouvenir == ui->lineEdit_souvenirName->text())
    {
        if(success)
        {
            double costToString = ui->doubleSpinBox_cost->value();
            QString cost = QString::number(costToString);
            m_db->updateSouvenir(tempSouvenir, ui->label_stadiumName->text(), cost, ui->lineEdit_souvenirName->text());
            qDebug() << ui->lineEdit_souvenirName->text();
        }
        else
        {
            qDebug() << "Remove error";
        }
        updateSouvenirs();
    }
    updateSouvenirs();
}

void Admin::on_pushButton_removeSouvenir_clicked()
{
    bool success = true;

    if(ui->lineEdit_souvenirName->text() == "")
    {
        ui->lineEdit_souvenirName->setPlaceholderText("");
        success = false;
    }

    if(!m_db->souvenirExists(ui->lineEdit_souvenirName->text(), ui->label_stadiumName->text()))
    {
       ui->lineEdit_souvenirName->setText("");
       ui->lineEdit_souvenirName->setPlaceholderText("souvenir doesn't exist!");
       success = false;
    }

    if(m_db->souvenirExists(ui->lineEdit_souvenirName->text(), ui->label_stadiumName->text()) && success)
    {
        m_db->removeSouvenir(ui->lineEdit_souvenirName->text(), ui->label_stadiumName->text());
        ui->lineEdit_souvenirName->setText("");
        ui->lineEdit_souvenirName->setPlaceholderText("souvenir name");
    }
    else
    {
        qDebug() << "Error removing Souvenir";
    }
    updateSouvenirs();
}

void Admin::on_souvenir_tableView_clicked(const QModelIndex &index)
{
    if(index.isValid())
    {
        int row = index.row();
        qDebug() << row;
        QString teams = index.sibling(row, 0).data().toString();
        qDebug() << teams;
        QString souvenirName = index.sibling(row, 1).data().toString();
        qDebug() << souvenirName;
        tempSouvenir = index.sibling(row, 1).data().toString();
        double thirdText = index.sibling(row, 2).data().toString().replace("$", "").toDouble();

        ui->lineEdit_souvenirName->setText(souvenirName);
        ui->label_stadiumName->setText(teams);
        ui->doubleSpinBox_cost->setValue(thirdText);
    }
}

//void Admin::on_pushButton_addSouvenir_clicked()
//{
//    addSouvenir adding;
//    adding.setModal(true);
//    adding.exec();
//    updateSouvenirs();
//}

//void Admin::on_pushButton_addNewColleges_clicked()
//{
//    fileSelector* browse = new fileSelector();
//    browse->show();
//    hide();
//}

//void Admin::on_pushButton_clearColleges_clicked()
//{
//    m_db.clearColleges();
//    updateColleges();
//}
