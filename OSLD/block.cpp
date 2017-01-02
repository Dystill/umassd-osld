#include "block.h"

/*
 *  CONSTRUCTOR
 */

Block::Block()
{
    title = "Default title";
    description = "Default description";
    hovertext = "Default hovertext";
    status = STATUS_VALID;
    contains = false;
    negated = false;
}

Block::Block(QString t, QString d, QString ht,
             int st = STATUS_VALID, bool c = false, bool n = true)
{
    title = t;
    description = d;
    hovertext = ht;
    status = st;
    contains = c;
    negated = n;
}

/*
 *  BLOCK DRAWING FUNCTIONS
 */

QRectF Block::boundingRect() const
{
    return QRectF(0, 0, 64, 256);
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    QBrush brush(this->color);

    painter->fillRect(rect, brush);
    painter->drawRect(rect);
}

void Block::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Block::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void Block::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{

}


/*
 *  GETTERS AND SETTERS
 */

// title
QString Block::getTitle() const
{
    return title;
}

void Block::setTitle(const QString &value)
{
    title = value;
}

// description
QString Block::getDescription() const
{
    return description;
}

void Block::setDescription(const QString &value)
{
    description = value;
}

// hovertext
QString Block::getHovertext() const
{
    return hovertext;
}

void Block::setHovertext(const QString &value)
{
    hovertext = value;
    this->setToolTip(hovertext);
}

// contains
bool Block::isContaining() const
{
    return contains;
}

void Block::setContains(bool value)
{
    contains = value;
}

// negated
bool Block::isNegated() const
{
    return negated;
}

void Block::setNegated(bool value)
{
    negated = value;
}

// status and color
int Block::getStatus() const
{
    return status;
}

QColor Block::getColor() const
{
    return color;
}

void Block::setStatus(int value)
{
    status = value;
    if(value == STATUS_VALID)
        color = QColor("#339933");
    else if(value == STATUS_INVALID)
        color = QColor("#CC3333");
    else if(value == STATUS_PENDING)
        color = QColor("#336699");
    else if(value == STATUS_WARNING)
        color = QColor("#CC6633");
    else
        color = QColor("#888888");
}
