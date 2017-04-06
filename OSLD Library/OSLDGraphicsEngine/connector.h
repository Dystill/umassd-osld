#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QPainter>
#include <QtWidgets>
#include <QGraphicsWidget>
#include <QDebug>

class Connector : public QGraphicsWidget
{
private:
    QPointF startPoint; // where to begin drawing the line. should be used for the input item
    QPointF endPoint;   // where to end drawing the line. should be used for the output item

    QColor lineColor = QColor("#212121");   // the color to draw the line in. defaults to drak gray

public:
    Connector(QColor color = QColor("#212121"));    // blank initialization constructor. allows initializing the color
    Connector(QPointF input, QPointF output, QColor color = QColor("#212121")); // constructor to initialize endpoints and color

    // QGraphicsItem implementation classes
    QRectF boundingRect() const;
    void setGeometry(const QRectF &rect);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    // getters and setters
    QPointF start() const;
    void setStartPoint(const QPointF &value);

    QPointF end() const;
    void setEndPoint(const QPointF &value);

    QColor color() const;
    void setColor(const QColor &value);
};

#endif // CONNECTOR_H
