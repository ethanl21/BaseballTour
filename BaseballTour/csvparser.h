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

    //!
    //! \brief csvParser
    //! \param path - file path to csv file to parse
    //!
    csvParser(const QString& path) : filepath(path) {};

    //!
    //! \brief setFilePath
    //! \param path - file path to csv file to parse
    //!
    void setFilePath(const QString& path) {filepath = path;}

    //!
    //! \brief parseTeamsFromFile
    //! \return vector of teams parsed from file
    //!
    vector<teamData> parseTeamsFromFile() const;

    //!
    //! \brief parseDistancesFromFile
    //! \return vector of edges parsed from file
    //!
    vector<distanceEdge> parseDistancesFromFile() const;

private:

    //!
    //! \brief filepath - path to file
    //!
    QString filepath;
};

#endif // CSVPARSER_H
