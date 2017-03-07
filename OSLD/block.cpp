#include "block.h"

/*
 *  CONSTRUCTOR
 */

bool Block::isInDiagram() const
{
    return inDiagram;
}

void Block::setIsInDiagram(bool value)
{
    inDiagram = value;
    if(!value) {
        this->setCircleRadius(0);
        this->setLineLength(0);
    }
}

Block::Block(QString id, QPointF loc, QString t, QString desc, QString ht)
    : DiagramItem(id, loc)
{
    this->setMaxWidth(256);
    this->setTitleSize(16);

    this->setTitle(t);
    this->setDescription(desc);
    this->setToolTip(ht);
    this->setBlockSizing(this->getTitle());

    this->isBlock(true);
}

Block::Block(Block *block) : DiagramItem() {
    this->setMaxWidth(256);
    this->setTitleSize(16);

    this->setTitle(block->getTitle());
    this->setDescription(block->getDescription());
    this->setToolTip(block->toolTip());
    this->setColor(block->getColor());  // sets color directly instead of using a status
    this->setTextColor(block->getTextColor());
    this->setBold(block->getFont().bold());
    this->setItalics(block->getFont().italic());
    this->setUnderline(block->getFont().underline());
    this->setWidth(block->width());
    this->setHeight(block->height());

    this->isBlock(true);
}

/*
 *  Block Sizing and Dimensions
 */

void Block::setBlockSizing(QString title)
{
    this->setInputPointOffset(QPointF(this->width() / 4,0));
    DiagramItem::setItemSizing(title);
}


/*
 *  Block QGraphicsWidget Functions
 */

QRectF Block::boundingRect() const
{
    return DiagramItem::boundingRect();
}

void Block::setGeometry(const QRectF &rect)
{
    DiagramItem::setGeometry(rect);
}

QSizeF Block::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    return DiagramItem::sizeHint(which, constraint);
}

// paint shapes in the block
void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // initialize painting area to the bounding rectangle
    QRectF rect = boundingRect();
    QTextOption texto;              // options for the title text

    // set the pen to draw lines
    QPen pen(QColor("#212121"));    // pen to outline the rectable block
    pen.setWidth(2);                    // thickness
    pen.setCosmetic(true);              // same thickness with scaling
    pen.setJoinStyle(Qt::RoundJoin);    // rounded corners
    pen.setCapStyle(Qt::RoundCap);      // rounded line ends
    painter->setPen(pen);

    // set the brush to fill areas with the status color
    QBrush brush(this->getColor());      // brush to fill the rectangle block
    painter->setBrush(brush);

    //// Drawing the Connector entry lines
    // adjust the painting area to draw the connector lines and circles
    rect.setLeft(rect.left() + this->getCircleRadius());
    rect.setRight(rect.right() - this->getCircleRadius());

    if(inDiagram) {
        // make points to place the connector entry circles
        QPointF middleLeft = QPointF(rect.left(), rect.center().y());
        QPointF middleRight = QPointF(rect.right(), rect.center().y());

        // draw the line crossing the block
        painter->drawLine(middleLeft, middleRight);

        // draw the connector circles
        painter->drawEllipse(middleLeft, this->getCircleRadius(), this->getCircleRadius());
        painter->drawEllipse(middleRight, this->getCircleRadius(), this->getCircleRadius());
    }

    //// Drawing the Block
    // resize the painting area to make the block
    rect.setLeft(rect.left() + this->getLineLength());
    rect.setRight(rect.right() - this->getLineLength());

    // draw the block
    if(this->getChildSubdiagram() == 0) {
        painter->drawRect(rect);
    }
    else {
        // reset the painter so there's no brush color
        painter->setBrush(QBrush(Qt::transparent));

        // prepare a gradient going down the block
        QLinearGradient gradient(rect.center().x(), rect.top(), rect.center().x(), rect.bottom());
            gradient.setColorAt(0, this->getColor().lighter(150));
            gradient.setColorAt(0.45, this->getColor());
            gradient.setColorAt(0.65, this->getColor());
            gradient.setColorAt(1, this->getColor().darker(175));

        painter->fillRect(rect, gradient);
        painter->drawRect(rect);
    }

    //// Drawing the Title text
    // create a textbox for the title
    QPointF textTopLeft(rect.left() + 10, rect.top());
    QPointF textBottomRight(rect.right() - 10, rect.bottom());
    QRectF textRect(textTopLeft, textBottomRight);

    // set some text flags
    texto.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);   // wordwrap
    texto.setAlignment(Qt::AlignCenter);                            // center align

    // set the color and font for the text
    if(this->isTransparent() && this->isInDiagram())
        pen.setColor(Qt::transparent);
    else
        pen.setColor(this->getTextColor());

    painter->setFont(this->getFont());
    painter->setPen(pen);

    // draw the text
    painter->drawText(textRect, this->getTitle(), texto);

    //qDebug() << this->inputPoint();
    //qDebug() << this->outputPoint();
}


/*
 * MOUSE EVENTS
 */

// when the user clicks down on a block
void Block::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    DiagramItem::mousePressEvent(event);
}

void Block::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    DiagramItem::mouseMoveEvent(event);
}

// when the user releases the mouse click
void Block::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->isCurrentlyRoot()) {
        this->setRootLocation(this->pos());
        QGraphicsItem::mouseReleaseEvent(event);
    }
    else {
        DiagramItem::mouseReleaseEvent(event);
    }
}


Subdiagram *Block::getChildSubdiagram() const
{
    return childSubdiagram;
}

void Block::setChildSubdiagram(Subdiagram *value)
{
    childSubdiagram = value;
    this->setCursor(Qt::PointingHandCursor);
    this->update();
}

bool Block::hasChildSubdiagram() const
{
    if(childSubdiagram == 0) {
        return false;
    }
    else {
        return true;
    }
}


// returns the location this block should be at when it is the root item
QPointF Block::getRootLocation() const
{
    return rootLocation;
}

void Block::setRootLocation(const QPointF &value)
{
    rootLocation = value;
}


// returns true if this item is the root item of the currently displayed subdiagram
bool Block::isCurrentlyRoot() const
{
    return currentlyRoot;
}

void Block::setCurrentlyRoot(bool value)
{
    currentlyRoot = value;
}
