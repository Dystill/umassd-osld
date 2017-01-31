#ifndef ROOTITEMPATHSCENE_H
#define ROOTITEMPATHSCENE_H

#include "osldgraphicsengine.h"

class RootItemPathScene : public QGraphicsScene
{
private:
    QList<Block *> rootPathList;
public:
    RootItemPathScene();
    RootItemPathScene(QList<Block *> itemList);
    QList<Block *> getList() const;
    void setList(const QList<Block *> &value);
    void alignVertically();
    void alignHorizontally();
};

#endif // ROOTITEMPATHSCENE_H
