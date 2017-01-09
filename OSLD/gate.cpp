#include "gate.h"

Gate::Gate(GateType type)
{
    gateType = type;            // set the gate type
}

Gate::Gate(QList<Block *> blocks, Block *output, GateType type)
{
    inputBlocks = blocks;   // set the input blocks

    // loop through the inputBlocks to get their statuses
    for (int i = 0; i < blocks.count(); i++) {          // for each block in inputBlocks
        Block *block = inputBlocks.at(i);
        blockStatuses.insert(i, block->getOriginalStatus());    // insert that blocks status value to the corresponding spot in blockStatuses
        if(block->isContaining()) {
            containingIndex.append(i);                  // record the index of blocks with subdiagrams
        }
    }

    outputBlock = output;   // set the output block
    gateType = type;        // set the gate type

    this->updateOutputStatus();   // call the function to update the output status
}

QList<int> Gate::getContainingIndex() const
{
    return containingIndex;
}

QRectF Gate::boundingRect() const
{
    return QRectF(0, 0, WIDTH + (LINE_LENGTH * 2), HEIGHT);
}

void Gate::setGeometry(const QRectF &rect)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(rect);
    setPos(rect.topLeft());
}

QSizeF Gate::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
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

// draw the gate onto the screen (currently draws an AND cate)
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
    QPointF topLeft(LINE_LENGTH, 0);
    QPointF bottomLeft(LINE_LENGTH, HEIGHT);
    QPointF right(LINE_LENGTH + WIDTH, HEIGHT/2);
    QPointF middleTop(LINE_LENGTH + (WIDTH/2), 0);
    QPointF middleBottom(LINE_LENGTH + (WIDTH/2), HEIGHT);

    QPainterPath *path = new QPainterPath(topLeft);

    // top edge
    path->lineTo(middleTop);

    // top-right curve
    path->cubicTo(QPointF(LINE_LENGTH + (WIDTH*0.75), 0),
                  QPointF(LINE_LENGTH + WIDTH, HEIGHT*0.25), right);

    // bottom-right curve
    path->cubicTo(QPointF(LINE_LENGTH + WIDTH, HEIGHT*0.75),
                  QPointF(LINE_LENGTH + (WIDTH*0.75), HEIGHT), middleBottom);

    // bottom edge
    path->lineTo(bottomLeft);

    // left edge
    path->lineTo(topLeft);

    return path;
}

QPainterPath *Gate::drawORGatePath()
{
    QPointF topLeft(LINE_LENGTH, 0);
    QPointF bottomLeft(LINE_LENGTH, HEIGHT);
    QPointF right(LINE_LENGTH + WIDTH, HEIGHT/2);
    QPointF inner(LINE_LENGTH + WIDTH*0.25, HEIGHT/2);

    QPainterPath *path = new QPainterPath(topLeft);

    // top curve
    path->cubicTo(QPointF(LINE_LENGTH + (WIDTH*0.25), 0),
                  QPointF(LINE_LENGTH + (WIDTH*0.75), 0), right);

    // bottom curve
    path->cubicTo(QPointF(LINE_LENGTH + (WIDTH*0.75), HEIGHT),
                  QPointF(LINE_LENGTH + (WIDTH*0.25), HEIGHT), bottomLeft);

    // inner-bottom quarter curve
    path->cubicTo(QPointF(LINE_LENGTH + (WIDTH*0.125), HEIGHT*0.90),
                  QPointF(LINE_LENGTH + (WIDTH*0.25), HEIGHT*0.725), inner);

    // inner-top quarter curve
    path->cubicTo(QPointF(LINE_LENGTH + (WIDTH*0.25), HEIGHT*0.275),
                  QPointF(LINE_LENGTH + (WIDTH*0.125), HEIGHT*0.10), topLeft);

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
