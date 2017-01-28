#include "gate.h"

/*
 *  CONSTRUCTOR
 */

Gate::Gate(QWidget *parent, QString id, QPointF loc, GateType type)
    : DiagramItem(parent, id, loc)
{
    gateType = type;            // set the gate type
    this->setGateSizing();

    QString hovertext = id;

    if(type == AndGate) {
        hovertext.append(" - AND gate");
    }
    else if(type == OrGate) {
        hovertext.append(" - OR gate");
    }
    else if(type == NotGate) {
        hovertext.append(" - NOT gate");
    }

    this->setToolTip(hovertext);

    this->isGate(true);
}

/*
 *  Gate Sizing and Dimensions
 */

void Gate::setGateSizing()
{
    int dpiX = this->parent()->logicalDpiX();
    int dpiY = this->parent()->logicalDpiY();

    this->setWidth(dpiX / 1.5);
    this->setHeight(dpiY / 1.5);
}

/*
 *  Gate QGraphicsWidget Functions
 */

QRectF Gate::boundingRect() const
{
    return DiagramItem::boundingRect();
}

void Gate::setGeometry(const QRectF &rect)
{
    DiagramItem::setGeometry(rect);
}

QSizeF Gate::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    return DiagramItem::sizeHint(which, constraint);
}

// draw the gate onto the screen
void Gate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRectF rect = boundingRect();
    QBrush brush(QColor("#bbdefb"));
    QPen pen(QColor("#212121"));
    QTextOption texto;

    pen.setWidth(2);
    pen.setCosmetic(true);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setCapStyle(Qt::RoundCap);
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


    //// Drawing the Gate
    // create the gate shape
    QPainterPath *gatePath;
    if(this->gateType == AndGate) {
        gatePath = this->drawANDGatePath(rect.width() - 2*this->getLineLength(), rect.height());
    }
    else if(this->gateType == OrGate) {
        gatePath = this->drawORGatePath(rect.width() - 2*this->getLineLength(), rect.height());
    }
    else if(this->gateType == NotGate) {
        gatePath = this->drawNOTGatePath(rect.width() - 2*this->getLineLength(), rect.height());
    }

    // move the gate shape to the center
    gatePath->translate(this->getCircleRadius() + this->getLineLength(), 0);

    // draw the gate shape
    painter->drawPath(*gatePath);

    // draw circles for the connector entry points
    painter->drawEllipse(QPointF(rect.left(), rect.center().y()), this->getCircleRadius(), this->getCircleRadius());
    painter->drawEllipse(QPointF(rect.right(), rect.center().y()), this->getCircleRadius(), this->getCircleRadius());

    // draw title if necessary

    if(!this->getTitle().isEmpty()) {
        // set some text flags
        texto.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);   // wordwrap
        texto.setAlignment(Qt::AlignCenter);                            // center align

        // set the color and font for the text
        pen.setColor(this->getTextColor());
        QFont font;
        font.setPointSize(12);
        painter->setFont(font);
        painter->setPen(pen);

        // draw the text
        painter->drawText(rect, this->getTitle(), texto);
    }

}

QPainterPath *Gate::drawANDGatePath(int width, int height)
{
    QPointF topLeft(0, 0);
    QPointF bottomLeft(0, height);
    QPointF right(width, height/2);
    QPointF middleTop(width/2, 0);
    QPointF middleBottom(width/2, height);

    QPainterPath *path = new QPainterPath(topLeft);

    // top edge
    path->lineTo(middleTop);

    // top-right curve
    path->cubicTo(QPointF(width*0.75, 0),
                  QPointF(width, height*0.25), right);

    // bottom-right curve
    path->cubicTo(QPointF(width, height*0.75),
                  QPointF(width*0.75, height), middleBottom);

    // bottom edge
    path->lineTo(bottomLeft);

    // left edge
    path->lineTo(topLeft);

    return path;
}

QPainterPath *Gate::drawORGatePath(int width, int height)
{
    QPointF topLeft(0, 0);
    QPointF bottomLeft(0, height);
    QPointF right(width, height / 2);
    QPointF inner(width*0.25, height / 2);

    QPainterPath *path = new QPainterPath(topLeft);

    // top curve
    path->cubicTo(QPointF(width*0.25, 0),
                  QPointF(width*0.75, 0), right);

    // bottom curve
    path->cubicTo(QPointF(width*0.75, height),
                  QPointF(width*0.25, height), bottomLeft);

    // inner-bottom quarter curve
    path->cubicTo(QPointF(width*0.125, height*0.90),
                  QPointF(width*0.25, height*0.725), inner);

    // inner-top quarter curve
    path->cubicTo(QPointF(width*0.25, height*0.275),
                  QPointF(width*0.125, height*0.10), topLeft);

    return path;
}

QPainterPath *Gate::drawNOTGatePath(int width, int height)
{
    int gateHeight = height / 2;      // the height of the gate
    int triangleWidth = width / 2.5;     // the width of the triangle
    int dotRadius = width / 10;         // the radius for the circle

    // defining corners for the triangle
    QPointF topLeft((width - triangleWidth) / 2, (height - gateHeight) / 2);
    QPointF bottomLeft((width - triangleWidth) / 2, (height + gateHeight) / 2);
    QPointF right((width + triangleWidth) / 2, (height / 2));

    // create a painter path object to store the shape
    QPainterPath *path = new QPainterPath(topLeft);

    // create lines for the triangle
    path->lineTo(right);
    path->lineTo(bottomLeft);
    path->lineTo(topLeft);

    // create the circle dot at the tip
    path->addEllipse(QPointF(right.x() + dotRadius, height / 2),
                     dotRadius, dotRadius);

    return path;
}
