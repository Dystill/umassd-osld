#include "diagramitem.h"

/*
 *  CONSTRUCTOR
 */

DiagramItem::DiagramItem(QWidget *parent, QString id, QPointF loc)
{
    this->itemParent = parent;  // save parent item for resizing purposes
    this->setParent(parent);
    this->itemId = id;      // save the item's id
    this->setPos(loc);      // position the item
    this->setFlags(QGraphicsItem::ItemIsSelectable |
                   QGraphicsItem::ItemIsMovable);

    this->lineLength = (parent->logicalDpiX() / 2);
    this->circleRadius = (parent->logicalDpiX() / 24);
}


/*
 *  Item Sizing and Dimensions
 */

QFont DiagramItem::getFont() const
{
    return font;
}

void DiagramItem::setFont(const QFont &value)
{
    font = value;
}

void DiagramItem::setFontPointSize(int size)
{
    font.setPointSize(size);
}

void DiagramItem::setItemSizing(QString title)
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

int DiagramItem::getMaxWidth() const
{
    return maxWidth;
}

void DiagramItem::setMaxWidth(int value)
{
    maxWidth = value;
}


/*
 *  OUTPUT ITEM MANAGEMENT
 */

QList<DiagramItem *> DiagramItem::outputItems() const
{
    return outputItem;
}

void DiagramItem::addOutputItem(DiagramItem *item)
{
    this->outputItem.append(item);
}

void DiagramItem::removeOutputItem(DiagramItem *item)
{
    for(int i = 0; i < this->outputItem.count(); i++) {
        if(item->id() == outputItem.at(i)->id()) {
            outputItem.removeAt(i);
        }
    }
}

/*
 *  QGRAPHICSWIDGET FUNCTIONS
 */
QRectF DiagramItem::boundingRect() const
{
    return QRectF(0, 0, this->width() + ((lineLength + circleRadius) * 2), this->height());
}

void DiagramItem::setGeometry(const QRectF &rect)
{
    prepareGeometryChange();
    this->updateConnectors();
    QGraphicsLayoutItem::setGeometry(rect);
    setPos(rect.topLeft());
}

QSizeF DiagramItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
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

/*
 *  CONNECTOR ATTACHING FUNCTIONS
 */

// get the point where connectors can enter this item
QPointF DiagramItem::inputPoint() const
{
    return this->pos() + QPoint(this->boundingRect().left() + circleRadius, this->boundingRect().center().y());
}

// get the point where connectors can leave this item
QPointF DiagramItem::outputPoint() const
{
    return this->pos() + QPoint(this->boundingRect().right() - circleRadius, this->boundingRect().center().y());
}

// update the line that exits this block
void DiagramItem::updateConnectors()
{
    for(int i = 0; i < inputConn.count(); i++) {
        //qDebug() << "Updating input connectors" << this->inputPoint();
        this->inputConn.at(i)->setEndPoint(this->inputPoint());
    }
    for(int i = 0; i < outputConn.count(); i++) {
        //qDebug() << "Updating output connectors" << this->outputPoint();
        this->outputConn.at(i)->setStartPoint(this->outputPoint());
    }
}

QList<Connector *> DiagramItem::inputConnector() const
{
    return inputConn;
}

void DiagramItem::addInputConnector(Connector *value)
{
    inputConn.append(value);
}

void DiagramItem::removeInputConnector(Connector *value)
{
    inputConn.removeOne(value);
}

QList<Connector *> DiagramItem::outputConnector() const
{
    return outputConn;
}

void DiagramItem::addOutputConnector(Connector *value)
{
    outputConn.append(value);
}

void DiagramItem::removeOutputConnector(Connector *value)
{
    outputConn.removeOne(value);
}


/*
 *  MOUSE FUNCTIONS
 */

void DiagramItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsItem::mousePressEvent(mouseEvent);
}

void DiagramItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsItem::mouseMoveEvent(mouseEvent);
}

void DiagramItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsItem::mouseReleaseEvent(mouseEvent);
}


/*
 *  ATTRIBUTE GETTERS AND SETTERS
 */

// returns the widget this block will be displayed in
QWidget *DiagramItem::parent() const
{
    return itemParent;
}

// returns this item's unique id
QString DiagramItem::id() const
{
    return itemId;
}

// returns the width of this item
int DiagramItem::width() const
{
    return itemWidth;
}

// sets the width for this item
// QGraphicsItem::update() may have to be called afterwards
void DiagramItem::setWidth(int value)
{
    itemWidth = value;
}

// returns the height of this item
int DiagramItem::height() const
{
    return itemHeight;
}

// sets the height for this item
// QGraphicsItem::update() may have to be called afterwards
void DiagramItem::setHeight(int value)
{
    itemHeight = value;
}


bool DiagramItem::isBlock() const
{
    return block;
}

bool DiagramItem::isGate() const
{
    return gate;
}

void DiagramItem::isBlock(bool value)
{
    block = value;
}

void DiagramItem::isGate(bool value)
{
    gate = value;
}

int DiagramItem::getCircleRadius() const
{
    return circleRadius;
}

void DiagramItem::setCircleRadius(int value)
{
    circleRadius = value;
}

int DiagramItem::getLineLength() const
{
    return lineLength;
}

void DiagramItem::setLineLength(int value)
{
    lineLength = value;
}

QColor DiagramItem::getTextColor() const
{
    return textColor;
}

void DiagramItem::setTextColor(const QColor &value)
{
    textColor = value;
}

QString DiagramItem::getTitle() const
{
    return title;
}

void DiagramItem::setTitle(const QString &value)
{
    this->title = value;
    this->setItemSizing(this->title);
}

QString DiagramItem::getDescription() const
{
    return description;
}

void DiagramItem::setDescription(const QString &value)
{
    description = value;
}

QString DiagramItem::getStatus() const
{
    return status;
}

void DiagramItem::setStatus(const QString &value, QMap<QString, QString> colorMap)
{
    //qDebug() << value;
    status = value;

    //qDebug() << colorMap[status];
    color = QColor(colorMap[status]);
}

QColor DiagramItem::getColor() const
{
    return color;
}












