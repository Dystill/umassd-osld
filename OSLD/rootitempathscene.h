#ifndef ROOTITEMPATHSCENE_H
#define ROOTITEMPATHSCENE_H

#include "block.h"

enum PathAlignment {
    Vertical,
    Horizontal
};

class RootItemPathScene : public QGraphicsScene
{
private:
    QList<Block *> rootPathList;
    PathAlignment currentAlignment;
public:
    RootItemPathScene();
    RootItemPathScene(QList<Block *> itemList, PathAlignment pa = Vertical);
    QList<Block *> getList() const;
    void setList(const QList<Block *> &itemList);
    void align(PathAlignment pa);
    void alignVertically();
    void alignHorizontally();
    PathAlignment getCurrentAlignment() const;
    void setCurrentAlignment(const PathAlignment &value);
    void updateItems();
};

#endif // ROOTITEMPATHSCENE_H
