#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QPainter>
#include <QGraphicsWidget>
#include <block.h>

enum ConnectType {
    FanOut,
    Single
};

class Connector : public QGraphicsWidget
{
private:
    QPointF startPoint;
    QPointF endPoint;
    int numOfLines;
    QList<QColor> colors;
    ConnectType type;
    int blockSpacing;

public:
    static const int WIDTH = 48;

    Connector(QPointF start, QPointF end, int spacing, QColor color = QColor("#212121"));
    Connector(int lines, int spacing, QColor color = QColor("#212121"));
    Connector(QList<BlockStatus> status, int spacing);
    Connector(QList<QColor> color, int spacing);

    QRectF boundingRect() const;
    void setGeometry(const QRectF &rect);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
};

#endif // CONNECTOR_H
