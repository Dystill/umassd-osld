#include "gate.h"

/*
 *  CONSTRUCTOR
 */

Gate::Gate(QWidget *parent, GateType type)
{
    gateType = type;            // set the gate type
}

Gate::Gate(QWidget *parent, QList<Block *> blocks, Block *output, GateType type)
{
    this->setParent(parent);
    this->setGateSizing(parent);

    inputBlocks = blocks;   // set the input blocks

    // loop through the inputBlocks to get their statuses
    for (int i = 0; i < blocks.count(); i++) {          // for each block in inputBlocks
        Block *block = inputBlocks.at(i);
        blockStatuses.insert(i, block->getOriginalStatus());    // insert that blocks status value to the corresponding spot in blockStatuses
        if(block->contains()) {
            containingIndex.append(i);                  // record the index of blocks with subdiagrams
        }
    }

    outputBlock = output;   // set the output block
    gateType = type;        // set the gate type

    this->updateOutputStatus();   // call the function to update the output status
}

/*
 *  Gate Sizing and Dimensions
 */

void Gate::setGateSizing(QWidget *parent)
{
    int dpiX = parent->logicalDpiX();
    int dpiY = parent->logicalDpiY();

    this->gateWidth = dpiX;
    this->gateHeight = dpiY;
    this->lineLength = dpiX / 1.5;
}

/*
 *  Gate QGraphicsWidget Functions
 */

QRectF Gate::boundingRect() const   // returns the dimensions of the containing rectangle
{
    return QRectF(0, 0, gateWidth + (lineLength * 2), gateHeight);
}

void Gate::setGeometry(const QRectF &rect)  // i don't know. don't touch this.
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(rect);
    setPos(rect.topLeft());
}

QSizeF Gate::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const   // returns the Qt size policy dimensions
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

// draw the gate onto the screen
void Gate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // gate colors
    QColor fillColor = QColor("#bbdefb");
    QColor outlineColor = QColor("#212121");

    // to draw the gate with
    QBrush brush(fillColor);
    QPen pen(outlineColor);
    pen.setWidth(2);    // outline thickness
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    // set the pen and brush
    painter->setPen(pen);
    painter->setBrush(brush);

    // draw lines coming out of the gate
    QPoint lineStart(boundingRect().left(), boundingRect().center().y());
    QPoint lineEnd(boundingRect().right(), boundingRect().center().y());
    painter->drawLine(lineStart, lineEnd);

    // create a path to outline the gate's shape
    QPainterPath *gatePath;

    // draw the path based on the type of gate that this gate was set to
    switch(gateType) {
    case AndGate:
        gatePath = drawANDGatePath();   // draw an AND gate shape
        break;
    case OrGate:
        gatePath = drawORGatePath();    // draw an OR gate shape
        break;
    default:
        break;
    }

    // draw the gate
    painter->drawPath(*gatePath);
}

QPainterPath *Gate::drawANDGatePath()
{
    QPointF topLeft(lineLength, 0);
    QPointF bottomLeft(lineLength, gateHeight);
    QPointF right(lineLength + gateWidth, gateHeight/2);
    QPointF middleTop(lineLength + (gateWidth/2), 0);
    QPointF middleBottom(lineLength + (gateWidth/2), gateHeight);

    QPainterPath *path = new QPainterPath(topLeft);

    // top edge
    path->lineTo(middleTop);

    // top-right curve
    path->cubicTo(QPointF(lineLength + (gateWidth*0.75), 0),
                  QPointF(lineLength + gateWidth, gateHeight*0.25), right);

    // bottom-right curve
    path->cubicTo(QPointF(lineLength + gateWidth, gateHeight*0.75),
                  QPointF(lineLength + (gateWidth*0.75), gateHeight), middleBottom);

    // bottom edge
    path->lineTo(bottomLeft);

    // left edge
    path->lineTo(topLeft);

    return path;
}

QPainterPath *Gate::drawORGatePath()
{
    QPointF topLeft(lineLength, 0);
    QPointF bottomLeft(lineLength, gateHeight);
    QPointF right(lineLength + gateWidth, gateHeight/2);
    QPointF inner(lineLength + gateWidth*0.25, gateHeight/2);

    QPainterPath *path = new QPainterPath(topLeft);

    // top curve
    path->cubicTo(QPointF(lineLength + (gateWidth*0.25), 0),
                  QPointF(lineLength + (gateWidth*0.75), 0), right);

    // bottom curve
    path->cubicTo(QPointF(lineLength + (gateWidth*0.75), gateHeight),
                  QPointF(lineLength + (gateWidth*0.25), gateHeight), bottomLeft);

    // inner-bottom quarter curve
    path->cubicTo(QPointF(lineLength + (gateWidth*0.125), gateHeight*0.90),
                  QPointF(lineLength + (gateWidth*0.25), gateHeight*0.725), inner);

    // inner-top quarter curve
    path->cubicTo(QPointF(lineLength + (gateWidth*0.25), gateHeight*0.275),
                  QPointF(lineLength + (gateWidth*0.125), gateHeight*0.10), topLeft);

    return path;
}

// add a block to the end of the block list
void Gate::addBlock(Block *b)
{
    inputBlocks.append(b);
}

// remove the block at the passed position in the list
void Gate::removeBlock(int pos)
{
    inputBlocks.removeAt(pos);
}

// remove the blocks with a title equal to the passed value
void Gate::removeBlock(QString title)
{
    for (int i = 0; i < inputBlocks.count(); i++) {
        if(!title.compare(inputBlocks.at(i)->getTitle())) {
            inputBlocks.removeAt(i);
        }
    }
}

QList<Block *> Gate::getInputBlocks() const
{
    return inputBlocks;
}

Block *Gate::getOutputBlock() const
{
    return outputBlock;
}

int Gate::getGateStatus()
{
    return outputStatus;
}

QString Gate::getGateStatusAsString()
{
    return "test";
}

GateType Gate::getGateType() const
{
    return gateType;
}

void Gate::setGateType(GateType value)
{
    gateType = value;
}

int Gate::width() const
{
    return gateWidth;
}

int Gate::height() const
{
    return gateHeight;
}

void Gate::updateOutputStatus()
{

}

int Gate::sizeOfBlocks(QList<Block *> blocks)
{
    return 0;
}

int Gate::getBlockCount()
{
    return inputBlocks.count();
}

QList<int> Gate::getContainingIndex() const
{
    return containingIndex;
}
