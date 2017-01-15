#include "osldgraphicsengine.h"

OSLDGraphicsEngine::OSLDGraphicsEngine(QWidget *parent)
{
    this->parent = parent;

    // get the status types for this diagram
    statuses["Valid"] = QColor("#8BC34A");
    statuses["Invalid"] = QColor("#EF5350");
    statuses["Unknown"] = QColor("#888888");

    // get the sources for this diagram
    CommonSource sourceInfo;
    sourceInfo.name = "Combat System Database";
    sourceInfo.type = "SQLite Database";
    sources["source1"] = sourceInfo;

    for(int i = 0; i < 5; i++) {
        QPointF point(10, 100*i);
        Block *block =
                new Block(parent, QString("BlockID"), point);
        block->setStatus("Valid");
        block->setColor(this->statuses.value("Valid"));

        this->addItem(block);
    }

    // create the gate
    Gate *gate1 = new Gate(parent, "andGateId", QPointF(300,0), AndGate);
    this->addItem(gate1);

    Gate *gate2 = new Gate(parent, "orGateId", QPointF(300,150), OrGate);
    this->addItem(gate2);

    Gate *gate3 = new Gate(parent, "notGateId", QPointF(300,300), NotGate);
    this->addItem(gate3);

}

