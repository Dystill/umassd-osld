#include "osldgraphicsengine.h"

OSLDGraphicsEngine::OSLDGraphicsEngine(QString filePath,
                                       QWidget *parent,
                                       int pollingRate,
                                       bool hideControls,
                                       QString rootViewOrientation,
                                       bool hideBlockTitles,
                                       bool fullscreen,
                                       bool showGridBackground) :
    QGraphicsScene(parent)
{
    this->hideControls = hideControls;
    this->pollingRate = pollingRate;
    this->rootViewOrientation = rootViewOrientation;
    this->hideBlockTitles = hideBlockTitles;
    this->fullscreen = fullscreen;
    this->showGridBackground = showGridBackground;

    this->readFileAndRunOSLD(filePath);
}

// read a description file and return the data object
OSLDDataObject OSLDGraphicsEngine::readDescriptionFile(QString filePath) {
    DescriptionFileReader descriptionFile(filePath);        // run the description file reader

    // save errors
    this->xmlError = descriptionFile.error();
    this->xmlErrorString = descriptionFile.errorString() + "\nLine number " + QString::number(descriptionFile.lineNumber()) + ".";

    OSLDDataObject data;
    if(this->xmlError == QXmlStreamReader::NoError) {
        data.name = descriptionFile.getDiagramName();           // obtain name of full diagram
        data.description = descriptionFile.getDescription();    // obtain description for full diagram
        data.blocks = descriptionFile.getAllBlocks();           // obtain QList of all the blocks in the diagram
        data.gates = descriptionFile.getAllGates();             // obtain QList of all the gates in the diagram
        data.blocksAndGates = descriptionFile.getAllItems();    // obtain QList containing both blocks and gates (may not be necessary?)
        data.subdiagrams = descriptionFile.getAllSubdiagrams(); // obtain QList of all Subdiagrams

        data.sourceMap = descriptionFile.getSources();   // QMap of source:CommonSource pairs
        data.statusMap = descriptionFile.getStatuses(); // QMap of status:StatusTypes pairs
    }

    return data;
}

// use a data object to display the graphics
void OSLDGraphicsEngine::runGraphics(OSLDDataObject data) {

    // remove all currently displayed items
    this->hideSubdiagramItems(currentSubdiagram);
    this->rootPathList.clear();

    // get all information from description file reader
    this->diagramName = data.name;   // name of full diagram
    this->diagramDescription = data.description;    // description for full diagram
    this->allBlocks = data.blocks;   // QList of all the blocks in the diagram
    this->allGates = data.gates; // QList of all the gates in the diagram
    this->allItems = data.blocksAndGates; // QList containing both blocks and gates (may not be necessary?)
    this->allSubdiagrams = data.subdiagrams; // QList of all Subdiagrams

    this->sources = data.sourceMap;   // QMap of source:CommonSource pairs
    this->statuses = data.statusMap; // QMap of status:StatusTypes pairs

    // draw main diagram if a subdiagram exists
    if(!allSubdiagrams.isEmpty()) {
        rootPathList.append(allSubdiagrams.at(0)->getRoot());
        this->drawSubdiagramItems(allSubdiagrams.at(0));
    }

    // create a path scene
    rootScene = new RootItemPathScene(this, this->getRootPathList(), Vertical);

    // print counts for each Qlist
    // qDebug() << "OSLD blocks" << this->allBlocks.count();
    // qDebug() << "OSLD gates" << this->allGates.count();
    // qDebug() << "OSLD items" << this->allItems.count();
    // qDebug() << "OSLD subdiagrams" << this->allSubdiagrams.count();

    // call function to retrieve status data
    this->retrieveStatusData();

    for (QString key : allItems.keys()) {
        allItems[key]->startPollTimer(this->pollingRate);    // start timer to regularly send polling signal

        connect(allItems[key], SIGNAL(pollStatus(QString,QString,QString,QString,QString)),
                this, SLOT(retrieveStatusDataForItem(QString,QString,QString,QString,QString)));    // connect item polling to graphicsengine slot

        allItems[key]->update();    // update item
    }
}

void OSLDGraphicsEngine::readFileAndRunOSLD(QString filePath)
{
    // process description file and display the graphics
    this->runGraphics(this->readDescriptionFile(filePath));
}

