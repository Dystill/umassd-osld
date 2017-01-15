#include "connector.h"

Connector::Connector(DiagramItem *input, DiagramItem *output, QColor color)
{
    startPoint = input->outputPoint();
    endPoint = output->inputPoint();

    lineColor = color;
}


QRectF Connector::boundingRect() const
{
    QPointF topLeft(
                (startPoint.x() < endPoint.x() ? startPoint.x() : endPoint.x()),
                (startPoint.y() < endPoint.y() ? startPoint.y() : endPoint.y())
                );

    QPointF bottomRight(
                (startPoint.x() > endPoint.x() ? startPoint.x() : endPoint.x()),
                (startPoint.y() > endPoint.y() ? startPoint.y() : endPoint.y())
                );

    return QRectF(topLeft, bottomRight);
}

void Connector::setGeometry(const QRectF &rect)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(rect);
    setPos(rect.topLeft());
}

QSizeF Connector::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    switch (which) {
    case Qt::MinimumSize:
    case Qt::PreferredSize:
    case Qt::MaximumSize:
        return boundingRect().size();
    default:
        break;
    }
    return constraint;
}

void Connector::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen(lineColor);

    pen.setWidth(2);
    pen.setJoinStyle(Qt::RoundJoin);

    painter->setPen(pen);
    painter->drawLine(startPoint, endPoint);
}
