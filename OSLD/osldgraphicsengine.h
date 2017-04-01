#ifndef OSLDGRAPHICSENGINE_H
#define OSLDGRAPHICSENGINE_H

#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include "subdiagram.h"
#include "rootitempathscene.h"
#include "descriptionfilereader.h"

struct OSLDDataObject {
    QString name = "Default Diagram Name";
    QString description = "Default Diagram Description";
    QList<Subdiagram *> subdiagrams;  // a list of all of the subdiagrams
    QList<Block *> blocks;       // a list of all of the blocks in the diagram
    QList<Gate *> gates;         // a list of all of the gates in the diagram
    QList<DiagramItem *> blocksAndGates;  // a list of both blocks and gates
    QMap<QString, CommonSource> sourceMap;    // maps source ids to their name and type
    QMap<QString, StatusTypes> statusMap;    // maps status names to different colors
};

class OSLDGraphicsEngine : public QGraphicsScene
{
private:
    QMap<QString, CommonSource> sources;    // maps source ids to their name and type
    QMap<QString, StatusTypes> statuses;    // maps status names to different colors

    Subdiagram *currentSubdiagram = 0;

    QString diagramName;
    QString diagramDescription;
    QList<Subdiagram *> allSubdiagrams;     // a list of all of the subdiagrams
    QList<Block *> allBlocks;               // a list of all of the blocks in the diagram
    QList<Gate *> allGates;                 // a list of all of the gates in the diagram
    QList<DiagramItem *> allItems;          // a list of both blocks and gates

    RootItemPathScene *rootScene;
    QList<Block *> rootPathList;    // holds the chain of root items to the current subdiagram

    QVarLengthArray<QLineF> backgroundGrid;
    QVarLengthArray<QPointF> backgroundDots;

    int gridUnitSize = 20;
    bool showGridBackground = false;
    QColor backgroundColor = QColor("#fafafa");

    QGraphicsItem *pressedItem;
    QPointF pressPosition;

    // functions for creating gates
    Gate *createRandomGate(QPointF pos);

    // functions for creating blocks
    Block *createRandomBlock(QPointF pos);    // get information from the description file reader
    Block *buildBlock(QString id, QPointF position, QMap<QString, DiagramItemData> data);    // passes data into a block


public:
    OSLDGraphicsEngine(QString filePath = "", QWidget *parent = 0);

    QMap<QString, CommonSource> getSources() const { return sources; }
    void setSources(const QMap<QString, CommonSource> &value) { sources = value; }

    QMap<QString, StatusTypes> getStatuses() const { return statuses; }
    void setStatuses(const QMap<QString, StatusTypes> &value) { statuses = value; }

    QList<Subdiagram *> getAllSubdiagrams() const;

    void showGrid(bool show, QRectF area);

    void randomlyGenerateSubdiagrams(int numSubs);

    void drawSubdiagramItems(Subdiagram *sub);

    bool blockExists(QString id);
    Block *retrieveBlock(QString id);
    Subdiagram *createRandomSubdiagram(Block *root, int index);
    void hideSubdiagramItems(Subdiagram *sub);

    QList<Block *> getRootPathList() const;

    QList<DiagramItem *> getAllItems() const;

    void hideAllItemTitleText(bool b);

    RootItemPathScene *getRootScene() const;

    Subdiagram *getCurrentSubdiagram() const;

    void goToSubdiagram(Block *rootBlock);
    QString getDiagramName() const;
    void setDiagramName(const QString &value);

    QString getDiagramDescription() const;
    void setDiagramDescription(const QString &value);

    OSLDDataObject readDescriptionFile(QString filePath = "");
    void runGraphics(OSLDDataObject data);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // OSLDGRAPHICSENGINE_H