// Emits a signal asking for the status data for all items.
void OSLDGraphicsEngine::retrieveStatusData()
{
    // QMap of queried items.
    QMap<QString, bool> queried;

    for (DiagramItem *diagramItem : allItems.values()) {

        // Check if item has a source.
        if (!diagramItem->getSourceId().isEmpty()) {
            QString queriedId;
            StatusData statusData;

            statusData.id = diagramItem->id();
            statusData.ref_id = diagramItem->ref_id();
            statusData.titleQuery = diagramItem->getStatusInfo().titleQuery;
            statusData.descriptionQuery = diagramItem->getStatusInfo().descriptionQuery;
            statusData.hovertextQuery = diagramItem->getStatusInfo().hovertextQuery;

            // Determine which item id to fetch information for.
            queriedId = (statusData.ref_id.isEmpty()) ? statusData.id : statusData.ref_id;

            // Emit signal if not already queried.
            if (!queried.contains(queriedId)) {
                emit statusDataQuery(statusData);
                queried[queriedId] = true;
            }
        }
    }
}

void OSLDGraphicsEngine::retrieveStatusDataForItem(QString itemId, QString refId, QString titleQuery, QString descQuery, QString hoverQuery)
{
    StatusData statusData;

    statusData.id = itemId;
    statusData.ref_id = refId;
    statusData.titleQuery = titleQuery;
    statusData.descriptionQuery = descQuery;
    statusData.hovertextQuery = hoverQuery;

    // qDebug() << "querying data for" << itemId << statusData.titleQuery << statusData.descriptionQuery << statusData.hovertextQuery;
    emit statusDataQuery(statusData);
}

// Updates a status with the recieved status data.
void OSLDGraphicsEngine::updateStatus(StatusData statusData)
{
    DiagramItem *item = allItems[statusData.id];
    DiagramItemData statusInfo = item->getStatusInfo();

    // Update status info from recieved data if not null.
    statusInfo.title = (statusData.title.isNull()) ? statusInfo.title : statusData.title;
    statusInfo.titleQuery = (statusData.titleQuery.isNull()) ? statusInfo.titleQuery : statusData.titleQuery;
    statusInfo.description = (statusData.description.isNull()) ? statusInfo.description : statusData.description;
    statusInfo.descriptionQuery = (statusData.descriptionQuery.isNull()) ? statusInfo.descriptionQuery : statusData.descriptionQuery;
    statusInfo.hovertext = (statusData.hovertext.isNull()) ? statusInfo.hovertext : statusData.hovertext;
    statusInfo.hovertextQuery = (statusData.hovertextQuery.isNull()) ? statusInfo.hovertextQuery : statusData.hovertextQuery;

    // Pass updated data to item.
    item->updateStatusInfo(statusInfo);
    item->setStatus(statusData.status, statuses);
}

void OSLDGraphicsEngine::alignRootScene(PathAlignment alignment, QGraphicsView *view)
{
    if(alignment == Vertical) {
        rootScene->alignVertically();
    }
    else {
        rootScene->alignHorizontally();
    }

    rootScene->setParentGraphicsView(view);
}

void OSLDGraphicsEngine::fitRootSceneToView()
{
    rootScene->fitToView();
}

void OSLDGraphicsEngine::resizeRootScenePadding(int padding)
{
    rootScene->setSceneRect(
            rootScene->itemsBoundingRect().adjusted(-padding, -padding, padding, padding));
}

// overrides to draw a grid for the background
void OSLDGraphicsEngine::drawBackground(QPainter *painter, const QRectF &rect)
{
    // fill background
    painter->fillRect(rect, QBrush(backgroundColor));

    // draw grid
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

        /* draw lines instead of dots for grid - graphic intensive
        for(qreal x = startingX; x < rightX; x += gridUnitSize) {
            backgroundGrid.append(QLineF(x, topY, x, bottomY));
        }
        for(qreal y = startingY; y < bottomY; y += gridUnitSize) {
            backgroundGrid.append(QLineF(leftX, y, rightX, y));
        }
        painter->drawLines(backgroundGrid.data(), backgroundGrid.size());
        */

        // draw points
        for(qreal x = startingX; x < rightX; x += gridUnitSize) {
            for(qreal y = startingY; y < bottomY; y += gridUnitSize) {
                backgroundDots.append(QPointF(x, y));
            }
        }
        painter->drawPoints(backgroundDots.data(), backgroundDots.size());
    }
}

