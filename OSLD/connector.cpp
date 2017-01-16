#include "connector.h"

Connector::Connector(QColor color)
{
    startPoint = QPointF();
    endPoint = QPointF();

    lineColor = color;
}

Connector::Connector(QPointF input, QPointF output, QColor color)
{
    startPoint = input;
    endPoint = output;

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
    pen.setCapStyle(Qt::RoundCap);

    painter->setPen(pen);
    painter->drawLine(startPoint, endPoint);
}


QPointF Connector::start() const
{
    return startPoint;
}

void Connector::setStartPoint(const QPointF &value)
{
    prepareGeometryChange();
    startPoint = value;
    this->update();
    //qDebug() << "Start point changed to:" << startPoint;
}

QPointF Connector::end() const
{
    return endPoint;
}

void Connector::setEndPoint(const QPointF &value)
{
    prepareGeometryChange();
    endPoint = value;
    this->update();
    //qDebug() << "End point changed to:" << endPoint;
}

QColor Connector::color() const
{
    return lineColor;
}

void Connector::setColor(const QColor &value)
{
    lineColor = value;
}
