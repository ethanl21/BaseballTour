#include "addsouvenir.h"
#include "ui_addsouvenir.h"
#include "dbmanager.h"
#include <QString>

addSouvenir::addSouvenir(dbManager* db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addSouvenir)
{
    m_db = db;

    ui->setupUi(this);
    fillComboBox();
}

addSouvenir::~addSouvenir()
{
    delete ui;
}

void addSouvenir::fillComboBox()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry = new QSqlQuery();

    qry->prepare("SELECT team_name FROM teams");

    if(qry->exec())
    {
        qDebug() << "Combo box filled.";
    }
    else
        qDebug() << "failed";

    model->setQuery(*qry);

    ui->comboBox_addTeamName->setModel(model);
}

void addSouvenir::on_pushButton_addNewSouvenir_clicked()
{
    bool success = true;
    QString teamName = ui->comboBox_addTeamName->currentText();
    qDebug() << teamName;


    if(ui->lineEdit_addSouvenirName->text() == "")
    {
        ui->lineEdit_addSouvenirName->setPlaceholderText("Souvenir name empty!");
        success = false;
    }

    if(m_db->souvenirExists(ui->lineEdit_addSouvenirName->text(), teamName))
    {
        qDebug() << "New: " << teamName;
        qDebug() << ui->lineEdit_addSouvenirName->text();
        ui->lineEdit_addSouvenirName->setText("");
        ui->lineEdit_addSouvenirName->setPlaceholderText("Souvenir name exists!");
        success = false;
    }

    if(success)
    {
        double costToString = ui->doubleSpinBox_cost->value();
        QString costTwoDecimal = QString::number(costToString, 'f', 2);
        qDebug() << costTwoDecimal;
//        QString cost = QString::number(costToString);
        qDebug() << "Cost when adding Souvenir: " << costTwoDecimal;
        m_db->addSouvenir(teamName, ui->lineEdit_addSouvenirName->text(), costTwoDecimal);
        qDebug() << "Success here";
        hide();
    }
}

void addSouvenir::on_pushButton_cancelNewSouvenir_clicked()
{
    hide();
}
