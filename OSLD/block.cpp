#include "block.h"

/*
 *  CONSTRUCTOR
 */

Block::Block(QString t, QString d, QString ht,
             BlockStatus st, bool n, bool c)
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
    return QRectF(0, 0, WIDTH + LINE_LENGTH, HEIGHT);
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
    QRectF rect = QRectF(0, 0, WIDTH, HEIGHT);

    // create the line exiting the rectangle
    QPointF lineStart = boundingRect().center();
    QPointF lineToNOT = QPointF(WIDTH + (LINE_LENGTH/2), boundingRect().center().y());
    QPointF lineEnd = QPointF(boundingRect().right(), boundingRect().center().y());

    QLineF line1(lineStart, lineToNOT);
    QLineF line2(lineStart, lineEnd);

    // create a color for the outline
    QColor outlineColor = QColor("#212121");
    QColor titleColor = QColor("#F1F1F1");

    // create a brush to fill the block with a status color
    QBrush brush(this->color);

    // create a pen for the title text and border
    QPen pen;
    pen.setWidth(2);

    // create a text options object
    QTextOption texto(Qt::AlignCenter);     // align the text to the center
    texto.setWrapMode(QTextOption::WordWrap); // force no wrapping of the text

    QFont titleFont;


    /*
     * drawing the shapes for the block
     */

    // draw the line exiting the block
    if(this->negated) {
        // draw the full line
        pen.setColor(outlineColor);
        painter->setPen(pen);
        painter->drawLine(line2);

        // draw the line before the NOT gate
        pen.setColor(this->color);
        painter->setPen(pen);
        painter->drawLine(line1);

        QPainterPath *gatePath = drawNOTGatePath();
        gatePath->translate(lineToNOT);
        pen.setColor(outlineColor);
        brush.setColor(QColor("#bbdefb"));
        painter->setPen(pen);
        painter->setBrush(brush);
        painter->drawPath(*gatePath);
    }
    else {
        pen.setColor(this->color);
        painter->setPen(pen);
        painter->drawLine(line2);
    }

    // fill block with the status color
    brush.setColor(this->color);
    painter->setBrush(brush);
    painter->fillRect(rect, brush);

    // draw an outline around the block
    pen.setColor(outlineColor);
    painter->setPen(pen);
    painter->drawRect(rect);

    // add text with the supplied block title
    pen.setColor(titleColor);
    painter->setPen(pen);
    painter->setFont(titleFont);
    painter->drawText(rect, this->title, texto);

}

QPainterPath *Block::drawNOTGatePath()
{
    int gateHeight = HEIGHT / 1.8;      // the height of the gate
    int triangleWidth = gateHeight / 1.2;     // the width of the triangle
    int dotRadius = gateHeight / 5;         // the radius for the circle

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
    path->addEllipse(QPointF(right.x() + dotRadius, gateHeight / 2),
                     dotRadius, dotRadius);

    // align the path by the middle of the triangle
    path->translate(-triangleWidth/2, -gateHeight/2);

    return path;
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

void Block::setStatus(BlockStatus value)    // sets the status and color for a block
{
    // set the status attribute to the value
    status = value;

    // sets the block color and the text color depending on the value
    if(value == Valid) {
        color = validColor;         // valid color green
    }
    else if(value == Invalid) {
        color = invalidColor;       // invalid color red
    }
    else if(value == Pending) {
        color = pendingColor;       // pending color blue
    }
    else if(value == Warning) {
        color = warningColor;       // warning color orange
    }
    else {
        color = QColor("#888888");          // default color grey
    }
}
