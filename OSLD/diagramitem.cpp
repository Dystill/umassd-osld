#include "diagramitem.h"

DiagramItem::DiagramItem(QWidget *parent, QString id, QPointF loc)
{
    this->parent = parent;
    this->itemId = id;
    this->itemLocation = loc;
    this->setPos(loc);
}

QList<DiagramItem *> DiagramItem::getOutputItem() const
{
    return outputItem;
}

void DiagramItem::addOutputItem(DiagramItem *item)
{
    this->outputItem.append(item);
}

void DiagramItem::removeOutputItem(DiagramItem *item)
{
    for(int i = 0; i < this->outputItem.count(); i++) {
        if(item->id() == outputItem.at(i)->id()) {
            outputItem.removeAt(i);
        }
    }
}

QPointF DiagramItem::convertPointToRelative(QPointF loc, DiagramItem *anchor)
{
    QPointF temp;
    QPointF anchorPoint = anchor->location();

    temp.setX(loc.x() - anchorPoint.x());
    temp.setY(loc.y() - anchorPoint.y());

    return temp;
}

QPointF DiagramItem::convertPointToAbsolute(QPointF loc, DiagramItem *anchor)
{
    QPointF temp;
    QPointF anchorPoint = anchor->location();

    temp.setX(loc.x() + anchorPoint.x());
    temp.setY(loc.y() + anchorPoint.y());

    return temp;
}


















