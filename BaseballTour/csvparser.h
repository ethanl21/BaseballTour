#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <QString>
#include <QDebug>
#include <QFile>
#include <QStringList>

#include <vector>

#include <dbmanager.h>


class csvParser
{
public:
    csvParser(const QString& path) : filepath(path) {};

    void setFilePath(const QString& path) {filepath = path;}

    vector<teamData> parseTeamsFromFile() const;
    vector<distanceEdge> parseDistancesFromFile() const;

private:
    QString filepath;
};

#endif // CSVPARSER_H
