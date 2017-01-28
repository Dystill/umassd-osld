#ifndef OSLDGRAPHICSENGINE_H
#define OSLDGRAPHICSENGINE_H

#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include "subdiagram.h"

// holds data source information
struct CommonSource {
    QString name;
    QString type;
};

class OSLDGraphicsEngine
{
private:
    QWidget *parent;

    QMap<QString, CommonSource> sources;    // maps source ids to their name and type
    QMap<QString, QString> statuses;    // maps status names to different colors


    QList<Subdiagram *> allSubdiagrams;  // a list of all of the subdiagrams
    QList<Block *> allBlocks;       // a list of all of the blocks in the diagram
    QList<Gate *> allGates;         // a list of all of the gates in the diagram
    QList<DiagramItem *> allItems;  // a list of both blocks and gates

    // functions for creating gates
    Gate *getGateInfoFromDescriptionFile(QPointF pos);

    // functions for creating blocks
    Block *getBlockInfoFromDescriptionFile(QPointF pos);    // get information from the description file reader
    Block *buildBlock(QString id, QPointF position, BlockData data);    // passes data into a block

    void drawAllItems();    // draws all of the items in the three "all" lists


public:
    OSLDGraphicsEngine(QWidget *parent);

    QMap<QString, CommonSource> getSources() const { return sources; }
    void setSources(const QMap<QString, CommonSource> &value) { sources = value; }

    QMap<QString, QString> getStatuses() const { return statuses; }
    void setStatuses(const QMap<QString, QString> &value) { statuses = value; }
    QList<Subdiagram *> getAllSubdiagrams() const;
};

#endif // OSLDGRAPHICSENGINE_H
