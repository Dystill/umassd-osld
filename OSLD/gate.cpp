#include "gate.h"

Gate::Gate(int type)
{
    gateType = type;            // set the gate type
}

Gate::Gate(QList<Block *> blocks, Block *output, int type)
{
    inputBlocks = blocks;   // set the input blocks
    outputBlock = output;   // set the output block
    gateType = type;        // set the gate type

    // loop through the inputBlocks to get their statuses
    for (int i = 0; i < blocks.count(); i++) {    // for each block in inputBlocks
        blockStatuses.insert(i, inputBlocks.at(i)->getStatus());     // insert that blocks status value to the corresponding spot in blockStatuses
    }

    this->updateOutputStatus();   // call the function to update the output status
}

QRectF Gate::boundingRect() const
{
    return QRectF(0, 0, WIDTH, HEIGHT);
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
        return QSizeF(WIDTH, HEIGHT);
    case Qt::PreferredSize:
        return QSizeF(WIDTH, HEIGHT);
    case Qt::MaximumSize:
        return QSizeF(1000,1000);
    default:
        break;
    }
    return constraint;
}

// draw the gate onto the screen (currently draws an AND cate)
void Gate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    prepareGeometryChange();

    // very hackish way of aligning the gate properly
    qreal downshift =
            (Block::HEIGHT * 1.5) * (inputBlocks.count() / 2.0) - (HEIGHT / 2.0);
    QRectF space = QRectF(0, downshift, WIDTH, HEIGHT);

    // gate colors
    QColor fillColor = QColor("#bbdefb");
    QColor outlineColor = QColor("#212121");

    // to draw the gate with
    QBrush brush(fillColor);
    QPen pen(outlineColor);
    pen.setWidth(2);    // outline thickness

    // for antialiasing
    painter->setRenderHint(QPainter::Antialiasing);

    // set the pen and brush
    painter->setPen(pen);
    painter->setBrush(brush);

    // draw the gate
    painter->drawEllipse(space);
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

int Gate::getGateType() const
{
    return gateType;
}

void Gate::setGateType(int value)
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
