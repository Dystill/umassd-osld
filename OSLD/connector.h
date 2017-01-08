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
    ConnectType type;

public:
    static const int WIDTH = 128;

    Connector(QPointF start, QPointF end);
    Connector(int lines);

    QRectF boundingRect() const;
    void setGeometry(const QRectF &rect);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
};

#endif // CONNECTOR_H
