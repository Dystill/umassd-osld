#include "osldgraphicsengine.h"

OSLDGraphicsEngine::OSLDGraphicsEngine(QWidget *parent)
{
    this->parent = parent;

    // get the status types for this diagram
    statuses["Valid"] = "#8BC34A";
    statuses["Invalid"] = "#EF5350";
    statuses["Unknown"] = "#888888";

    // get the sources for this diagram
    CommonSource sourceInfo;
    sourceInfo.name = "Combat System Database";
    sourceInfo.type = "SQLite Database";
    sources["source1"] = sourceInfo;

    // makes some blocks in a column
    QPointF point(0, 0);
    for(int i = 0; i < 1; i++) {

        if(!allBlocks.isEmpty())
            point.setY(point.y() + allBlocks.at(i - 1)->height() + 20);

        qDebug() << "Place at" << point;

        Block *block;

        BlockData bd;

        bd.title = QString("Block %1 Title").arg(i);
        bd.description = QString("Block %1 Description").arg(i);
        bd.hovertext = QString("Block %1 Hovertext").arg(i);
        bd.status = (i % 2 == 0 ? "Valid" : "Invalid");

        if(i%3 == 0) bd.title.append(" h89w8hfwe9gh9f8h9w 8fhuhwf3 @@@@@@@@@ll@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

        QString id = QString("Block %1 ID").arg(i);
        block = this->buildBlock(id, point, bd);

        allBlocks.append(block);
        this->addItem(block);
    }

    // create some gates
    Gate *gate1 = new Gate(parent, "andGateId", QPointF(300,0), AndGate);
    this->addItem(gate1);

    Gate *gate2 = new Gate(parent, "orGateId", QPointF(300,150), OrGate);
    this->addItem(gate2);

    Gate *gate3 = new Gate(parent, "notGateId", QPointF(300,300), NotGate);
    this->addItem(gate3);

}

// adds data to a block
Block *OSLDGraphicsEngine::buildBlock(QString id, QPointF position, BlockData data)
{
    Block *block = new Block(this->parent, id, position);

    block->setTitle(data.title);
    block->setDescription(data.description);
    block->setHovertext(data.hovertext);
    block->setStatus(data.status, statuses);

    qDebug() << block->getTitle();

    return block;
}

