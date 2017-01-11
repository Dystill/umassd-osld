#include "connector.h"

Connector::Connector(QWidget *parent, QPointF start, QPointF end, QColor color)
{
    startPoint = start;
    endPoint = end;
    colors.append(color);

    this->setParent(parent);
}

// constructor for drawing a fan of lines (going into a gate) with a single color
Connector::Connector(QWidget *parent, int lines, int spacing, QColor color)
{
    numOfLines = lines; // the number of lines needed to be drawn
    // the point that all lines will fan into
    endPoint = QPointF(fanWidth, (spacing * numOfLines)/2);
    // what type of line to draw
    type = FanOut;

    this->setParent(parent);

    for (int i = 0; i < lines; i++) {
        colors.append(color);
    }

    this->blockSpacing = spacing;
}

// constructor for drawing a draw a fan of lines, each with a different color supplied by a QColor list
Connector::Connector(QWidget *parent, int spacing, QList<QColor> colors)
{
    type = FanOut;  // what type of line to draw for this constructor

    this->setParent(parent);
    this->setFanWidth(parent);

    numOfLines = colors.count();    // get the number of lines from colors

    endPoint = QPointF(fanWidth, (spacing * numOfLines)/2);    // generate the point that all lines will fan into

    this->blockSpacing = spacing;   // save the passed in spacing amount

    this->colors = colors;  // save the passed in color list
}

// same a previous, but by parsing a BlockStatus list, added for convenience
Connector::Connector(QWidget *parent, int spacing, QList<BlockStatus> status)
{
    type = FanOut;  // what type of line to draw

    this->setParent(parent);
    this->setFanWidth(parent);

    numOfLines = status.count();    // get the number of lines from status

    endPoint = QPointF(fanWidth, (spacing * numOfLines)/2);    // generate the point that all lines will fan into

    this->blockSpacing = spacing;   // save the passed in spacing amount

    // get the colors for each status from the Block class
    for (int i = 0; i < status.count(); i++) {
        colors.append(Block::parseColor(status.at(i)));
    }
}

void Connector::setFanWidth(QWidget *parent)
{
    int dpiX = parent->logicalDpiX();

    this->fanWidth = dpiX / 1.5;
}

// creating the containing rectangle to hold the lines
QRectF Connector::boundingRect() const
{
    if(type == FanOut) {
        return QRectF(0, 0, fanWidth, blockSpacing * numOfLines);
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
        this->drawFanOutLines(painter, &pen);
    }

    #if 0   // draw a dotted rectangle around the containing space
    pen.setStyle(Qt::DotLine);
    painter->setPen(pen);
    painter->drawRect(boundingRect());
    #endif

}

// deprecated method of drawing the fanout lines
void Connector::drawFanOutLines(QPainter *painter, QPen *pen)
{
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
        start.setY(endPoint.y() + ((blockSpacing) / 2));
    }
    pen->setColor(colors.at(block));
    painter->setPen(*pen);
    painter->drawLine(start, endPoint); // draw the line

    // a loop to draw the rest of the lines
    for(int i = 1; i < numOfLines; i++) {
        // alternate between drawing a line above and a line below the middle line
        if(i % 2 == 1) {    // below = subtract from y value
            block -= i;
            start.setY(start.y() - ((blockSpacing) * i));
        }
        else {              // above = add to y value
            block += i;
            start.setY(start.y() + ((blockSpacing) * i));
        }
        // qDebug() << block;
        pen->setColor(colors.at(block));
        painter->setPen(*pen);
        painter->drawLine(start, endPoint); // draw each line
    }
}

int Connector::width() const
{
    return fanWidth;
}



















