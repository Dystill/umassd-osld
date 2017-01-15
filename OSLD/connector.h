#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QPainter>
#include <QtWidgets>
#include <QGraphicsWidget>
#include <QDebug>

class Connector : public QGraphicsWidget
{
private:
    QPointF startPoint;
    QPointF endPoint;

    QColor lineColor;

public:
    Connector(QColor color = QColor("#212121"));
    Connector(QPointF input, QPointF output, QColor color = QColor("#212121"));

    QRectF boundingRect() const;
    void setGeometry(const QRectF &rect);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    QPointF getStartPoint() const;
    void setStartPoint(const QPointF &value);

    QPointF getEndPoint() const;
    void setEndPoint(const QPointF &value);

    QColor color() const;
    void setColor(const QColor &value);
};

#endif // CONNECTOR_H
