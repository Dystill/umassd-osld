#ifndef DESCRIPTIONFILEREADER_H
#define DESCRIPTIONFILEREADER_H

#include <QtCore>
#include <QFileDialog>
#include <QDebug>
#include "subdiagram.h"


// holds data source information
struct CommonSource {
    QString name;
    QString type;
};

struct StatusTypes {
    QString color;
    QString textColor;
    bool    italics = false;
    bool    bold = false;
    bool    underline = false;
};



class DescriptionFileReader: public QXmlStreamReader
{
private:
    TokenType currentToken;
    QString diagramName;
    QString diagramDescription;

    QMap <QString, CommonSource> sources;
    QMap <QString, StatusTypes> statuses;

    QList<Subdiagram *> allSubdiagrams;  // a list of all of the subdiagrams
    QList<Block *> allBlocks;       // a list of all of the blocks in the diagram
    QList<Gate *> allGates;         // a list of all of the gates in the diagram
    QList<DiagramItem *> allItems;  // a list of both blocks and gates

    QMap<QString, int> getDimensions();
    QPointF getLocationPoint(QString tagName);
    void getStatusInfo();

public:
    DescriptionFileReader(QWidget *parent = 0);
    ~DescriptionFileReader();

    //Methods
    void readFile(QString filepath);

    QString getDiagramName() const;

    QString getDescription() const;

    QString cleanString(QString s);

    bool stringToBool (QString boolString);

    void readMetaData();
    void readBlocks();
    void readGates();
    void readSubdiagrams();

    QList<Subdiagram *> getAllSubdiagrams() const;

    QList<Block *> getAllBlocks() const;

    QList<Gate *> getAllGates() const;

    QList<DiagramItem *> getAllItems() const;
};

#endif // DESCRIPTIONFILEREADER_H
