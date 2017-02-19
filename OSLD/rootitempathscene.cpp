#include "rootitempathscene.h"

/*
 *  CONSTRUCTORS
 */

// Blank constructor - potentially not necessary
RootItemPathScene::RootItemPathScene()
{
}

// Constructor that sets the inital alignment and then sets the initial list
RootItemPathScene::RootItemPathScene(QList<Block *> itemList, PathAlignment pa)
{
    this->setCurrentAlignment(pa);
    this->setList(itemList);
}

// returns the current list being displayed
QList<Block *> RootItemPathScene::getList() const
{
    return rootPathList;
}

// clears the current list, sets it to a new one, then updates the scene
void RootItemPathScene::setList(const QList<Block *> &itemList)
{
    // remove all items in the current main root list from being displayed
    for(int i = rootPathList.count() - 1; i >= 0; i--) {
        this->removeItem(rootPathList.at(i));
    }

    // should clear all items in the root list from memory
    rootPathList.clear();

    // go through all of the items from the passed in list
    for(int i = 0; i < itemList.count(); i++) {
        Block *block = new Block(itemList.at(i));   // create a copy of the current block
        // qDebug() << "block width:" << block->width();
        block->setIsInDiagram(false);               // set block so it knows it isn't in the main diagram
        rootPathList.append(block);                 // add the new block to the main list
    }

    // update the items, scene, and view
    this->updateItems();
}

// function to align the current items either vertically or horizontally
void RootItemPathScene::align(PathAlignment pa)
{
    // qDebug() << "aligning items";

    QPointF position(0,0);  // start at point 0,0

    // go through each item in the root list
    for(int i = 0; i < rootPathList.count(); i++) {

        // create a pointer to that block
        Block *block = rootPathList.at(i);

        if(this->items().contains(block)) this->removeItem(block); // remove the item from the scene if it hasn't been remove yet

        block->setPos(position); // set the position of the block to the current QPointF

        this->addItem(block); // add the block to the scene

        // update the QPointF for the next block
        // move the point down if vertical or right if horizontal
        if(pa == Vertical)
            position.setY(position.y() + block->boundingRect().height() + blockMargin);
        else if(pa == Horizontal)
            position.setX(position.x() + block->boundingRect().width() + blockMargin);

        // qDebug() << "scene rect width 1:" << this->itemsBoundingRect().width();
    }

    this->setCurrentAlignment(pa); // set the current alignment to the passed in enum

    this->update(); // update the scene
}

// convenience function to align vertically and then update items
void RootItemPathScene::alignVertically()
{
    this->setCurrentAlignment(Vertical);
    this->updateItems();
}

// convenience function to align horizontally and then update items
void RootItemPathScene::alignHorizontally()
{
    this->setCurrentAlignment(Horizontal);
    this->updateItems();
}

// get the current alignment for this
PathAlignment RootItemPathScene::getCurrentAlignment() const
{
    return currentAlignment;
}

// set the current alignment for this
// *** note: not sure if this should be public
void RootItemPathScene::setCurrentAlignment(const PathAlignment &value)
{
    currentAlignment = value;
}

// function to update each item in the list by adding the items
void RootItemPathScene::updateItems()
{
    // qDebug() << "updating items";

    // align the items based on the current alignment
    this->align(this->getCurrentAlignment());

    // update the scene
    this->update();

    // fit the scene to the view
    this->fitToView();
}

// gets the graphicsview this is being displayed in
QGraphicsView *RootItemPathScene::getParentGraphicsView() const
{
    return parentGraphicsView;
}

// set the graphicsview this is being displayed in
void RootItemPathScene::setParentGraphicsView(QGraphicsView *value)
{
    parentGraphicsView = value;
}

// calls parent graphicsview to fit the scene's contents to the viewport
void RootItemPathScene::fitToView()
{
    //qDebug() << "checking for view";
    if(this->getParentGraphicsView() != 0) {
        //qDebug() << "view found, fitting to view";

        //qDebug() << "recalculating scene rect";
        // set the scene rect to contain all of the newly added items
        this->setSceneRect(this->itemsBoundingRect()
                           .adjusted(-blockMargin, -blockMargin, blockMargin, blockMargin));

        //qDebug() << "scene rect width 2:" << this->itemsBoundingRect().width();
        QRectF rect;

        //qDebug() << "getting current alignment";
        if(this->getCurrentAlignment() == Vertical) {
            //qDebug() << "vertical";
            rect = QRectF(this->sceneRect().left(),
                          this->sceneRect().bottom(),
                          this->sceneRect().width(),
                          1);
        } else {
            //qDebug() << "horizontal";
            rect = QRectF(this->sceneRect().right(),
                          this->sceneRect().top(),
                          1,
                          this->sceneRect().height());
        }

        //qDebug() << "Fit to Rect:" << rect;
        this->getParentGraphicsView()->fitInView(rect,Qt::KeepAspectRatio);
    }
}
