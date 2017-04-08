#include "gate.h"

/*
 *  CONSTRUCTOR
 */

Gate::Gate(QString id, GateType type, QPointF loc)
    : DiagramItem(id, loc)
{
    gateType = type;            // set the gate type

    QString hovertext = id;

    // set default size for this object
    this->setDefaultWidth(defaultSize);
    this->setDefaultHeight(defaultSize);

    // set the title fontsize
    this->setTitleSize(16);

    // determine type of block and resize based on that
    if(type == AndGate) {
        hovertext.append(" - AND gate");
        this->setGateSizing(defaultSize);
    }
    else if(type == OrGate) {
        hovertext.append(" - OR gate");
        this->setGateSizing(defaultSize);
    }
    else if(type == NotGate) {
        hovertext.append(" - NOT gate");
        this->setGateSizing(defaultSize/1.5);
    }

    this->setToolTip(hovertext);

    this->isGate(true);
    this->setColor(QColor("#bbdefb"));
}

/*
 *  Gate Sizing and Dimensions
 */

void Gate::setGateSizing(int size)
{
    this->setWidth(size);
    this->setHeight(size);
    this->setInputPointOffset(QPointF(this->width() / 4,0));
}

void Gate::setGateSizing(int w, int h)
{
    // call parent
    DiagramItem::setItemSizing(w,h);

    // move input point in slightly
    this->setInputPointOffset(QPointF(this->width() / 4,0));
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
    QBrush brush(this->getColor());
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

    // draw the connector circles
    painter->drawEllipse(middleLeft, this->getCircleRadius(), this->getCircleRadius());
    painter->drawEllipse(middleRight, this->getCircleRadius(), this->getCircleRadius());


    //// Drawing the Gate
    // create the gate shape
    QPainterPath gatePath;
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
    gatePath.translate(this->getCircleRadius() + this->getLineLength(), 0);

    // draw the gate shape
    painter->drawPath(gatePath);

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
        painter->setFont(this->getFont());
        painter->setPen(pen);

        // draw the text
        painter->drawText(rect, this->getTitle(), texto);
    }

}

void Gate::setGateType(QString type)
{
    if(type.contains(QRegExp("[Aa][Nn][Dd]"))) {
        this->gateType = AndGate;
    }
    else if(type.contains(QRegExp("[Oo][Rr]"))) {
        this->gateType = OrGate;
    }
    else if(type.contains(QRegExp("[Nn][Oo][Tt]"))) {
        this->gateType = NotGate;
    }
    else {
        qDebug() << "GateType not recognized.";
    }
}

QPainterPath Gate::drawANDGatePath(int width, int height)
{
    QPointF topLeft(0, 0);
    QPointF bottomLeft(0, height);
    QPointF right(width, height/2);
    QPointF middleTop(width/2, 0);
    QPointF middleBottom(width/2, height);

    QPainterPath path;
    path.moveTo(topLeft);

    // top edge
    path.lineTo(middleTop);

    // top-right curve
    path.cubicTo(QPointF(width*0.75, 0),
                  QPointF(width, height*0.25), right);

    // bottom-right curve
    path.cubicTo(QPointF(width, height*0.75),
                  QPointF(width*0.75, height), middleBottom);

    // bottom edge
    path.lineTo(bottomLeft);

    // left edge
    path.lineTo(topLeft);

    return path;
}

QPainterPath Gate::drawORGatePath(int width, int height)
{
    QPointF topLeft(0, 0);
    QPointF bottomLeft(0, height);
    QPointF right(width, height / 2);
    QPointF innerCurveMiddle(width*0.25, height / 2);

    this->setInputPointOffset(QPointF((this->width() / 4) + 16, 0));
    this->updateConnectors();

    QPainterPath path;
    path.moveTo(topLeft);

    // top curve
    path.cubicTo(QPointF(width*0.25, 0),
                  QPointF(width*0.75, 0), right);

    // bottom curve
    path.cubicTo(QPointF(width*0.75, height),
                  QPointF(width*0.25, height), bottomLeft);

    // inner-bottom quarter curve
    path.cubicTo(QPointF(width*0.125, height*0.90),
                  QPointF(width*0.25, height*0.725), innerCurveMiddle);

    // inner-top quarter curve
    path.cubicTo(QPointF(width*0.25, height*0.275),
                  QPointF(width*0.125, height*0.10), topLeft);

    return path;
}

QPainterPath Gate::drawNOTGatePath(int width, int height)
{
    int gateHeight = height;      // the height of the gate
    int dotRadius = width / 6;         // the radius for the circle
    int triangleWidth = width - (dotRadius*2);     // the width of the triangle

    // defining corners for the triangle
    QPointF topLeft(0, 0);
    QPointF bottomLeft(0, gateHeight);
    QPointF right(triangleWidth, (height / 2));

    // create a painter path object to store the shape
    QPainterPath path;
    path.moveTo(topLeft);

    // create lines for the triangle
    path.lineTo(right);
    path.lineTo(bottomLeft);
    path.lineTo(topLeft);

    // create the circle dot at the tip
    path.addEllipse(QPointF(right.x() + dotRadius, height / 2),
                     dotRadius, dotRadius);

    return path;
}

