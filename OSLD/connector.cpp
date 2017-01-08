#include "connector.h"

Connector::Connector(QPointF start, QPointF end)
{
    startPoint = start;
    endPoint = end;
}

// constructor for drawing a fan of lines (going into a gate)
Connector::Connector(int lines)
{
    numOfLines = lines; // the number of lines needed to be drawn
    // the point that all lines will fan into
    endPoint = QPointF(WIDTH, ((Block::HEIGHT + Block::V_MARGIN) * numOfLines)/2);
    // letting the object know what type of line to draw
    type = FanOut;
}

// creating the containing rectangle to hold the lines
QRectF Connector::boundingRect() const
{
    if(type == FanOut) {
        return QRectF(0, 0, WIDTH, (Block::HEIGHT + Block::V_MARGIN) * numOfLines);
    }
    else if(type == Single) {
        if(startPoint.y() < endPoint.y()) {
            return QRectF(startPoint, endPoint);
        } else {
            QPointF topLeft(startPoint.x(), endPoint.y());
            QPointF bottomRight(endPoint.x(), startPoint.y());
            return QRectF(topLeft, bottomRight);
        }
    }
    else
        return QRectF();
}

// needed for QGraphicsItem
void Connector::setGeometry(const QRectF &rect)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(rect);
    setPos(rect.topLeft());
}

// broadcasting the size of the containing rectangle
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

// painting the lines
void Connector::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen;
    pen.setWidth(2);
    pen.setCapStyle(Qt::RoundCap);
    pen.setColor(QColor("#212121"));
    painter->setPen(pen);

    if(type == FanOut) {
        // create a starting point for the lines to draw
        QPointF start(0, 0);

        // draw the centermost line
        if(numOfLines % 2 == 1) {
            // a straight line if an odd number of blocks
            start.setY(endPoint.y());
        }
        else {
            // draw to the block below if there's an even number of blocks
            start.setY(endPoint.y() + ((Block::HEIGHT + Block::V_MARGIN + 2) / 2));
        }
        painter->drawLine(start, endPoint); // draw the line

        // a loop to draw the rest of the lines
        for(int i = 1; i < numOfLines; i++) {
            // alternate between drawing a line above and a line below the middle line
            if(i % 2 == 1) {    // below = subtract from y value
                start.setY(start.y() - ((Block::HEIGHT + Block::V_MARGIN + 1+ 4/numOfLines) * i));
            }
            else {              // above = add to y value
                start.setY(start.y() + ((Block::HEIGHT + Block::V_MARGIN + 1+ 4/numOfLines) * i));
            }
            painter->drawLine(start, endPoint); // draw each line
        }

        /* old code
        for(int i = 0; i < numOfLines; i++) {
            painter->drawLine(start, endPoint);
            start.setY(start.y() + Block::V_MARGIN + 4 + Block::HEIGHT);
        }
        */
    }

    // testing purposes - draw a dotted line around the connector container
    pen.setStyle(Qt::DotLine);
    painter->setPen(pen);
    painter->drawRect(boundingRect());

}




















