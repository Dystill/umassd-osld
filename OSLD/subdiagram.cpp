#include "subdiagram.h"

Subdiagram::Subdiagram()
{

}

Subdiagram::Subdiagram(Block *root, QString name, QString description)
{
    this->root = root;
    this->root->setSubdiagram(this);
    this->name = name;
    this->description = description;
}

void Subdiagram::connectItems(DiagramItem *input, DiagramItem *output)
{
    QPointF startPoint = input->outputPoint();
    QPointF endPoint = output->inputPoint();
    QColor color = input->getColor();

    //qDebug() << "Connecting Block to Item:" << startPoint << "to" << endPoint;

    Connector *conn = new Connector(startPoint, endPoint, color);

    input->addOutputConnector(conn);
    output->addInputConnector(conn);

    connectors.append(conn);
}



// overrides to draw a grid for the background
void Subdiagram::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->fillRect(rect, QBrush(QColor("#fafafa")));

    if(showGridBackground) {
        QPen pen;
        pen.setCosmetic(true);
        pen.setColor(QColor("#212121"));
        painter->setPen(pen);

        qreal topY = rect.top();
        qreal leftX = rect.left();
        qreal bottomY = rect.bottom();
        qreal rightX = rect.right();

        qreal startingX = int(leftX) - (int(leftX) % gridUnitSize);
        qreal startingY = int(topY) - (int(topY) % gridUnitSize);

        /*
        for(qreal x = startingX; x < rightX; x += gridUnitSize) {
            backgroundGrid.append(QLineF(x, topY, x, bottomY));
        }
        for(qreal y = startingY; y < bottomY; y += gridUnitSize) {
            backgroundGrid.append(QLineF(leftX, y, rightX, y));
        }
        painter->drawLines(backgroundGrid.data(), backgroundGrid.size());
        */

        for(qreal x = startingX; x < rightX; x += gridUnitSize) {
            for(qreal y = startingY; y < bottomY; y += gridUnitSize) {
                backgroundDots.append(QPointF(x, y));
            }
        }
        painter->drawPoints(backgroundDots.data(), backgroundDots.size());
    }
}

void Subdiagram::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    clickedItem = itemAt(event->scenePos(), QTransform());
    clickPosition = event->scenePos();
    update();
}

void Subdiagram::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}

void Subdiagram::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    QGraphicsItem *releaseItem = itemAt(event->scenePos(), QTransform());
    if(releaseItem == clickedItem && clickPosition == event->scenePos()) {
        DiagramItem *pressedItem = qgraphicsitem_cast<DiagramItem *>(releaseItem);
        if(pressedItem->isBlock()) {
            Block *pressedBlock = qgraphicsitem_cast<Block *>(pressedItem);
            if(pressedBlock->hasSubdiagram()) {
                qDebug() << "Go to" << pressedBlock->getSubdiagram()->getName();
            }
        }
    }
    update();
}


void Subdiagram::drawAllItems()
{
    for(int i = 0; i < connectors.count(); i++) {
        //qDebug() << "Drawing Connector" << i;
        this->addItem(connectors.at(i));
    }
    for(int i = 0; i < inputItems.count(); i++) {
        //qDebug() << "Drawing Block" << i;
        this->addItem(inputItems.at(i));
    }
    this->addItem(root);
}




QString Subdiagram::getName() const
{
    return name;
}

void Subdiagram::setName(const QString &value)
{
    name = value;
}

QString Subdiagram::getDescription() const
{
    return description;
}

void Subdiagram::setDescription(const QString &value)
{
    description = value;
}

Block *Subdiagram::getRoot() const
{
    return root;
}

void Subdiagram::setRoot(Block *value)
{
    root = value;
}

QList<DiagramItem *> Subdiagram::getInputItems() const
{
    return inputItems;
}

void Subdiagram::setInputItems(const QList<DiagramItem *> &value)
{
    inputItems = value;
}

void Subdiagram::addInputItem(DiagramItem *value) {
    inputItems.append(value);
}



/*
 *  OTHER FUNCTIONS
 */

void Subdiagram::showGrid(bool show, QRectF area) {
    showGridBackground = show;
    this->invalidate(area, BackgroundLayer);
}
