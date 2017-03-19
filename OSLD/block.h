#ifndef BLOCK_H
#define BLOCK_H

#include <QDebug>
#include "diagramitem.h"

class Subdiagram;

class Block : public DiagramItem
{
private:
    Subdiagram *childSubdiagram = 0; // holds subdiagram if this block has one
    QPointF rootLocation = QPointF(0,0);
    bool currentlyRoot = false;
    bool inDiagram = true;

public:
    // constructor
    Block(QString id, QPointF loc,     // blocks must have at least the id and location
          QString t = "Block Title",
          QString desc = "Block Description",
          QString ht = "Block Hovertext");
    Block(Block *block);    // copy constructor

    // QGraphicsItem stuff
    QRectF boundingRect() const;    // returns the rectagular container for this item
    void setGeometry(const QRectF &rect);   // used by QGraphicsItem to resize and update graphics elements
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;    // gives default sizes for items to use
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,   // paints the graphics to use for the object
               QWidget *widget);

    Subdiagram *getChildSubdiagram() const;
    void setChildSubdiagram(Subdiagram *value);
    bool hasChildSubdiagram() const;

    QPointF getRootLocation() const;
    void setRootLocation(const QPointF &value);

    bool isCurrentlyRoot() const;
    void setCurrentlyRoot(bool value);

    bool isInDiagram() const;
    void setIsInDiagram(bool value);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void setBlockSizing(QString title);

signals:

public slots:
};

#endif // BLOCK_H
