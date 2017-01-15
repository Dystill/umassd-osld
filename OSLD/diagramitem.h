#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QPainter>
#include <QtWidgets>
#include <QGraphicsWidget>
#include <QDebug>

class DiagramItem : public QGraphicsWidget
{
private:
    QWidget *parent;
    QString itemId;

    QList<DiagramItem *> outputItem;

    int itemWidth;
    int itemHeight;

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

};

#endif // DIAGRAMITEM_H
