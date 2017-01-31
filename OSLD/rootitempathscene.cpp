#include "rootitempathscene.h"

RootItemPathScene::RootItemPathScene()
{

}

RootItemPathScene::RootItemPathScene(QList<Block *> itemList)
{
    rootPathList = itemList;
}

QList<Block *> RootItemPathScene::getList() const
{
    return rootPathList;
}

void RootItemPathScene::setList(const QList<Block *> &value)
{
    rootPathList = value;
}

void RootItemPathScene::alignVertically()
{

}

void RootItemPathScene::alignHorizontally()
{

}
