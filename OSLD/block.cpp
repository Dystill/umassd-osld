#include "block.h"

/*
 *  CONSTRUCTOR
 */
Block::Block(QWidget *parent, QString id, QPointF loc, QString t, QString desc, QString ht)
    : DiagramItem(parent, id, loc)
{
    this->maxWidth = (this->parent()->logicalDpiX() * 2);
    this->font.setPointSize(12);

    this->title = t;
    this->description = desc;
    this->setToolTip(ht);
    this->setBlockSizing(this->title);

    this->isBlock(true);
}

/*
 *  Block Sizing and Dimensions
 */

void Block::setBlockSizing(QString title)
{
    QFontMetricsF metrics(font);

    qreal textWidth = metrics.boundingRect(title).width();
    qreal textHeight = metrics.boundingRect(title).height();

    //qDebug() << "textWidth:" << title;
    //qDebug() << "textWidth:" << textWidth;
    //qDebug() << "textHeight:" << textHeight;

    int cutOff = textWidth / this->maxWidth;

    this->setWidth(((textWidth > maxWidth) ? maxWidth : textWidth) + (this->parent()->logicalDpiX() / 2));
    this->setHeight((((textHeight * cutOff)) + 1) + (this->parent()->logicalDpiY() / 2));

    this->update();
    this->updateConnectors();
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
    this->updateConnectors();
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

    QBrush brush(this->color);
    QPen pen(QColor("#212121"));
    QTextOption texto;

    texto.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    texto.setAlignment(Qt::AlignCenter);

    pen.setWidth(2);
    pen.setCosmetic(true);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);

    painter->setPen(pen);
    painter->setFont(font);
    painter->fillRect(boundingRect(), brush);
    painter->drawRect(boundingRect());

    QPointF textTopLeft(boundingRect().left() + 10, boundingRect().top());
    QPointF textBottomRight(boundingRect().right() - 10, boundingRect().bottom());
    QRectF textRect(textTopLeft, textBottomRight);

    pen.setColor(QColor("#FFFFFF"));
    painter->setPen(pen);
    painter->drawText(textRect, this->title, texto);

    //qDebug() << this->inputPoint();
    //qDebug() << this->outputPoint();
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
    this->title = value;
    this->setBlockSizing(this->title);
}

QString Block::getDescription() const
{
    return description;
}

void Block::setDescription(const QString &value)
{
    description = value;
}

QString Block::getStatus() const
{
    return status;
}

void Block::setStatus(const QString &value, QMap<QString, QString> colorMap)
{
    //qDebug() << value;
    status = value;

    //qDebug() << colorMap[status];
    color = QColor(colorMap[status]);
}

QColor Block::getColor() const
{
    return color;
}
