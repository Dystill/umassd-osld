#ifndef OSLDGRAPHICSENGINE_H
#define OSLDGRAPHICSENGINE_H

#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QGraphicsGridLayout>
#include "block.h"
#include "gate.h"
#include "connector.h"

class OSLDGraphicsEngine : public QGraphicsScene
{
public:
    OSLDGraphicsEngine(QObject *parent);
    QGraphicsWidget *drawGateGroup(Gate *gate);


private:
    QGraphicsScene *scene;  // holds the entire diagram
    QList<Gate *> gates;    // holds all of the gates
};

#endif // OSLDGRAPHICSENGINE_H
