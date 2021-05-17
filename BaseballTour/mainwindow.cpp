#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "admin.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // get expected path of database
    const QString FILE_NAME = "mlb_data.db";
    QString dbPath = qApp->applicationDirPath();
    dbPath.append('/' + FILE_NAME);

    // open database with file path
    database = new dbManager(dbPath);
    qDebug() << "Database should be located at: " << dbPath;

    // user is not admin on program start
    isAdmin = false;

    // populate graph and combo boxes
    graph = nullptr;
    rebuildGraph();
}

MainWindow::~MainWindow()
{
    delete graph;
    delete ui;
}


void MainWindow::on_actionView_Database_triggered()
{
    dbView = new databaseviewform(database);
    dbView->exec();
    delete dbView;
}

void MainWindow::on_actionLog_In_triggered()
{
    lDialog = new logindialog(database);
    lDialog->exec();
    isAdmin = false;

    isAdmin = lDialog->userIsAdmin();
    qDebug() << isAdmin;

    delete lDialog;
}

void MainWindow::on_actionDBG_Is_User_Admin_triggered()
{
    if (isAdmin) {
        QMessageBox::information(this, "Success", "User is admin.");
    } else {
        QMessageBox::information(this, "Error", "User is NOT admin.");
    }
}

void MainWindow::on_actionLog_Out_triggered()
{
    if(isAdmin) {
        isAdmin = false;
        QMessageBox::information(this, "Success", "Logged out.");
    }else {
        QMessageBox::information(this, "Error", "User is not logged in.");
    }
}

void MainWindow::on_actionView_Database_by_Name_triggered()
{
    dbNameView = new databaseNameView(database);
    dbNameView->exec();
    delete dbNameView;
}

void MainWindow::on_addPushButton_clicked()
{
    if (ui->addComboBox->count() != 0) {
        QString team = ui->addComboBox->currentText();
        selectedList.push_back(team);

        ui->teamListWidget->addItem(team);
        ui->addComboBox->removeItem(ui->addComboBox->currentIndex());
        ui->startComboBox->addItem(team);
    }
}

void MainWindow::on_removePushButton_clicked()
{
    if (ui->teamListWidget->currentItem() != NULL) {
        QListWidgetItem *item = ui->teamListWidget->currentItem();
        int index = ui->teamListWidget->row(item);
        selectedList.erase(selectedList.begin() + index);

        ui->addComboBox->addItem(item->text());
        ui->startComboBox->removeItem(index);
        ui->teamListWidget->takeItem(index);
    }
}

void MainWindow::on_simpleStartButton_clicked()
{
    int distance = 0;
    vector<QString> route;
    if (ui->simpleToComboBox->currentIndex() == 0) { // visit all option
        //distance = graph->startShortestPath(ui->simpleFromComboBox->currentText());
        distance = graph->startMultiDijkstra(nameList,
                                         ui->simpleFromComboBox->currentText());
        //route = graph->shortestOrder;
        route = graph->dijkstraOrder;
    } else {
        QString start = ui->simpleFromComboBox->currentText();
        QString dest = ui->simpleToComboBox->currentText();
        distance = graph->startDijkstra(start, dest);
        route.push_back(start);
        route.push_back(dest);
    }

    // convert stadium names to team names
    vector<QString> teams;
    QString teamName;
    for (const QString &stadium : route) {
        qDebug() << "[simpleStartPushButton] stadium name: " << stadium;
        teamName = database->getStadiumData(stadium).team_name;
        teams.push_back(teamName);
    }

//    // display total distance
//    QMessageBox msgBox;
//    msgBox.setText("Total distance: " + QString::number(distance) + " miles");
//    msgBox.exec();

    // start trip planner
    tripWindow = new tripPlanner(teams, database, this);
    tripWindow->setDist(distance);
    tripWindow->exec();
    delete tripWindow;
}

