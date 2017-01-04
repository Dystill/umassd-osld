#ifndef OSLDGRAPHICSENGINE_H
#define OSLDGRAPHICSENGINE_H

#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QGraphicsGridLayout>
#include "block.h"
#include "gate.h"

class OSLDGraphicsEngine
{
public:
    OSLDGraphicsEngine(QObject *parent);
    QGraphicsWidget *drawGateGroup(Gate *gate);
    QGraphicsScene *getDiagramScene();


private:
    QGraphicsScene *scene;  // holds the entire diagram
};

#endif // OSLDGRAPHICSENGINE_H
