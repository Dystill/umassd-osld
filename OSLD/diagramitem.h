#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QPainter>
#include <QtWidgets>
#include <QGraphicsWidget>
#include <QDebug>
#include "connector.h"

class Subdiagram;

// holds information about the external system being used for a diagram item
struct CommonSource {
    QString name;
    QString type;
};

// holds information about a specific status being used by this block
struct StatusTypes {
    QString color;
    QString textColor;
    bool    italics = false;
    bool    bold = false;
    bool    underline = false;
};

// holds information about what this diagram item will be displaying
struct DiagramItemData {
    QColor color = QColor("#888888");
    QColor textColor = QColor(Qt::black);

    QString title = "Default item title";
    QString description = "Default item description";
    QString hovertext = "Default item hovertext";

    // query attributes for name, description, and hovertext
    // these strings are sent alongside the item's IDs to the external source
    // the external source can then execute whatever is in these strings to find the data
    QString titleQuery;
    QString descriptionQuery;
    QString hovertextQuery;
    //

    bool italics = false;
    bool bold = false;
    bool underline = false;
};

class DiagramItem : public QGraphicsWidget
{
private:
    static bool transparentTitle;

    QString itemId;     // the unique identifier for this item. cannot be changed once item is constructed
    QString referenceId;     // the id used in place of id to get info from stimulator
    QString sourceId;     // the source for this item's information

    QList<DiagramItem *> outputItem;    // the item this item outputs to if applicable

    QList<Connector *> inputConn;   // the set of connectors that lead into this item
    QList<Connector *> outputConn;  // the set of connectors that exit from this item

    // data for this item
    QMap<QString, DiagramItemData> statusInfoDataList;  // a map of data to use for each status
    DiagramItemData currentStatusInfo;  // the current info to use for this diagram item
    QString currentStatus = "";  // holds the text of the block's status, which is used to access the data from the above map
                                 // initialized with "default_status" in the description file if available

    QPointF location = QPointF(0,0);

    Subdiagram *parentSubdiagram = 0;

    QFont font; // font for the title text
                // change font size by using setTitleSize()

    int maxWidth;       // the maximum width of the block before word wraping the title

    int itemWidth = 0;  // the width of this item
    int itemHeight = 0; // the height of this item

    int defaultWidth = 128;
    int defaultHeight = 64;

    int circleRadius = 0;   // radius of the circle used for input and output points
    int lineLength = 0;     // line to extend from input and output points

    QPointF inputPointOffset;    // offset for the input

    bool block = false; // holds whether or not this item is a block
    bool gate = false;  // holds whether or not this item is a gate

public:
    DiagramItem();
    // constructor
    DiagramItem(QString id, QPointF loc = QPointF(0, 0));  // requires the parent object and id. location defaults to (0,0)


    // QGraphicsItem stuff
    QRectF boundingRect() const;    // returns the rectagular container for this item
    void setGeometry(const QRectF &rect);   // used by QGraphicsItem to resize and update graphics elements
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;    // gives default sizes for items to use

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
    QString id() const;
    QString ref_id() const;
    int width() const;
    void setWidth(int value);
    int height() const;
    void setHeight(int value);

    bool isBlock() const;
    bool isGate() const;


    // getter and setter functions
    QString getTitle() const;

    QString getDescription() const;

    QString getStatus() const;
    QColor getColor() const;

    void setStatus(const QString &value, QMap<QString, StatusTypes> colorMap);  // sets both status and color
    void setColor(const QColor &value);

    QColor getTextColor() const;
    void setTextColor(QColor value);

    int getMaxWidth() const;

    QFont getFont() const;

    Subdiagram *getParentSubdiagram() const;
    void setParentSubdiagram(Subdiagram *value);

    QPointF getLocation() const;

    void setItalics(bool b);
    void setBold(bool b);
    void setUnderline(bool b);

    static bool isTransparent();
    static void setTransparent(bool value);

    int getLineLength() const;
    void setLineLength(int value);

    QPointF getInputPointOffset() const;
    void setInputPointOffset(const QPointF &value);

    void setStatusInfoDataList(const QMap<QString, DiagramItemData> &value);

    void updateStatusInfo();

    QString getSourceId() const;
    void setSourceId(const QString &value);

    void setLocation(const QPointF &value);

    void setItemSizing(int w, int h);

    void printQueries() const;

protected:
    void setItemSizing(QString title);          // private function used to generate a size for this block that contains the title text

    void setItemId(const QString &value);
    void setReferenceId(const QString &value);

    void isBlock(bool value);   // set if this item is a block
    void isGate(bool value);    // set if this item is a gate

    int getCircleRadius() const;
    void setCircleRadius(int value);

    int getDefaultWidth() const;
    void setDefaultWidth(int value);

    int getDefaultHeight() const;
    void setDefaultHeight(int value);

    void setTitle(QString value);
    void setDescription(QString value);
    void setMaxWidth(int value);

    void setTitleSize(int size);

    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
};

#endif // DIAGRAMITEM_H
