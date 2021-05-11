#include "csvparser.h"

vector<teamData> csvParser::parseTeamsFromFile() const {
  QStringList row;
  teamData temp;
  vector<teamData> teamsOut;

  // open the file
  QFile iFile(filepath);
  iFile.open(QIODevice::ReadOnly);

  // link stream to file
  QTextStream csvStream(&iFile);

  csvStream.readLine(); // ignore heading

  // parse teams from file
  while (!csvStream.atEnd()) {
    QString s = csvStream.readLine();

    s.replace("\\,", QChar(QChar::SoftHyphen));

    row.append(s.split(","));

    for(auto &i : row) {
        i.replace(QChar(QChar::SoftHyphen), ',');
        i.replace("\"", "");
    }

    temp.team_name = row[0];
    temp.stadium_name = row[1];
    temp.stadium_seating_capacity = row[2].toInt();
    temp.stadium_location = row[3];
    temp.stadium_playing_surface = row[4];
    temp.team_league = row[5];
    temp.stadium_date_opened = row[6].toInt();
    temp.stadium_dist_ctrfield = row[7];
    temp.stadium_typology = row[8];
    temp.stadium_roof_type = row[9];

    teamsOut.push_back(temp);

    row.clear();
  }
  iFile.close();

  return teamsOut;
}

vector<distanceEdge> csvParser::parseDistancesFromFile() const
{
    QStringList row;
    distanceEdge temp;
    vector<distanceEdge> edgeOut;

    // open the file
    QFile iFile(filepath);
    iFile.open(QIODevice::ReadOnly);

    // link stream to file
    QTextStream csvStream(&iFile);

    csvStream.readLine(); // ignore heading

    // parse distances from file
    while (!csvStream.atEnd()) {
      QString s = csvStream.readLine();

      s.replace("\\,", QChar(QChar::SoftHyphen));

      row.append(s.split(","));

      for(auto &i : row) {
          i.replace(QChar(QChar::SoftHyphen), ',');
          i.replace("\"", "");
      }

      temp.team_name_origin = row[0];
      temp.team_name_destination = row[1];
      temp.distance = row[2].toInt();


      edgeOut.push_back(temp);

      row.clear();
    }
    iFile.close();

    return edgeOut;
}