void OSLDGraphicsEngine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressedItem = itemAt(event->scenePos(), QTransform());  // store the item that was clicked down on
    pressPosition = event->scenePos();                      // store the position of the click
    QGraphicsScene::mousePressEvent(event);
}

void OSLDGraphicsEngine::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}

// handles click events within the diagram scene graphics
// determines what happens when a diagram item is pressed
void OSLDGraphicsEngine::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem *releaseItem = itemAt(event->scenePos(), QTransform());   // get the item that was released

    // if the left mouse button was used to press a diagram item
    if(event->button() == Qt::LeftButton) {

        // if the item was released at the same position that it was pressed, i.e. mouse wasn't moved during click
        if(releaseItem == pressedItem && pressPosition == event->scenePos()) {

            Block *pressedBlock;    // to store a pointer to the clicked block

            if((pressedBlock = dynamic_cast<Block *>(releaseItem))) {   // store pointer if the item was a block

                // check if the block has a subdiagram
                if(pressedBlock->hasChildSubdiagram()) {

                    Subdiagram *sub = pressedBlock->getChildSubdiagram();    // get pointer to the block's subdiagram

                    // if the current subdiagram's root block was pressed and it's not the main top level subdiagram
                    // then go back to previous subdiagram
                    if(sub == currentSubdiagram) {
                        if(pressedBlock->getParentSubdiagram() != 0) {
                            // go to previous subdiagram
                            this->goToSubdiagram(pressedBlock->getParentSubdiagram()->getRoot());
                        }
                    }
                    // else when a regular subdiagram block was pressed
                    else {
                        this->goToSubdiagram(pressedBlock);
                    }
                }
            }
        }
    }
    // if the right mouse button was used to press a diagram item
    else if(event->button() == Qt::RightButton) {

        DiagramItem *pressedItem;    // to store a pointer to the clicked block

        if((pressedItem = dynamic_cast<DiagramItem *>(releaseItem))) {   // store pointer to the item that was clicked

            if(!(pressedItem->getDescription().isEmpty()))
                QMessageBox::information(event->widget(),pressedItem->getTitle(),pressedItem->getDescription());

        }
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void OSLDGraphicsEngine::goToSubdiagram(Block *rootBlock) {

    this->hideSubdiagramItems(currentSubdiagram);   // hide current subdiagram

    int rootBlockListIndex = -1;    // index for the rootBlock in the rootPathList

    // search for the rootBlock in the rootPathList and save the index if found
    for(int i = 0; i < rootPathList.count(); i++) {
        if(rootPathList.at(i)->id() == rootBlock->id()) {
            rootBlockListIndex = i;
        }
    }

    // if not found
    if(rootBlockListIndex == -1) {
        rootPathList.append(rootBlock); // add new block to the end
    }

    // else if found
    else {
        // start from end of rootPathList and remove blocks up to the saved index
        for(int i = (rootPathList.count() - 1); i > rootBlockListIndex; i--) {
            rootPathList.removeAt(i);
        }
    }

    // draw rootBlock's subdiagram
    this->drawSubdiagramItems(rootBlock->getChildSubdiagram());
    rootScene->setList(rootPathList);
}


void OSLDGraphicsEngine::drawSubdiagramItems(Subdiagram *sub)
{
    // draw all of this subdiagram's connecting lines
    for(int i = 0; i < sub->getConnectors().count(); i++) {
        //qDebug() << "Drawing Connector" << i;
        this->addItem(sub->getConnectors().at(i));
    }

    // draw all of the items except for the rootBlock
    DiagramItem *item;
    for(int i = 0; i < sub->getInputItems().count(); i++) {
        //qDebug() << "Drawing Block" << i;
        item = sub->getInputItems().at(i);
        item->setPos(item->getLocation());
        this->addItem(item);
    }

    // get the subdiagram's root item
    Block *root = sub->getRoot();

    // set it's position to the root location
    root->setPos(root->getRootLocation());

    root->setCurrentlyRoot(true);

    this->addItem(root);
    currentSubdiagram = sub;

    this->update();
    emit subdiagramChanged();
}

void OSLDGraphicsEngine::hideSubdiagramItems(Subdiagram *sub)
{
    if(sub != 0) {
        for(int i = 0; i < sub->getConnectors().count(); i++) {
            //qDebug() << "Drawing Connector" << i;
            this->removeItem(sub->getConnectors().at(i));
        }
        for(int i = 0; i < sub->getInputItems().count(); i++) {
            //qDebug() << "Drawing Block" << i;
            this->removeItem(sub->getInputItems().at(i));
        }
        Block *root = sub->getRoot();
        root->setCurrentlyRoot(false);
        this->removeItem(root);
        currentSubdiagram = 0;
    }
}

// create a gate with random information
QList<Block *> OSLDGraphicsEngine::getRootPathList() const
{
    return rootPathList;
}

QMap<QString, DiagramItem *> OSLDGraphicsEngine::getAllItems() const
{
    return allItems;
}

RootItemPathScene *OSLDGraphicsEngine::getRootScene() const
{
    return rootScene;
}

Subdiagram *OSLDGraphicsEngine::getCurrentSubdiagram() const
{
    return currentSubdiagram;
}

QString OSLDGraphicsEngine::getDiagramName() const
{
    return diagramName;
}

void OSLDGraphicsEngine::setDiagramName(const QString &value)
{
    diagramName = value;
}

QString OSLDGraphicsEngine::getDiagramDescription() const
{
    return diagramDescription;
}

void OSLDGraphicsEngine::setDiagramDescription(const QString &value)
{
    diagramDescription = value;
}

QList<Subdiagram *> OSLDGraphicsEngine::getAllSubdiagrams() const
{
    return allSubdiagrams;
}

QList<Block *> OSLDGraphicsEngine::getAllBlocks() const
{
    return allBlocks;
}

QList<Gate *> OSLDGraphicsEngine::getAllGates() const
{
    return allGates;
}

bool OSLDGraphicsEngine::getHideControls() const
{
    return hideControls;
}

QString OSLDGraphicsEngine::getRootViewOrientation() const
{
    return rootViewOrientation;
}

bool OSLDGraphicsEngine::getHideBlockTitles() const
{
    return hideBlockTitles;
}

bool OSLDGraphicsEngine::getFullscreen() const
{
    return fullscreen;
}

bool OSLDGraphicsEngine::getShowGridBackground() const
{
    return showGridBackground;
}

int OSLDGraphicsEngine::getPollingRate() const
{
    return pollingRate;
}

void OSLDGraphicsEngine::showGrid(bool show, QRectF area) {
    showGridBackground = show;
    this->invalidate(area, BackgroundLayer);
}

bool OSLDGraphicsEngine::blockExists(QString id) {
    for(int i = 0; i < allBlocks.count(); i++) {
        if(id.compare(allBlocks.at(i)->id())) {
            return true;
        }
    }
    return false;
}

Block *OSLDGraphicsEngine::retrieveBlock(QString id) {
    for(int i = 0; i < allBlocks.count(); i++) {
        if(id.compare(allBlocks.at(i)->id())) {
            return allBlocks.at(i);
        }
    }
    return 0;
}

void OSLDGraphicsEngine::hideAllItemTitleText(bool b) {
    DiagramItem::setTransparent(b);
    for (QString key : allItems.keys()) {
        allItems[key]->update();
    }
    this->update();
}


/*
 *  RANDOM GENERATION FUNCTIONS BELOW
 *  FOR TESTING PURPOSES - NOT USED
 */

void OSLDGraphicsEngine::randomlyGenerateSubdiagrams(int numSubs)
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    // create some random subdiagrams with three blocks and a single gate
    for(int i = 0; i < numSubs; i++) {
        QPointF rootPoint(0, 0);

        // set the root for the subdiagram
        Block *block;
        if(i == 0) {    // for the main subdiagram
            block = createRandomBlock(rootPoint); // create a root block
        }
        else {
            DiagramItem *item;  // create a diagramitem
            do {
                int random = qrand() % allSubdiagrams.at(i - 1)->getInputItems().count();
                item = allSubdiagrams.at(i - 1)->getInputItems().at(random);    // get a random input item from the previous subdiagram
            } while (item->isGate());                                           // keep trying until a block is obtained
            block = qgraphicsitem_cast<Block *>(item);  // set the root block to the random item
        }
        block->setRootLocation(rootPoint);  // set the root block's root location
        allBlocks.append(block);
        allItems[block->id()] = block;

        // add items
        QPointF itemPoints;
        itemPoints.setX(rootPoint.x() - 200);
        itemPoints.setY(rootPoint.y());

        Gate *gate = createRandomGate(itemPoints);
        allGates.append(gate);
        allItems[gate->id()] = gate;

        itemPoints.setX(itemPoints.x() - 400);
        itemPoints.setY(itemPoints.y() - 100);
        Block *block1 = createRandomBlock(itemPoints);
        allBlocks.append(block1);
        allItems[block1->id()] = block1;

        itemPoints.setY(itemPoints.y() + 200);
        Block *block2 = createRandomBlock(itemPoints);
        allBlocks.append(block2);
        allItems[block2->id()] = block2;

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

        allSubdiagrams.append(sub);
    }
}

