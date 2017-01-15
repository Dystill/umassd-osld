#include "block.h"

/*
 *  CONSTRUCTOR
 */
Block::Block(QWidget *parent, QString id, QPointF loc, QString t, QString desc, QString ht)
    : DiagramItem(parent, id, loc)
{
    this->title = t;
    this->description = desc;
    this->hovertext = ht;
    this->setBlockSizing(parent);
}

/*
 *  Block Sizing and Dimensions
 */

void Block::setBlockSizing(QWidget *parent)
{
    int dpiX = parent->logicalDpiX();
    int dpiY = parent->logicalDpiY();

    this->setWidth(dpiX * 2);
    this->setHeight(dpiY / 2);
}


/*
 *  Block QGraphicsWidget Functions
 */

QRectF Block::boundingRect() const
{
    return QRectF(0, 0, this->width(), this->height());
}

void Block::setGeometry(const QRectF &rect)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(rect);
    setPos(rect.topLeft());
}

QSizeF Block::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
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

// paint shapes in the block
void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawRect(boundingRect());
}


/*
 * MOUSE EVENTS
 */

// when the user clicks down on a block
void Block::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

// when the user releases the mouse click
void Block::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

// when the user double clicks
void Block::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseDoubleClickEvent(event);
}

/*
 * GETTERS & SETTERS
 */

QString Block::getTitle() const
{
    return title;
}

void Block::setTitle(const QString &value)
{
    title = value;
}

QString Block::getDescription() const
{
    return description;
}

void Block::setDescription(const QString &value)
{
    description = value;
}

QString Block::getHovertext() const
{
    return hovertext;
}

void Block::setHovertext(const QString &value)
{
    hovertext = value;
}

QString Block::getStatus() const
{
    return status;
}

void Block::setStatus(const QString &value)
{
    status = value;
}

QColor Block::getColor() const
{
    return color;
}

void Block::setColor(const QColor &value)
{
    color = value;
}
