#include "gate.h"

/*
 *  CONSTRUCTOR
 */

Gate::Gate(QWidget *parent, QString id, QPointF loc,GateType type)
    : DiagramItem(parent, id, loc)
{
    gateType = type;            // set the gate type
    this->setParent(parent);
    this->setGateSizing(parent);

    this->isGate(true);

    this->setFlag(QGraphicsItem::ItemIsMovable);
}

/*
 *  Gate Sizing and Dimensions
 */

void Gate::setGateSizing(QWidget *parent)
{
    int dpiX = parent->logicalDpiX();
    int dpiY = parent->logicalDpiY();

    this->setWidth(dpiX);
    this->setHeight(dpiY);
}

/*
 *  Gate QGraphicsWidget Functions
 */

QRectF Gate::boundingRect() const   // returns the dimensions of the containing rectangle
{
    return QRectF(0, 0, this->width(), this->height());
}

void Gate::setGeometry(const QRectF &rect)  // i don't know. don't touch this.
{
    prepareGeometryChange();
    this->updateConnectors();
    QGraphicsLayoutItem::setGeometry(rect);
    setPos(rect.topLeft());
}

QSizeF Gate::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const   // returns the Qt size policy dimensions
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

// draw the gate onto the screen
void Gate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QBrush brush(QColor("#bbdefb"));
    QPen pen(QColor("#212121"));

    pen.setWidth(2);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);
    painter->setPen(pen);

    QPainterPath *gatePath;

    QPointF left(0, this->height() / 2);
    QPointF right(this->width(), this->height() / 2);

    if(this->gateType == AndGate) {
        gatePath = this->drawANDGatePath();
    }
    else if(this->gateType == OrGate) {
        gatePath = this->drawORGatePath();
        painter->drawLine(left, right);
    }
    else if(this->gateType == NotGate) {
        gatePath = this->drawNOTGatePath();
        painter->drawLine(left, right);
    }

    painter->fillPath(*gatePath, brush);
    painter->drawPath(*gatePath);
}

QPainterPath *Gate::drawANDGatePath()
{
    QPointF topLeft(0, 0);
    QPointF bottomLeft(0, this->height());
    QPointF right(this->width(), this->height() / 2);
    QPointF middleTop(this->width() / 2, 0);
    QPointF middleBottom(this->width() / 2, this->height());

    QPainterPath *path = new QPainterPath(topLeft);

    // top edge
    path->lineTo(middleTop);

    // top-right curve
    path->cubicTo(QPointF(this->width()*0.75, 0),
                  QPointF(this->width(), this->height()*0.25), right);

    // bottom-right curve
    path->cubicTo(QPointF(this->width(), this->height()*0.75),
                  QPointF(this->width()*0.75, this->height()), middleBottom);

    // bottom edge
    path->lineTo(bottomLeft);

    // left edge
    path->lineTo(topLeft);

    return path;
}

QPainterPath *Gate::drawORGatePath()
{
    QPointF topLeft(0, 0);
    QPointF bottomLeft(0, this->height());
    QPointF right(this->width(), this->height() / 2);
    QPointF inner(this->width()*0.25, this->height() / 2);

    QPainterPath *path = new QPainterPath(topLeft);

    // top curve
    path->cubicTo(QPointF(this->width()*0.25, 0),
                  QPointF(this->width()*0.75, 0), right);

    // bottom curve
    path->cubicTo(QPointF(this->width()*0.75, this->height()),
                  QPointF(this->width()*0.25, this->height()), bottomLeft);

    // inner-bottom quarter curve
    path->cubicTo(QPointF(this->width()*0.125, this->height()*0.90),
                  QPointF(this->width()*0.25, this->height()*0.725), inner);

    // inner-top quarter curve
    path->cubicTo(QPointF(this->width()*0.25, this->height()*0.275),
                  QPointF(this->width()*0.125, this->height()*0.10), topLeft);

    return path;
}

QPainterPath *Gate::drawNOTGatePath()
{
    int gateHeight = this->height() / 3;      // the height of the gate
    int triangleWidth = this->width() / 4;     // the width of the triangle
    int dotRadius = triangleWidth / 4;         // the radius for the circle

    // defining corners for the triangle
    QPointF topLeft((this->width() - triangleWidth) / 2, (this->height() - gateHeight) / 2);
    QPointF bottomLeft((this->width() - triangleWidth) / 2, (this->height() + gateHeight) / 2);
    QPointF right((this->width() + triangleWidth) / 2, (this->height() / 2));

    // create a painter path object to store the shape
    QPainterPath *path = new QPainterPath(topLeft);

    // create lines for the triangle
    path->lineTo(right);
    path->lineTo(bottomLeft);
    path->lineTo(topLeft);

    // create the circle dot at the tip
    path->addEllipse(QPointF(right.x() + dotRadius, this->height() / 2),
                     dotRadius, dotRadius);

    return path;
}
