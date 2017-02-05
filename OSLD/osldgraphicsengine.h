#ifndef OSLDGRAPHICSENGINE_H
#define OSLDGRAPHICSENGINE_H

#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include "subdiagram.h"
#include "rootitempathscene.h"

// holds data source information
struct CommonSource {
    QString name;
    QString type;
};

class OSLDGraphicsEngine : public QGraphicsScene
{
private:
    QMap<QString, CommonSource> sources;    // maps source ids to their name and type
    QMap<QString, QString> statuses;    // maps status names to different colors

    Subdiagram *currentSubdiagram = 0;
    QList<Subdiagram *> allSubdiagrams;  // a list of all of the subdiagrams
    QList<Block *> allBlocks;       // a list of all of the blocks in the diagram
    QList<Gate *> allGates;         // a list of all of the gates in the diagram
    QList<DiagramItem *> allItems;  // a list of both blocks and gates

    RootItemPathScene *rootScene;
    QList<Block *> rootPathList;    // holds the chain of root items to the current subdiagram

    QVarLengthArray<QLineF> backgroundGrid;
    QVarLengthArray<QPointF> backgroundDots;

    int gridUnitSize = 20;
    bool showGridBackground = false;

    QGraphicsItem *pressedItem;
    QPointF pressPosition;

    // functions for creating gates
    Gate *getGateInfoFromDescriptionFile(QPointF pos);

    // functions for creating blocks
    Block *getBlockInfoFromDescriptionFile(QPointF pos);    // get information from the description file reader
    Block *buildBlock(QString id, QPointF position, BlockData data);    // passes data into a block


public:
    OSLDGraphicsEngine(QWidget *parent);

    QMap<QString, CommonSource> getSources() const { return sources; }
    void setSources(const QMap<QString, CommonSource> &value) { sources = value; }

    QMap<QString, QString> getStatuses() const { return statuses; }
    void setStatuses(const QMap<QString, QString> &value) { statuses = value; }

    QList<Subdiagram *> getAllSubdiagrams() const;

    void showGrid(bool show, QRectF area);

    void drawSubdiagramItems(Subdiagram *sub);

    bool blockExists(QString id);
    Block *retrieveBlock(QString id);
    Subdiagram *getSubdiagramInfoFromDescriptionFile(Block *root, int index);
    void hideSubdiagramItems(Subdiagram *sub);

    QList<Block *> getRootPathList() const;

    QList<DiagramItem *> getAllItems() const;

    void hideAllItemTitleText(bool b);

    RootItemPathScene *getRootScene() const;

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // OSLDGRAPHICSENGINE_H
