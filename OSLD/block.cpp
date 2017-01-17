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

    // initialize items
    QRectF rect = boundingRect();   // box for the block
    QBrush brush(this->color);      // brush to fill the rectangle block
    QPen pen(QColor(this->color));    // pen to outlien the rectable block
    QTextOption texto;              // options for the title

    // set the pen
    pen.setWidth(2);                    // thickness
    pen.setCosmetic(true);              // same thickness with scaling
    pen.setJoinStyle(Qt::RoundJoin);    // rounded corners
    pen.setCapStyle(Qt::RoundCap);      // rounded line ends
    pen.setColor(QColor("#212121"));
    painter->setPen(pen);
    painter->setBrush(brush);

    //// Drawing the Connector entry lines
    // adjust the drawing rectangle to draw the connector lines and circles
    rect.setLeft(rect.left() + this->getCircleRadius());
    rect.setRight(rect.right() - this->getCircleRadius());

    // make points for the connector entry areas
    QPointF middleLeft = QPointF(rect.left(), rect.center().y());
    QPointF middleRight = QPointF(rect.right(), rect.center().y());

    // draw middle line
    painter->drawLine(middleLeft, middleRight);

    // draw the connector circles
    painter->drawEllipse(middleLeft, this->getCircleRadius(), this->getCircleRadius());
    painter->drawEllipse(middleRight, this->getCircleRadius(), this->getCircleRadius());

    //// Drawing the Block
    // resize the drawing rectangle to make the block
    rect.setLeft(rect.left() + this->getLineLength());
    rect.setRight(rect.right() - this->getLineLength());

    // draw the block
    painter->drawRect(rect);


    //// Drawing the Title text
    // create a textbox for the title
    QPointF textTopLeft(rect.left() + 10, rect.top());
    QPointF textBottomRight(rect.right() - 10, rect.bottom());
    QRectF textRect(textTopLeft, textBottomRight);

    // set some text flags
    texto.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);   // wordwrap
    texto.setAlignment(Qt::AlignCenter);                            // center align

    // set the color and font for the text
    pen.setColor(QColor("#FFFFFF"));
    painter->setFont(font);
    painter->setPen(pen);

    // draw the text
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
    qDebug() << "Mouse pressed onto" << this->title;
    DiagramItem::mousePressEvent(event);
}

void Block::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Mouse moving" << this->title;
    DiagramItem::mouseMoveEvent(event);
}

// when the user releases the mouse click
void Block::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Mouse released" << this->title;
    DiagramItem::mouseReleaseEvent(event);
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
