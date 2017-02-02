#include "rootitempathscene.h"

RootItemPathScene::RootItemPathScene()
{

}

RootItemPathScene::RootItemPathScene(QList<Block *> itemList, PathAlignment pa)
{
    rootPathList = itemList;
    for(int i = 0; i < rootPathList.count(); i++) {
        this->addItem(new Block(rootPathList.at(i)));
    }
    this->setCurrentAlignment(pa);
}

QList<Block *> RootItemPathScene::getList() const
{
    return rootPathList;
}

void RootItemPathScene::setList(const QList<Block *> &value)
{
    rootPathList = value;
    this->align(this->getCurrentAlignment());
}

void RootItemPathScene::align(PathAlignment pa)
{
    QPointF position(0,0);
    for(int i = 0; i < rootPathList.count(); i++) {

        Block *block = rootPathList.at(i);

        if(this->items().contains(block)) this->removeItem(block);

        block->setPos(position);

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
