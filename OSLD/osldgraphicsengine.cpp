#include "osldgraphicsengine.h"

OSLDGraphicsEngine::OSLDGraphicsEngine(QWidget *parent)
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

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

    for(int i = 0; i < 2; i++) {
        QPointF rootPoint(0, 0);

        // set the root for the subdiagram
        Block *block = getBlockInfoFromDescriptionFile(rootPoint);
        allBlocks.append(block);
        allItems.append(block);

        // add items
        QPointF itemPoints;
        itemPoints.setX(rootPoint.x() - 200);
        itemPoints.setY(rootPoint.y());

        Gate *gate = getGateInfoFromDescriptionFile(itemPoints);
        allGates.append(gate);
        allItems.append(gate);

        itemPoints.setX(itemPoints.x() - 400);
        itemPoints.setY(itemPoints.y() - 100);
        Block *block1 = getBlockInfoFromDescriptionFile(itemPoints);
        allBlocks.append(block1);
        allItems.append(block1);

        itemPoints.setY(itemPoints.y() + 200);
        Block *block2 = getBlockInfoFromDescriptionFile(itemPoints);
        allBlocks.append(block2);
        allItems.append(block2);

        // set subdiagram nam and description
        QString name = QString("Subdiagram %1").arg(i);
        QString desc = QString("Subdiagram Description for %1").arg(i);

        Subdiagram *sub = new Subdiagram(block, name, desc);
        sub->addInputItem(gate);
        sub->connectItems(gate, block);

        sub->addInputItem(block1);
        sub->connectItems(block1, gate);

        sub->addInputItem(block2);
        sub->connectItems(block2, gate);

        sub->drawAllItems();
        allSubdiagrams.append(sub);
    }
}

Gate *OSLDGraphicsEngine::getGateInfoFromDescriptionFile(QPointF pos) {

    int random = qrand() % 123456;

    QString id = "Gate ";
    id.append(QString::number(random));

    GateType type;

    if(random % 3 == 0) {
        type = AndGate;
    }
    else if((random % 3) - 1 == 0) {
        type = OrGate;
    }
    else {
        type = NotGate;
    }

    Gate *gate = new Gate(this->parent, id, pos, type);

    gate->setStatus("Valid", statuses);

    return gate;
}


/*
 *  BLOCK FUNCTIONS
 */

// gets block information from a description file
// ******currently only generates random data
Block *OSLDGraphicsEngine::getBlockInfoFromDescriptionFile(QPointF pos)
{
    // create DescriptionFileReader object

    // obtain the id for this a block from
    int random = qrand() % 123456;

    QString id = "Block ";
    id.append(QString::number(random));

    QPointF position = pos;

    // create a BlockData structure to store the block data
    BlockData bd;
    bd.title = QString("Block %1 Title").arg(random);
    bd.description = QString("Block %1 Description").arg(random);
    bd.hovertext = QString("Block %1 Hovertext").arg(random);
    bd.status = (random % 2 == 0 ? "Valid" : "Invalid");

    if(random % 2 == 1) {
        bd.textColor = QColor(Qt::black);
    }
    else if(random % 3 == 0) {

    }

    // for testing large title strings
    // if(random % 3 == 0) bd.title.append("@@@@@ @@@@@@@@@ @@@@@@@ @@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@ @@@@@ @@@@ @@@@@@@@@@@@@@@@ @@@ @ @@@@@@@@@@@@ @@@@@@@@@ @@@ @@@@@@@@@@@@@@@@@@ @@@@ @");

    return buildBlock(id, position, bd);
}

// adds data to a block
Block *OSLDGraphicsEngine::buildBlock(QString id, QPointF position, BlockData data)
{
    // qDebug() << "Creating Block" << id;

    Block *block = new Block(this->parent, id, position);

    block->setTitle(data.title);
    block->setDescription(data.description);
    block->setToolTip(data.hovertext);
    block->setStatus(data.status, statuses);
    block->setTextColor(data.textColor);

    return block;
}


QList<Subdiagram *> OSLDGraphicsEngine::getAllSubdiagrams() const
{
    return allSubdiagrams;
}
