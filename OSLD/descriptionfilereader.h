#ifndef DESCRIPTIONFILEREADER_H
#define DESCRIPTIONFILEREADER_H

#include <QtCore>
#include <QFileDialog>
#include <QDebug>
#include "block.h"
#include "gate.h"


// holds data source information
struct CommonSource {
    QString sourceNum;
    QString name;
    QString type;
};

struct statusTypes {
    QString status;
    QString color;
    QString textColor;
    QString typeFaceFlagString;
    bool    typeFaceFlag;
};



class DescriptionFileReader: public QXmlStreamReader
{
public:
    DescriptionFileReader(QWidget *parent = 0);
    ~DescriptionFileReader();

    QMap <QString, statusTypes> statuses;



    //Methods
    void readFile(QString filepath);

    QString getDiagramName() const;
    void setDiagramName();

    QString getDescription() const;

    QString cleanString(QString s);
    void storeStatusData(QString s, statusTypes t, QString currentTag, QXmlStreamAttributes a);
    bool StringConvert (statusTypes t);
    void multiReadNext(int i);

    void readMetaData(QString tag);
    void readBlocks();
    void readGates();
    void readSubdiagrams();

    QList<Subdiagram *> getAllSubdiagrams() const;

    QList<Block *> getAllBlocks() const;

    QList<Gate *> getAllGates() const;

    QList<DiagramItem *> getAllItems() const;

protected:
    QString path;

private:
    TokenType currentToken;
    QString diagramName;
    QString description;

    QList<Subdiagram *> allSubdiagrams;  // a list of all of the subdiagrams
    QList<Block *> allBlocks;       // a list of all of the blocks in the diagram
    QList<Gate *> allGates;         // a list of all of the gates in the diagram
    QList<DiagramItem *> allItems;  // a list of both blocks and gates

    QMap<QString, int> getDimensions();
    QPointF getLocationPoint();
    void getStatusInfo();
};

#endif // DESCRIPTIONFILEREADER_H
//Disregard
