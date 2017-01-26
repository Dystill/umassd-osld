#include "osldgraphicsengine.h"

OSLDGraphicsEngine::OSLDGraphicsEngine(QWidget *parent)
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    int random;

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

    // get gates from the description file
    QPointF point(600, 0);
    for(int i = 0; i < 6; i++) {

        if(!allGates.isEmpty()) {
            point.setY(point.y() + allGates.at(i - 1)->height() + 20);
        }

        Gate *gate = getGateInfoFromDescriptionFile(point);

        allGates.append(gate);
        allItems.append(gate);
    }

    // get blocks from the description file
    point.setX(0);
    point.setY(0);
    for(int i = 0; i < 6; i++) {

        if(!allBlocks.isEmpty()) {
            point.setY(point.y() + allBlocks.at(i - 1)->height() + 20);
        }

        Block *block = getBlockInfoFromDescriptionFile(point);

        allBlocks.append(block);
        allItems.append(block);

        random = qrand() % allGates.count();

        this->connectItems(block, allGates.at(random));
    }

    for(int i = 0; i < allGates.count(); i++) {
        random = qrand() % allBlocks.count();
        // this->connectItems(allBlocks.at(random), allGates.at(i));
        this->connectItems(allGates.at(i), allBlocks.at(random));
    }

    this->drawAllItems();
}

// overrides to draw a grid for the background
void OSLDGraphicsEngine::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->fillRect(rect, QBrush(QColor("#fafafa")));

    if(showGridBackground) {
        QPen pen;
        pen.setCosmetic(true);
        pen.setColor(QColor("#212121"));
        painter->setPen(pen);

        qreal topY = rect.top();
        qreal leftX = rect.left();
        qreal bottomY = rect.bottom();
        qreal rightX = rect.right();

        qreal startingX = int(leftX) - (int(leftX) % gridUnitSize);
        qreal startingY = int(topY) - (int(topY) % gridUnitSize);

        /*
        for(qreal x = startingX; x < rightX; x += gridUnitSize) {
            backgroundGrid.append(QLineF(x, topY, x, bottomY));
        }
        for(qreal y = startingY; y < bottomY; y += gridUnitSize) {
            backgroundGrid.append(QLineF(leftX, y, rightX, y));
        }
        painter->drawLines(backgroundGrid.data(), backgroundGrid.size());
        */

        for(qreal x = startingX; x < rightX; x += gridUnitSize) {
            for(qreal y = startingY; y < bottomY; y += gridUnitSize) {
                backgroundDots.append(QPointF(x, y));
            }
        }
        painter->drawPoints(backgroundDots.data(), backgroundDots.size());
    }
}

Subdiagram *OSLDGraphicsEngine::createSubdiagram(DiagramItem *rootItem, QList<QString> itemIds, QString name)
{
    Subdiagram *sub = new Subdiagram;

    sub->name = name;
    sub->root = rootItem;   // store the root item

    for(int i = 0; i < allItems.count(); i++) {                 // loop through each item in allItems
        for(int j = 0; j < itemIds.count(); j++) {                  // loop through each string in the id list
            if(allItems.at(i)->id().compare(itemIds.at(j)) == 0) {  // if the item's id matches the id in the id list
                sub->inputItems.append(allItems.at(i));              // add the item to the subdiagram
                j = itemIds.count();                                // go to the next id
            }
        }
    }

    return sub;
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

    return new Gate(this->parent, id, pos, type);
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

void OSLDGraphicsEngine::drawAllItems()
{
    for(int i = 0; i < allConns.count(); i++) {
        //qDebug() << "Drawing Connector" << i;
        this->addItem(allConns.at(i));
    }
    for(int i = 0; i < allGates.count(); i++) {
        //qDebug() << "Drawing Gate" << i;
        this->addItem(allGates.at(i));
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

/*
 *  OTHER FUNCTIONS
 */

void OSLDGraphicsEngine::showGrid(bool show, QRectF area) {
    showGridBackground = show;
    this->invalidate(area, BackgroundLayer);
}
