#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "diagramitem.h"

class Connector : public QGraphicsWidget
{
private:
    QPointF startPoint;
    QPointF endPoint;

    QColor lineColor;

public:
    Connector(DiagramItem *input, DiagramItem *output, QColor color = QColor("#212121"));

    QRectF boundingRect() const;
    void setGeometry(const QRectF &rect);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
};

#endif // CONNECTOR_H
