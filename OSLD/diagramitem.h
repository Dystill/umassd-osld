#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QPainter>
#include <QtWidgets>
#include <QGraphicsWidget>
#include <QDebug>
#include "connector.h"

class DiagramItem : public QGraphicsWidget
{
private:
    QWidget *itemParent;    // mainly used to obtain screen dpi
    QString itemId;     // the unique identifier for this item. cannot be changed once item is constructed

    QList<DiagramItem *> outputItem;    // the item this item outputs to if applicable

    QList<Connector *> inputConn;   // the set of connectors that lead into this item
    QList<Connector *> outputConn;  // the set of connectors that exit from this item

    int itemWidth;  // the width of this item
    int itemHeight; // the height of this item

    bool block = false; // holds whether or not this item is a block
    bool gate = false;  // holds whether or not this item is a gate

public:
    // constructor
    DiagramItem(QWidget *parent, QString id, QPointF loc = QPointF(0, 0));  // requires the parent object and id. location defaults to (0,0)

    //static QPointF convertPointToRelative(QPointF loc, DiagramItem *anchor);
    //static QPointF convertPointToAbsolute(QPointF loc, DiagramItem *anchor);

    QPointF inputPoint() const;     // returns the point that input connectors should lead into (the middle of the left edge)
    QPointF outputPoint() const;    // returns the point that output connectors should come out of (the middle of the right edge)

    QList<DiagramItem *> outputItems() const;   // returns the list of output items for this item
    void addOutputItem(DiagramItem *item);      // add an output item
    void removeOutputItem(DiagramItem *item);   // remove an output item


    void updateConnectors();    // updates graphics for all of the connectors connected to this item

    QList<Connector *> inputConnector() const;  // returns a list of all of the input connectors
    void addInputConnector(Connector *value);
    void removeInputConnector(Connector *value);

    QList<Connector *> outputConnector() const;  // returns a list of all of the output connectors
    void addOutputConnector(Connector *value);
    void removeOutputConnector(Connector *value);

    // getters and setters
    QWidget *parent() const;
    QString id() const;
    int width() const;
    void setWidth(int value);
    int height() const;
    void setHeight(int value);

    bool isBlock() const;
    bool isGate() const;

protected:
    void isBlock(bool value);   // set if this item is a block
    void isGate(bool value);    // set if this item is a gate

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

};

#endif // DIAGRAMITEM_H