void MainWindow::on_startPushButton_clicked()
{
    if (ui->mostEfficientRadioButton->isChecked())
    {
        QString start = ui->startComboBox->currentText();
        vector<QString> stadiumNames;

        // get all stadium names selected
        for (int i = 0; i < ui->teamListWidget->count(); i++) {
            stadiumNames.push_back(ui->teamListWidget->item(i)->text());
        }

        // perform dijkstra recursively
        int distance = graph->startMultiDijkstra(stadiumNames, start);

        // convert stadium names to team names
        vector<QString> route = graph->dijkstraOrder;
        vector<QString> teams;
        QString teamName;
        for (const QString &stadium : route) {
            qDebug() << "[startPushButton] stadium name: " << stadium;
            teamName = database->getStadiumData(stadium).team_name;
            teams.push_back(teamName);
        }

        // display total distance
        QMessageBox msgBox;
        msgBox.setText("Total distance: " + QString::number(distance) + " miles");
        msgBox.exec();

        // start trip planner
        tripWindow = new tripPlanner(teams, database, this);
        tripWindow->setDist(distance);
        tripWindow->exec();
        delete tripWindow;

    } else if (ui->shortestTripsRadioButton->isChecked()) {

        QString start = ui->startComboBox->currentText();
        vector<QString> stadiumNames;

        // get all stadium names selected
        for (int i = 0; i < ui->teamListWidget->count(); i++) {
            stadiumNames.push_back(ui->teamListWidget->item(i)->text());
        }

        int distance = 0;

        for (unsigned int i = 1; i < stadiumNames.size(); i++) {
            int distanceToAdd = graph->startDijkstra(ui->teamListWidget->item(i - 1)->text(), ui->teamListWidget->item(i)->text());
            qDebug() << "start:  " << ui->teamListWidget->item(i - 1)->text();
            qDebug() << "end: " << ui->teamListWidget->item(i)->text();
            qDebug() << "Distance to add: " << distanceToAdd;
            distance += distanceToAdd;
        }

        // convert stadium names to team names
        vector<QString> teams;
        QString teamName;
        for (const QString &stadium : stadiumNames) {
            qDebug() << "[startPushButton] stadium name: " << stadium;
            teamName = database->getStadiumData(stadium).team_name;
            teams.push_back(teamName);
        }

        // display total distance
        QMessageBox msgBox;
        msgBox.setText("Total distance: " + QString::number(distance) + " miles");
        msgBox.exec();

        // start trip planner
        tripWindow = new tripPlanner(teams, database, this);
        tripWindow->setDist(distance);
        tripWindow->exec();
        delete tripWindow;
    } else {
        QMessageBox::information(this, "Error", "Please select a trip order.");
    }


}

void MainWindow::rebuildGraph()
{
    ui->simpleToComboBox->clear();
    ui->simpleFromComboBox->clear();
    ui->addComboBox->clear();

    // populate vectors and comboBox
    nameList = database->getStadiumNames();
    tempList = nameList;
    ui->simpleToComboBox->addItem("Visit all"); // visit all option

    for (auto teamName : nameList) {
        ui->simpleFromComboBox->addItem(teamName);
        ui->simpleToComboBox->addItem(teamName);
        ui->addComboBox->addItem(teamName);
    }

    // populate graph
    if(graph != nullptr) {
        delete graph;
    }
    graph = new Graph<QString>();
    vector<distanceEdge> edges;
    for (const QString &stadium : nameList) {
        qDebug() << "adding node:" << stadium;
        graph->addNode(stadium);
    }
    for (const QString &stadium : nameList) {
        edges = database->getDistances(stadium);
        for (const auto &edge : edges) {
            qDebug() << "adding edge:" << edge.team_name_origin << edge.team_name_destination << edge.distance;
            graph->addEdge(edge.team_name_origin, edge.team_name_destination,
                           edge.distance);
        }
    }
}

void MainWindow::on_actionModify_Database_triggered()
{
    if(isAdmin) {
        adminWindow = new Admin(database, this);
        adminWindow->exec();
        delete adminWindow;
    }else {
        QMessageBox::information(this, "Error", "You must be an administrator to modify the database.");
    }
}

