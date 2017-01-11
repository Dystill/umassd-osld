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
    ConnectType type;
    QPointF startPoint;
    QPointF endPoint;
    int numOfLines;
    int blockSpacing = 0;
    QList<QColor> colors;
    int fanWidth;

    void drawFanOutLines(QPainter *painter, QPen *pen);
    void setFanWidth(QWidget *parent);

public:
    static const int WIDTH = 48;

    // Overloaded Constructors
    Connector(QWidget *parent, QPointF start, QPointF end, QColor color = QColor("#212121"));                // single line
    Connector(QWidget *parent, int lines, int spacing, QColor color = QColor("#212121"));                    // fanout lines + single color
    Connector(QWidget *parent, int spacing, QList<QColor> colors);                                           // fanout lines + multicolor
    Connector(QWidget *parent, int spacing, QList<BlockStatus> status);                                      // fanout lines + multicolor alt

    QRectF boundingRect() const;
    void setGeometry(const QRectF &rect);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    int width() const;
};

#endif // CONNECTOR_H
