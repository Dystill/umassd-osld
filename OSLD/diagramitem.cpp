#include "diagramitem.h"

/*
 *  CONSTRUCTOR
 */

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
 *  MOUSE FUNCTIONS
 */

void DiagramItem::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    /*
    mDragged = qgraphicsitem_cast<QGraphicsItem*>(itemAt(mouseEvent->scenePos(), QTransform()));
    if (mDragged) {
        mDragOffset = mouseEvent->scenePos() - mDragged->pos();
    } else
        QGraphicsScene::mousePressEvent(mouseEvent);
    */
    qDebug() << "Mouse pressed onto" << this->id();
    QGraphicsItem::mousePressEvent(mouseEvent);

    update();
}

void DiagramItem::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    /*
    if (mDragged) {
        // Ensure that the item's offset from the mouse cursor stays the same.
        mDragged->setPos(mouseEvent->scenePos() - mDragOffset);
    } else
        QGraphicsScene::mouseMoveEvent(mouseEvent);
        */
    qDebug() << "Mouse moving" << this->id();
    QGraphicsItem::mouseMoveEvent(mouseEvent);

    update();
}

void DiagramItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    /*
    if (mDragged) {
        int x = floor(mouseEvent->scenePos().x() / mCellSize.width()) * mCellSize.width();
        int y = floor(mouseEvent->scenePos().y() / mCellSize.height()) * mCellSize.height();
        mDragged->setPos(x, y);
        mDragged = 0;
    } else
        QGraphicsScene::mouseReleaseEvent(mouseEvent);
        */
    qDebug() << "Mouse released" << this->id();
    QGraphicsItem::mouseReleaseEvent(mouseEvent);

    update();
}

/*
 *  ITEM POSITIONING AND LOCATING
 */

/*
QPointF DiagramItem::convertPointToRelative(QPointF loc, DiagramItem *anchor)
{
    QPointF temp;
    QPointF anchorPoint = anchor->location();

    temp.setX(loc.x() - anchorPoint.x());
    temp.setY(loc.y() - anchorPoint.y());

    return temp;
}

QPointF DiagramItem::convertPointToAbsolute(QPointF loc, DiagramItem *anchor)
{
    QPointF temp;
    QPointF anchorPoint = anchor->location();

    temp.setX(loc.x() + anchorPoint.x());
    temp.setY(loc.y() + anchorPoint.y());

    return temp;
}
*/

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
 *  ATTRIBUTE GETTERS AND SETTERS
 */

// returns the widget this block will be displayed in
QWidget *DiagramItem::parent() const { return itemParent; }

// returns this item's unique id
QString DiagramItem::id() const { return itemId; }

// returns the width of this item
int DiagramItem::width() const { return itemWidth; }

// sets the width for this item
// QGraphicsItem::update() may have to be called afterwards
void DiagramItem::setWidth(int value) { itemWidth = value; }

// returns the height of this item
int DiagramItem::height() const { return itemHeight; }

// sets the height for this item
// QGraphicsItem::update() may have to be called afterwards
void DiagramItem::setHeight(int value) { itemHeight = value; }


bool DiagramItem::isBlock() const {
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












