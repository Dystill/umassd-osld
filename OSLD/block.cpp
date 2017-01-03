#include "block.h"

/*
 *  CONSTRUCTOR
 */

Block::Block(QString t  = "Default title",
             QString d  = "Default description",
             QString ht = "Default hovertext",
             int st = STATUS_VALID, bool c = false, bool n = true)
{
    this->setTitle(t);
    this->setDescription(d);
    this->setHovertext(ht);
    this->setStatus(st);
    this->setContains(c);
    this->setNegated(n);

    this->setFlag(ItemIsSelectable);
}

/*
 *  BLOCK DRAWING FUNCTIONS
 */

QRectF Block::boundingRect() const
{
    return QRectF(0, 0, 128, 32);
}

// paint shapes in the block
void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    QBrush brush(this->color);
    QPen pen(textColor);
    QTextOption texto(Qt::AlignCenter);

    painter->setPen(pen);

    painter->fillRect(rect, brush);
    painter->drawRect(rect);
    painter->drawText(rect, this->title, texto);

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

void Block::setStatus(int value)    // sets the status and color for a block
{
    // set the status attribute to the value
    status = value;

    // sets the block color and the text color depending on the value
    if(value == STATUS_VALID) {
        color = QColor("#339933");
        textColor = QColor("#F1F1F1");
    } else if(value == STATUS_INVALID) {
        color = QColor("#CC3333");
        textColor = QColor("#F1F1F1");
    } else if(value == STATUS_PENDING) {
        color = QColor("#336699");
        textColor = QColor("#F1F1F1");
    } else if(value == STATUS_WARNING) {
        color = QColor("#CC6633");
        textColor = QColor("#F1F1F1");
    } else {
        color = QColor("#888888");
        textColor = QColor("#F1F1F1");
    }
}
