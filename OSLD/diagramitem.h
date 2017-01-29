#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QPainter>
#include <QtWidgets>
#include <QGraphicsWidget>
#include <QDebug>
#include "connector.h"

class Subdiagram;

class DiagramItem : public QGraphicsWidget
{
private:
    QWidget *itemParent;    // mainly used to obtain screen dpi
    QString itemId;     // the unique identifier for this item. cannot be changed once item is constructed

    QList<DiagramItem *> outputItem;    // the item this item outputs to if applicable

    QList<Connector *> inputConn;   // the set of connectors that lead into this item
    QList<Connector *> outputConn;  // the set of connectors that exit from this item

    QString status = "No Status Available";     // holds the text of the block's status, which is used to access a QMap of status/color combos
    QColor color = QColor("#888888");           // the color of the block is stored here for easier access
    QColor textColor;
    QString title;                              // the name of the step this block represents
    QString description;                        // the description of this block
    QString hovertext;                          // the text that shows when the user hovers over the block
    QPointF location = QPointF(0,0);

    Subdiagram *parentSubdiagram = 0;

    QFont font;         // font for the title text

    int maxWidth;                               // the maximum width of the block before word wraping the title


    int itemWidth;  // the width of this item
    int itemHeight; // the height of this item

    int circleRadius;
    int lineLength;

    bool block = false; // holds whether or not this item is a block
    bool gate = false;  // holds whether or not this item is a gate

public:
    // constructor
    DiagramItem(QWidget *parent, QString id, QPointF loc = QPointF(0, 0));  // requires the parent object and id. location defaults to (0,0)


    // QGraphicsItem stuff
    QRectF boundingRect() const;    // returns the rectagular container for this item
    void setGeometry(const QRectF &rect);   // used by QGraphicsItem to resize and update graphics elements
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;    // gives default sizes for items to use


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


    // getter and setter functions
    QString getTitle() const;
    void setTitle(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getStatus() const;
    QColor getColor() const;

    void setStatus(const QString &value, QMap<QString, QString> colorMap);  // sets both status and color. color cannot be changed directly

    QColor getTextColor() const;
    void setTextColor(const QColor &value);

    int getMaxWidth() const;
    void setMaxWidth(int value);

    QFont getFont() const;
    void setFont(const QFont &value);
    void setFontPointSize(int size);

    Subdiagram *getParentSubdiagram() const;
    void setParentSubdiagram(Subdiagram *value);

    QPointF getLocation() const;

protected:
    void setItemSizing(QString title);         // private function used to generate a size for this block that contains the title text

    void isBlock(bool value);   // set if this item is a block
    void isGate(bool value);    // set if this item is a gate

    int getCircleRadius() const;
    void setCircleRadius(int value);

    int getLineLength() const;
    void setLineLength(int value);

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

};

#endif // DIAGRAMITEM_H
