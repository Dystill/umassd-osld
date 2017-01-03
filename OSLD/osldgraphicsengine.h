#ifndef OSLDGRAPHICSENGINE_H
#define OSLDGRAPHICSENGINE_H

#include <QtCore>
#include <QGraphicsScene>
#include "block.h"
#include "gate.h"

class OSLDGraphicsEngine
{
public:
    OSLDGraphicsEngine(QObject *parent);
    QGraphicsScene* getDiagramScene();

private:
    QGraphicsScene *scene;  // testing block
    Block *block;           // testing block
};

#endif // OSLDGRAPHICSENGINE_H
