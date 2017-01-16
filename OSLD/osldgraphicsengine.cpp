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

    // create some gates
    Gate *gate1 = new Gate(parent, "andGateId", QPointF(600,0), AndGate);
    allGates.append(gate1);
    Gate *gate2 = new Gate(parent, "orGateId", QPointF(600,150), OrGate);
    allGates.append(gate2);
    Gate *gate3 = new Gate(parent, "notGateId", QPointF(600,300), NotGate);
    allGates.append(gate3);

    // get blocks from the description file
    QPointF point(0, 0);
    for(int i = 0; i < 5; i++) {    // obtain the number of diagram items from the description file

        if(!allBlocks.isEmpty()) {
            point.setY(point.y() + allBlocks.at(i - 1)->height() + 20);
        }

        Block *block = getBlockInfoFromDescriptionFile(point);

        allBlocks.append(block);

        this->connectItems(block, gate2);
    }

    this->drawAllItems();
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
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
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

    // for testing large title strings
    // if(random % 3 == 0) bd.title.append("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

    return buildBlock(id, position, bd);
}

// adds data to a block
Block *OSLDGraphicsEngine::buildBlock(QString id, QPointF position, BlockData data)
{
    qDebug() << "Creating Block" << id;

    Block *block = new Block(this->parent, id, position);

    block->setTitle(data.title);
    block->setDescription(data.description);
    block->setToolTip(data.hovertext);
    block->setStatus(data.status, statuses);

    return block;
}

void OSLDGraphicsEngine::drawAllItems()
{
    for(int i = 0; i < allGates.count(); i++) {
        //qDebug() << "Drawing Gate" << i;
        this->addItem(allGates.at(i));
    }
    for(int i = 0; i < allConns.count(); i++) {
        //qDebug() << "Drawing Connector" << i;
        this->addItem(allConns.at(i));
    }
    for(int i = 0; i < allBlocks.count(); i++) {
        //qDebug() << "Drawing Block" << i;
        this->addItem(allBlocks.at(i));
    }
}


/*
 *  CONNECTOR FUNCTIONS
 */

void OSLDGraphicsEngine::connectItems(Gate *input, DiagramItem *output)
{
    QPointF startPoint = input->outputPoint();
    QPointF endPoint = output->inputPoint();

    Connector *conn = new Connector(startPoint, endPoint);

    //qDebug() << "Connecting Gate to Item:" << startPoint << "to" << endPoint;

    input->addOutputConnector(conn);
    output->addInputConnector(conn);

    allConns.append(conn);
}

void OSLDGraphicsEngine::connectItems(Block *input, DiagramItem *output)
{

    QPointF startPoint = input->outputPoint();
    QPointF endPoint = output->inputPoint();
    QColor color = input->getColor();

    //qDebug() << "Connecting Block to Item:" << startPoint << "to" << endPoint;

    Connector *conn = new Connector(startPoint, endPoint, color);

    input->addOutputConnector(conn);
    output->addInputConnector(conn);

    allConns.append(conn);
}
