#ifndef OSLDGRAPHICSENGINE_H
#define OSLDGRAPHICSENGINE_H

#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include "block.h"
#include "gate.h"
#include "connector.h"

// holds data source information
struct CommonSource {
    QString name;
    QString type;
};

// holds subdiagram information
struct Subdiagram {
    QString name;
    DiagramItem *root;                  // the final item for the diagram
    QList<DiagramItem *> inputItems;    // all other diagram items in the subdiagram
};

class OSLDGraphicsEngine : public QGraphicsScene
{
private:
    QWidget *parent;

    QMap<QString, CommonSource> sources;    // maps source ids to their name and type
    QMap<QString, QString> statuses;    // maps status names to different colors

    int fullWidth;  // holds the width of the entire diagram
    int fullHeight; // holds the height for the entire diagram
    int gridUnitSize = 20;

    QVarLengthArray<QLineF> backgroundGrid;
    QVarLengthArray<QPointF> backgroundDots;

    bool showGridBackground = false;

    QList<Block *> allSubdiagrams;  // a list of all of the blocks in the diagram
    QList<Block *> allBlocks;       // a list of all of the blocks in the diagram
    QList<Gate *> allGates;         // a list of all of the gates in the diagram
    QList<DiagramItem *> allItems;  // a list of both blocks and gates
    QList<Connector *> allConns;    // a list of all connector objects for this diagram


    Subdiagram *createSubdiagram(DiagramItem *rootItem, QList<QString> itemIds, QString name);

    // functions for creating gates
    Gate *getGateInfoFromDescriptionFile(QPointF pos);

    // functions for creating blocks
    Block *getBlockInfoFromDescriptionFile(QPointF pos);    // get information from the description file reader
    Block *buildBlock(QString id, QPointF position, BlockData data);    // passes data into a block

    void connectItems(Gate *input, DiagramItem *output);    // creates a connector from a gate to another item
    void connectItems(Block *input, DiagramItem *output);   // creates a connector from a block to another item

    void drawAllItems();    // draws all of the items in the three "all" lists


public:
    OSLDGraphicsEngine(QWidget *parent);
    QGraphicsWidget *drawGateGroup(Gate *gate);

    QMap<QString, CommonSource> getSources() const { return sources; }
    void setSources(const QMap<QString, CommonSource> &value) { sources = value; }

    QMap<QString, QString> getStatuses() const { return statuses; }
    void setStatuses(const QMap<QString, QString> &value) { statuses = value; }

    void drawBackground(QPainter *painter, const QRectF &rect);
    void showGrid(bool show, QRectF area);
};

#endif // OSLDGRAPHICSENGINE_H
