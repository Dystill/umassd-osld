#include "block.h"

/*
 *  CONSTRUCTOR
 */

Block::Block(QString t, QString d, QString ht,
             int st, bool n, bool c)
{
    this->setTitle(t);
    this->setDescription(d);
    this->setHovertext(ht);
    this->setStatus(st);
    this->setContains(c);
    this->setNegated(n);
}

/*
 *  BLOCK DRAWING FUNCTIONS
 */

QRectF Block::boundingRect() const
{
    return QRectF(0, 0, WIDTH + (LINE_LENGTH * 2), HEIGHT + (TOP_MARGIN * 2));
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


    /*
     * initialize drawing tools
     */

    // create a new rectangle space to draw the block in
    QRectF rect = QRectF(LINE_LENGTH, TOP_MARGIN, WIDTH, HEIGHT);

    // create a color for the outline
    QColor outlineColor = QColor("#212121");
    QColor titleColor = QColor("#F1F1F1");

    // create a brush to fill the block with a status color
    QBrush brush(this->color);

    // create a pen for the title text and border
    QPen pen(outlineColor);
    pen.setWidth(2);
    painter->setPen(pen);   // add the pen to the painter object
    painter->setRenderHint(QPainter::Antialiasing);

    // create a text options object
    QTextOption texto(Qt::AlignCenter);     // align the text to the center
    texto.setWrapMode(QTextOption::NoWrap); // force no wrapping of the text

    QFont titleFont;
    titleFont.setPointSize(12);


    /*
     * drawing the shapes for the block
     */

    // draw lines coming out of the block's sides
    QPoint lineStart(boundingRect().left(), boundingRect().center().y());
    QPoint lineEnd(boundingRect().right(), boundingRect().center().y());
    painter->drawLine(lineStart, lineEnd);

    // fill block with the status color
    painter->fillRect(rect, brush);

    // draw a black outline around the block
    painter->drawRect(rect);

    // add text with the supplied block title
    pen.setColor(titleColor);
    painter->setFont(titleFont);
    painter->setPen(pen);
    painter->drawText(rect, this->title, texto);

    // draw a NOT gate if necessary
    if(this->negated) {
        // set the gate's color
        brush.setColor(QColor("#bbdefb"));
        pen.setColor(outlineColor);
        painter->setPen(pen);

        // get the shape of the not gate
        QPainterPath *path = drawNOTGatePath();

        // move the gate to the correct position
        path->translate(WIDTH + LINE_LENGTH * 1.35, HEIGHT);

        // paint the gate
        painter->fillPath(*path, brush);
        painter->drawPath(*path);
    }
}

QPainterPath *Block::drawNOTGatePath()
{
    int gateHeight = HEIGHT / 1.5;          // the height of the gate
    int triangleWidth = gateHeight / 1.2;   // the width of the triangle

    // defining corners for the triangle
    QPointF topLeft(0, 0);
    QPointF bottomLeft(0, gateHeight);
    QPointF right(triangleWidth, (gateHeight / 2));

    // create a painter path object to store the shape
    QPainterPath *path = new QPainterPath(topLeft);

    // create lines for the triangle
    path->lineTo(right);
    path->lineTo(bottomLeft);
    path->lineTo(topLeft);

    // create the circle dot at the tip
    int dotRadius = gateHeight / 5; // the radius for the circle

    // draw the circle
    path->addEllipse(QPointF(right.x() + dotRadius, gateHeight / 2),
                     dotRadius, dotRadius);

    // align the path by the middle of the triangle
    path->translate(0, -gateHeight/2);

    return path;
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
    }
    else if(value == STATUS_INVALID) {
        color = STATUS_INVALID_COLOR;       // invalid color red
    }
    else if(value == STATUS_PENDING) {
        color = STATUS_PENDING_COLOR;       // pending color blue
    }
    else if(value == STATUS_WARNING) {
        color = STATUS_WARNING_COLOR;       // warning color orange
    }
    else {
        color = QColor("#888888");          // default color grey
    }
}
