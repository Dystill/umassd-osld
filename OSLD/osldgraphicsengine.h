#ifndef OSLDGRAPHICSENGINE_H
#define OSLDGRAPHICSENGINE_H

#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include "block.h"
#include "gate.h"
#include "connector.h"

struct CommonSource {
    QString name;
    QString type;
};

struct Subdiagram {
    QString name;
    QString description;
    QString hovertext;
    bool showOutline;
    QList<DiagramItem *> items;
};

class OSLDGraphicsEngine : public QGraphicsScene
{
private:
    QWidget *parent;  // holds the entire diagram

    QMap<QString, CommonSource> sources;
    QMap<QString, QString> statuses;

    int fullWidth;
    int fullHeight;

    QList<Block *> allBlocks;
    QList<Gate *> allGates;
    QList<Connector *> allConns;

    Block *getBlockInfoFromDescriptionFile(QPointF pos);
    Block *buildBlock(QString id, QPointF position, BlockData data);

    void connectItems(Gate *input, DiagramItem *output);
    void connectItems(Block *input, DiagramItem *output);

    void drawAllItems();

public:
    OSLDGraphicsEngine(QWidget *parent);
    QGraphicsWidget *drawGateGroup(Gate *gate);

    QMap<QString, CommonSource> getSources() const { return sources; }
    void setSources(const QMap<QString, CommonSource> &value) { sources = value; }

    QMap<QString, QString> getStatuses() const { return statuses; }
    void setStatuses(const QMap<QString, QString> &value) { statuses = value; }
};

#endif // OSLDGRAPHICSENGINE_H
