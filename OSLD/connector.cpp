#include "connector.h"

Connector::Connector(QPointF start, QPointF end, int spacing, QColor color)
{
    startPoint = start;
    endPoint = end;
    colors.append(color);
}

// constructor for drawing a fan of lines (going into a gate) with a single color
Connector::Connector(int lines, int spacing, QColor color)
{
    numOfLines = lines; // the number of lines needed to be drawn
    // the point that all lines will fan into
    endPoint = QPointF(WIDTH, (spacing * numOfLines)/2);
    // what type of line to draw
    type = FanOut;

    for (int i = 0; i < lines; i++) {
        colors.append(color);
    }

    this->blockSpacing = spacing;
}

// constructor for drawing a draw a fan of lines, each with a different color supplied by a QColor list
Connector::Connector(QList<QColor> color, int spacing)
{
    numOfLines = color.count();

    // the point that all lines will fan into
    endPoint = QPointF(WIDTH, (spacing * numOfLines)/2);

    // what type of line to draw
    type = FanOut;

    colors = color;

    this->blockSpacing = spacing;
}

// same a previous, but by parsing a BlockStatus list, added for convenience
Connector::Connector(QList<BlockStatus> status, int spacing)
{
    numOfLines = status.count();

    // the point that all lines will fan into
    endPoint = QPointF(WIDTH, (spacing * numOfLines)/2);

    // what type of line to draw
    type = FanOut;

    for (int i = 0; i < status.count(); i++) {
        colors.append(Block::parseColor(status.at(i)));
    }

    this->blockSpacing = spacing;
}

// creating the containing rectangle to hold the lines
QRectF Connector::boundingRect() const
{
    if(type == FanOut) {
        return QRectF(0, 0, WIDTH, blockSpacing * numOfLines);
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

    if(type == FanOut) {
        // create a starting point for the lines to draw
        QPointF start(0, 0);

        // to keep track of the current block connector being drawn
        int block = numOfLines / 2;

        // draw the centermost line
        if(numOfLines % 2 == 1) {
            // a straight line if an odd number of blocks
            start.setY(endPoint.y());
        }
        else {
            // draw to the block below if there's an even number of blocks
            start.setY(endPoint.y() + ((blockSpacing + 1.4) / 2));
        }
        pen.setColor(colors.at(block));
        painter->setPen(pen);
        painter->drawLine(start, endPoint); // draw the line

        // a loop to draw the rest of the lines
        for(int i = 1; i < numOfLines; i++) {
            // alternate between drawing a line above and a line below the middle line
            if(i % 2 == 1) {    // below = subtract from y value
                block -= i;
                start.setY(start.y() - ((blockSpacing + 0.6 + 4/numOfLines) * i));
            }
            else {              // above = add to y value
                block += i;
                start.setY(start.y() + ((blockSpacing + 0.6 + 4/numOfLines) * i));
            }
            // qDebug() << block;
            pen.setColor(colors.at(block));
            painter->setPen(pen);
            painter->drawLine(start, endPoint); // draw each line
        }
    }

    #if 0   // draw a rectangle around the containing space
    pen.setStyle(Qt::DotLine);
    painter->setPen(pen);
    painter->drawRect(boundingRect());
    #endif

}




















