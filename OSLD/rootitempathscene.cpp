#include "rootitempathscene.h"

RootItemPathScene::RootItemPathScene()
{

}

RootItemPathScene::RootItemPathScene(QList<Block *> itemList, PathAlignment pa)
{
    this->setCurrentAlignment(pa);
    this->setList(itemList);
}

QList<Block *> RootItemPathScene::getList() const
{
    return rootPathList;
}

void RootItemPathScene::setList(const QList<Block *> &itemList)
{
    // remove all items from the main root list from the scene
    for(int i = rootPathList.count() - 1; i >= 0; i--) {
        this->removeItem(rootPathList.at(i));
    }

    // clear all items in the root list from memory
    rootPathList.clear();

    // go through all of the items from the passed list
    for(int i = 0; i < itemList.count(); i++) {
        Block *block = new Block(itemList.at(i));   // create a copy block
        qDebug() << "block width:" << block->width();
        block->setIsInDiagram(false);               // set that it isn't in the main diagram
        rootPathList.append(block);                 // add the new block to the main list
    }

    // update the items, scene, and view
    this->updateItems();
}

void RootItemPathScene::align(PathAlignment pa)
{
    qDebug() << "aligning items";
    QPointF position(0,0);  // start at 0

    // go through each item in the root list
    for(int i = 0; i < rootPathList.count(); i++) {

        Block *block = rootPathList.at(i);

        if(this->items().contains(block)) this->removeItem(block);

        block->setPos(position);

        this->addItem(block);

        if(pa == Vertical)
            position.setY(position.y() + block->boundingRect().height() + blockMargin);
        else if(pa == Horizontal)
            position.setX(position.x() + block->boundingRect().width() + blockMargin);


        qDebug() << "scene rect width 1:" << this->itemsBoundingRect().width();
    }

    this->setCurrentAlignment(pa);
    this->update();
}

void RootItemPathScene::alignVertically()
{
    this->setCurrentAlignment(Vertical);
    this->updateItems();
}

void RootItemPathScene::alignHorizontally()
{
    this->setCurrentAlignment(Horizontal);
    this->updateItems();
}

PathAlignment RootItemPathScene::getCurrentAlignment() const
{
    return currentAlignment;
}

void RootItemPathScene::setCurrentAlignment(const PathAlignment &value)
{
    currentAlignment = value;
}

void RootItemPathScene::updateItems()
{
    qDebug() << "updating items";

    // add all of the items to the scene
    for(int i = 0; i < rootPathList.count(); i++) {
        this->addItem(rootPathList.at(i));
    }

    // align the items based on the current alignment
    this->align(this->getCurrentAlignment());

    // update the scene
    this->update();

    // fit the scene to the view
    this->fitToView();
}

QGraphicsView *RootItemPathScene::getParentGraphicsView() const
{
    return parentGraphicsView;
}

void RootItemPathScene::setParentGraphicsView(QGraphicsView *value)
{
    parentGraphicsView = value;
}

void RootItemPathScene::fitToView()
{
    qDebug() << "checking for view";
    if(this->getParentGraphicsView() != 0) {
        qDebug() << "view found, fitting to view";

        qDebug() << "recalculating scene rect";
        // set the scene rect to contain all of the newly added items
        this->setSceneRect(this->itemsBoundingRect()
                           .adjusted(-blockMargin, -blockMargin, blockMargin, blockMargin));

        qDebug() << "scene rect width 2:" << this->itemsBoundingRect().width();
        QRectF rect;

        qDebug() << "getting current alignment";
        if(this->getCurrentAlignment() == Vertical) {
            qDebug() << "vertical";
            rect = QRectF(this->sceneRect().left(),
                          this->sceneRect().bottom(),
                          this->sceneRect().width(),
                          1);
        } else {
            qDebug() << "horizontal";
            rect = QRectF(this->sceneRect().right(),
                          this->sceneRect().top(),
                          1,
                          this->sceneRect().height());
        }

        qDebug() << "Fit to Rect:" << rect;
        this->getParentGraphicsView()->fitInView(rect,Qt::KeepAspectRatio);
    }
}