Subdiagram *OSLDGraphicsEngine::createRandomSubdiagram(Block *root, int index) {
    Subdiagram *sub = new Subdiagram();

    // get name and description
    sub->setName(QString("Subdiagram %1").arg(index));
    sub->setDescription(QString("Subdiagram Description for %1").arg(index));

    // set the root block
    sub->setRoot(root);

    // get item ids, find the items, then add to the subdiagram

    // set all of the connectors

    return sub;
}

// gets block information from a description file
// ******currently only generates random data
Block *OSLDGraphicsEngine::createRandomBlock(QPointF pos)
{
    // create DescriptionFileReader object

    // obtain the id for this a block from
    int random = qrand() % 123456;

    QString id = "Block ";
    id.append(QString::number(random));

    QPointF position = pos;

    QMap<QString, DiagramItemData> dataList;

    // create a DiagramItemData structure to store the block data
    DiagramItemData itemData;
    itemData.title = QString("Block %1 Title").arg(random);
    itemData.description = QString("Block %1 Description").arg(random);
    itemData.hovertext = QString("Block %1 Hovertext").arg(random);

    for(int i = 0; i < statuses.count(); i++) {
        int random2 = qrand() % 2;
        if(random2 == 0) {
            itemData.textColor = QColor(Qt::white);
        }
        random2 = qrand() % 2;
        if(random2 == 0) {
            itemData.bold = true;
        }
        random2 = qrand() % 2;
        if(random2 == 1) {
            itemData.underline = true;
        }
        random2 = qrand() % 2;
        if(random2 == 1) {
            itemData.italics = true;
        }
        dataList[statuses.keys().at(i)] = itemData;
    }

    // for testing large title strings
    // if(random % 3 == 0) bd.title.append("@@@@@ @@@@@@@@@ @@@@@@@ @@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@ @@@@@ @@@@ @@@@@@@@@@@@@@@@ @@@ @ @@@@@@@@@@@@ @@@@@@@@@ @@@ @@@@@@@@@@@@@@@@@@ @@@@ @");

    return buildBlock(id, position, dataList);
}

// adds data to a block
Block *OSLDGraphicsEngine::buildBlock(QString id, QPointF position, QMap<QString, DiagramItemData> data)
{
    // qDebug() << "Creating Block" << id;

    int random = qrand() % 2;

    Block *block = new Block(id, position);

    QString status = (random == 0 ? "Valid" : "Invalid");

    block->setStatusInfoDataList(data);
    block->setStatus(status, statuses);
    block->updateStatusInfo();

    // qDebug() << block->getTextColor();
    // qDebug() << data[status].textColor;

    return block;
}

QString OSLDGraphicsEngine::getXmlErrorString() const
{
    return xmlErrorString;
}

QXmlStreamReader::Error OSLDGraphicsEngine::getXmlError() const
{
    return xmlError;
}

Gate *OSLDGraphicsEngine::createRandomGate(QPointF pos) {

    int random = qrand() % 123456;  // make a random number

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

    Gate *gate = new Gate(id, type, pos);

    gate->setStatus("Valid", statuses);

    return gate;
}

