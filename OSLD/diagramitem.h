#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QPainter>
#include <QtWidgets>
#include <QGraphicsWidget>
#include <QDebug>

enum ItemLayout {
    Absolute,
    Relative
};

class DiagramItem : public QGraphicsWidget
{
private:
    QWidget *parent;
    QString itemId;

    QList<DiagramItem *> outputItem;

    QPointF itemLocation;
    QPointF anchorPoint = QPointF(0, 0);
    ItemLayout layout;

    int itemWidth;
    int itemHeight;

public:
    DiagramItem(QWidget *parent, QString id, QPointF loc = QPointF(0, 0));

    static QPointF convertPointToRelative(QPointF loc, DiagramItem *anchor);
    static QPointF convertPointToAbsolute(QPointF loc, DiagramItem *anchor);

    QList<DiagramItem *> getOutputItem() const;
    void addOutputItem(DiagramItem *item);
    void removeOutputItem(DiagramItem *item);

    // getters and setters
    QString id() const { return itemId; }
    int width() const { return itemWidth; }
    void setWidth(int value) { itemWidth = value; }
    int height() const { return itemHeight; }
    void setHeight(int value) { itemHeight = value; }
    QPointF location() const { return itemLocation; }
    void setLocation(const QPointF &value) { itemLocation = value;
                                             this->setPos(itemLocation); }
    ItemLayout itemLayout() const { return layout; }
    void setItemLayout(const ItemLayout &value) { layout = value; }
};

#endif // DIAGRAMITEM_H
