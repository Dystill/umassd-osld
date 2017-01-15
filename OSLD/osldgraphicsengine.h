#ifndef OSLDGRAPHICSENGINE_H
#define OSLDGRAPHICSENGINE_H

#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QGraphicsGridLayout>
#include "block.h"
#include "gate.h"

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

public:
    OSLDGraphicsEngine(QWidget *parent);
    QGraphicsWidget *drawGateGroup(Gate *gate);

    QMap<QString, CommonSource> getSources() const { return sources; }
    void setSources(const QMap<QString, CommonSource> &value) { sources = value; }

    QMap<QString, QString> getStatuses() const { return statuses; }
    void setStatuses(const QMap<QString, QString> &value) { statuses = value; }

    Block *buildBlock(QString id, QPointF position, BlockData data);
};

#endif // OSLDGRAPHICSENGINE_H
