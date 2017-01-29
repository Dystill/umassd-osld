#include "block.h"

/*
 *  CONSTRUCTOR
 */

bool Block::isCurrentlyRoot() const
{
    return currentlyRoot;
}

void Block::setCurrentlyRoot(bool value)
{
    currentlyRoot = value;
}

Block::Block(QWidget *parent, QString id, QPointF loc, QString t, QString desc, QString ht)
    : DiagramItem(parent, id, loc)
{
    this->setMaxWidth(this->parent()->logicalDpiX() * 2);
    this->setFontPointSize(12);

    this->setTitle(t);
    this->setDescription(desc);
    this->setToolTip(ht);
    this->setBlockSizing(this->getTitle());

    this->isBlock(true);
}

/*
 *  Block Sizing and Dimensions
 */

void Block::setBlockSizing(QString title)
{
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

    // make points to place the connector entry circles
    QPointF middleLeft = QPointF(rect.left(), rect.center().y());
    QPointF middleRight = QPointF(rect.right(), rect.center().y());

    // draw the line crossing the block
    painter->drawLine(middleLeft, middleRight);

    // draw the connector circles
    painter->drawEllipse(middleLeft, this->getCircleRadius(), this->getCircleRadius());
    painter->drawEllipse(middleRight, this->getCircleRadius(), this->getCircleRadius());

    //// Drawing the Block
    // resize the painting area to make the block
    rect.setLeft(rect.left() + this->getLineLength());
    rect.setRight(rect.right() - this->getLineLength());

    // draw the block
    if(this->getSubdiagram() == 0) {
        painter->drawRect(rect);
    }
    else {
        // reset the painter so there's no brush color
        painter->setBrush(QBrush(Qt::transparent));

        // prepare a gradient going down the block
        QLinearGradient gradient(rect.center().x(), rect.top(), rect.center().x(), rect.bottom());
            gradient.setColorAt(0, this->getColor().lighter(150));
            gradient.setColorAt(0.25, this->getColor());
            gradient.setColorAt(0.75, this->getColor());
            gradient.setColorAt(1, this->getColor().darker(150));

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


Subdiagram *Block::getSubdiagram() const
{
    return subdiagram;
}

void Block::setSubdiagram(Subdiagram *value)
{
    subdiagram = value;
    this->update();
}

bool Block::hasSubdiagram() const
{
    if(subdiagram == 0) {
        return false;
    }
    else {
        return true;
    }
}


QPointF Block::getRootLocation() const
{
    return rootLocation;
}

void Block::setRootLocation(const QPointF &value)
{
    rootLocation = value;
}