void MainWindow::on_actionImport_Teams_triggered()
{
    if(!isAdmin) {
        QMessageBox::information(this, "Error", "You must be an administrator to modify the database.");
    }else {
        qDebug() << "Home location: " << QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        QString addTeamsFilePath = QFileDialog::getOpenFileName(this, tr("Open Teams File"), QStandardPaths::writableLocation(QStandardPaths::HomeLocation), tr("Teams (*.csv)"));
        qDebug() << "path: " << addTeamsFilePath;

        csvParser parser(addTeamsFilePath);

        vector<teamData> newTeams = parser.parseTeamsFromFile();
        vector<QString> existingTeams = database->getTeamNames();

        // make sure new teams are unique
        for(const auto &i : newTeams) {
            if(std::find(existingTeams.begin(), existingTeams.end(), i.team_name) != existingTeams.end()) {
                // if new team exists in database already, remove it
                newTeams.erase(vector<teamData>::const_iterator(&i));
            }
        }

        if(newTeams.size() > 0) {
            for(const auto &i : newTeams) {
                database->addTeam(i);

                // add default souvenirs
                database->addSouvenir(i.team_name, "Baseball Cap", "19.99");
                database->addSouvenir(i.team_name, "Baseball Bat", "89.39");
                database->addSouvenir(i.team_name, "Team Pennant", "17.99");
                database->addSouvenir(i.team_name, "Autographed Baseball", "29.99");
                database->addSouvenir(i.team_name, "Team Jersey", "199.99");
            }

        }

        rebuildGraph();
    }
}

void MainWindow::on_actionImport_Distances_triggered()
{
    if(!isAdmin) {
        QMessageBox::information(this, "Error", "You must be an administrator to modify the database.");
    }else {
        qDebug() << "Home location: " << QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
        QString addDistFilePath = QFileDialog::getOpenFileName(this, tr("Open Distances File"), QStandardPaths::writableLocation(QStandardPaths::HomeLocation), tr("Distances (*.csv)"));
        qDebug() << "path: " << addDistFilePath;

        csvParser parser(addDistFilePath);

        vector<distanceEdge> newDist = parser.parseDistancesFromFile();

        // add the distances to database
        if(newDist.size() > 0) {
            for(const auto &i : newDist) {
                database->addDist(i);
            }
        }

        rebuildGraph();
    }
}

void MainWindow::on_DFSpushButton_clicked()
{
    int distance = graph->startDFS("Oracle Park");
    QString pathStr;
    for (const auto &dest : graph->dfsOrder) {
        pathStr += dest + "\n";
    }

    QMessageBox msgBox;
    msgBox.setText("DFS starting from Oracle Park (San Francisco Giants)");
    msgBox.setInformativeText("Total distance: " + QString::number(distance));
    msgBox.setDetailedText(pathStr);
    msgBox.exec();
}

void MainWindow::on_BFSpushButton_clicked()
{
    int distance = graph->startBFS("Target Field");
    QString pathStr;
    for (const auto &dest : graph->bfsOrder) {
        pathStr += dest + "\n";
    }

    QMessageBox msgBox;
    msgBox.setText("BFS starting from Target Field (Minnesota Twins)");
    msgBox.setInformativeText("Total distance: " + QString::number(distance));
    msgBox.setDetailedText(pathStr);
    msgBox.exec();
}

void MainWindow::on_MSTpushButton_clicked()
{
    int distance = graph->startMST();
    QString pathStr = "MST Edges:\n";
    pathStr += graph->mstString;

    QMessageBox msgBox;
    msgBox.setStyleSheet("QLabel{min-width: 400px;}");
    msgBox.setText("MST");
    msgBox.setInformativeText("Total distance: " + QString::number(distance));
    msgBox.setDetailedText(pathStr);
    msgBox.exec();
}
