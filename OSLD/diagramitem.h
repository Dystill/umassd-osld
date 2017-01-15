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
    QWidget *parent;
    QString itemId;

    QList<DiagramItem *> outputItem;

    QList<Connector *> inputConn;
    QList<Connector *> outputConn;

    int itemWidth;
    int itemHeight;

    bool block = false;
    bool gate = false;

public:
    DiagramItem(QWidget *parent, QString id, QPointF loc = QPointF(0, 0));

    //static QPointF convertPointToRelative(QPointF loc, DiagramItem *anchor);
    //static QPointF convertPointToAbsolute(QPointF loc, DiagramItem *anchor);

    QPointF inputPoint() const;
    QPointF outputPoint() const;

    QList<DiagramItem *> outputItems() const;
    void addOutputItem(DiagramItem *item);
    void removeOutputItem(DiagramItem *item);

    // getters and setters
    QString id() const;
    int width() const;
    void setWidth(int value);
    int height() const;
    void setHeight(int value);

    void updateConnectors();

    QList<Connector *> inputConnector() const;
    void addInputConnector(Connector *value);

    QList<Connector *> outputConnector() const;
    void addOutputConnector(Connector *value);

    bool isBlock() const;
    bool isGate() const;

protected:
    void isBlock(bool value);
    void isGate(bool value);

};

#endif // DIAGRAMITEM_H
