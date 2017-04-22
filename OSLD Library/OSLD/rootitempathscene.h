#ifndef ROOTITEMPATHSCENE_H
#define ROOTITEMPATHSCENE_H

#include "block.h"

class OSLDGraphicsEngine;

enum PathAlignment {
    Vertical,
    Horizontal
};

class RootItemPathScene : public QGraphicsScene
{
private:
    QList<Block *> rootPathList;
    PathAlignment currentAlignment;

    QGraphicsView *parentGraphicsView = 0;

    int blockMargin = 8;
    QColor backgroundColor = QColor("#fafafa");

    QGraphicsItem *pressedItem;
    OSLDGraphicsEngine *pairedDiagram;

public:
    RootItemPathScene();
    RootItemPathScene(OSLDGraphicsEngine *diagram, QList<Block *> itemList, PathAlignment pa = Vertical);
    QList<Block *> getList() const;
    void setList(const QList<Block *> &itemList);
    void align(PathAlignment pa);
    void alignVertically();
    void alignHorizontally();
    PathAlignment getCurrentAlignment() const;
    void setCurrentAlignment(const PathAlignment &value);
    void updateItems();
    QGraphicsView *getParentGraphicsView() const;
    void setParentGraphicsView(QGraphicsView *value);
    void fitToView();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // ROOTITEMPATHSCENE_H
