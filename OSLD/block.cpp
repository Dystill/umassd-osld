#include "block.h"

/*
 *  CONSTRUCTOR
 */

Block::Block(QString t, QString d, QString ht,
             int st, bool c, bool n)
{
    this->setTitle(t);
    this->setDescription(d);
    this->setHovertext(ht);
    this->setStatus(st);
    this->setContains(c);
    this->setNegated(n);

    this->textFont.setPointSize(12);
}

/*
 *  BLOCK DRAWING FUNCTIONS
 */

QRectF Block::boundingRect() const
{
    return QRectF(0, 0, WIDTH, HEIGHT + MARGIN * 2);
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
        return QSizeF(WIDTH, HEIGHT + MARGIN * 2);
    default:
        break;
    }
    return constraint;
}

// paint shapes in the block
void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // create a new rectangle space to draw in
    QRectF rect = QRectF(0, MARGIN, WIDTH, HEIGHT);

    // create a color for the outline
    QColor outlineColor = QColor("#212121");

    // create a brush to fill the block with a status color
    QBrush brush(this->color);

    // create a pen for the title text and border
    QPen pen(outlineColor);
    pen.setWidth(2);

    // to set options for the title text
    QTextOption texto(Qt::AlignCenter);
    texto.setWrapMode(QTextOption::NoWrap);

    // set the pen for the painter
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);

    // fill the block with the brush color
    painter->fillRect(rect, brush);

    // draw an outline around the block
    painter->drawRect(rect);

    // add text with the block's title
    pen.setColor(textColor);
    painter->setFont(textFont);
    painter->setPen(pen);
    painter->drawText(rect, this->title, texto);

}

/*
 * MOUSE EVENTS
 */

// when the user clicks down on a block
void Block::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

// when the user releases the mouse click
void Block::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
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
        color = STATUS_VALID_COLOR;         // valid color green
        textColor = QColor("#F1F1F1");
    }
    else if(value == STATUS_INVALID) {
        color = STATUS_INVALID_COLOR;       // invalid color red
        textColor = QColor("#F1F1F1");
    }
    else if(value == STATUS_PENDING) {
        color = STATUS_PENDING_COLOR;       // pending color blue
        textColor = QColor("#F1F1F1");
    }
    else if(value == STATUS_WARNING) {
        color = STATUS_WARNING_COLOR;       // warning color orange
        textColor = QColor("#F1F1F1");
    }
    else {
        color = QColor("#888888");          // default color grey
        textColor = QColor("#F1F1F1");
    }
}
