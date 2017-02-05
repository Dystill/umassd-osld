#include "rootitempathscene.h"

RootItemPathScene::RootItemPathScene()
{

}

RootItemPathScene::RootItemPathScene(QList<Block *> itemList, PathAlignment pa)
{
    for(int i = 0; i < itemList.count(); i++) {
        rootPathList.append(new Block(itemList.at(i)));
        qDebug() << "root list adding" << rootPathList.at(i)->getTitle();
    }
    this->setCurrentAlignment(pa);
    this->updateItems();
}

QList<Block *> RootItemPathScene::getList() const
{
    return rootPathList;
}

void RootItemPathScene::setList(const QList<Block *> &itemList)
{
    qDebug() << "deleting items total:" << rootPathList.count();
    for(int i = rootPathList.count() - 1; i >= 0; i--) {
        qDebug() << "removing item" << i;
        qDebug() << rootPathList.at(i)->getTitle();
        this->removeItem(rootPathList.at(i));
    }
    qDebug() << "deleting list";
    rootPathList.clear();
    qDebug() << "deleted list";
    for(int i = 0; i < itemList.count(); i++) {
        qDebug() << "adding item" << itemList.at(i)->getTitle();
        rootPathList.append(new Block(itemList.at(i)));
    }
    qDebug() << "finished setting list";
}

void RootItemPathScene::align(PathAlignment pa)
{
    qDebug() << "aligning items";
    QPointF position(0,0);
    for(int i = 0; i < rootPathList.count(); i++) {

        Block *block = rootPathList.at(i);

        if(this->items().contains(block)) this->removeItem(block);

        block->setPos(position);

        block->setLineLength(0);

        this->addItem(block);

        if(pa == Vertical)
            position.setY(position.y() + block->boundingRect().height());
        else if(pa == Horizontal)
            position.setX(position.x() + block->boundingRect().width());
    }

    this->setCurrentAlignment(pa);
    this->update();
}

void RootItemPathScene::alignVertically()
{
    QPointF position(0,0);
    for(int i = 0; i < rootPathList.count(); i++) {
        Block *block = rootPathList.at(i);
        this->removeItem(block);
        block->setPos(position);
        block->setLineLength(0);
        this->addItem(block);
        position.setY(position.y() + block->boundingRect().height());
    }
    this->setCurrentAlignment(Vertical);
    this->update();
}

void RootItemPathScene::alignHorizontally()
{
    QPointF position(0,0);
    for(int i = 0; i < rootPathList.count(); i++) {
        Block *block = rootPathList.at(i);
        this->removeItem(block);
        block->setPos(position);
        block->setLineLength(0);
        this->addItem(block);
        position.setX(position.x() + block->boundingRect().width());
    }
    this->setCurrentAlignment(Horizontal);
    this->update();
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
    for(int i = 0; i < rootPathList.count(); i++) {
        qDebug() << "root list displaying" << i;
        qDebug() << rootPathList.at(i)->getTitle();
        this->addItem(rootPathList.at(i));
    }
    this->align(this->getCurrentAlignment());
    this->update();
}
