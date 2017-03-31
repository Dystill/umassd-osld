#include "diagramitem.h"

bool DiagramItem::transparentTitle = false;

/*
 *  CONSTRUCTOR
 */

void DiagramItem::setStatusInfoDataList(const QMap<QString, DiagramItemData> &value)
{
    statusInfoDataList = value;
}

DiagramItem::DiagramItem()
{

}

DiagramItem::DiagramItem(QString id, QPointF loc)
{
    this->itemId = id;      // save the item's id
    this->setLocation(loc);
    this->setFlags(QGraphicsItem::ItemIsSelectable);
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

void DiagramItem::setTitleSize(int size)
{
    font.setPixelSize(size);
}

void DiagramItem::setItemSizing(QString title)
{
    QFontMetricsF metrics(font);

    qreal textWidth = metrics.boundingRect(title).width();
    qreal textHeight = metrics.boundingRect(title).height();

    //qDebug() << "title:" << title;
    //qDebug() << "textWidth:" << textWidth;
    //qDebug() << "textHeight:" << textHeight;

    int wordWrapLimit = ((textWidth + this->maxWidth - 1) / this->maxWidth);

    //qDebug() << "wordWrapLimit:" << wordWrapLimit;

    this->setWidth(((textWidth > this->maxWidth) ? this->maxWidth : textWidth) + 64);
    this->setHeight(((textHeight * wordWrapLimit) + 1) * 2.5);

    //qDebug() << "Width:" << this->width();
    //qDebug() << "Height:" << this->height();

    this->update();
    this->updateConnectors();
}

void DiagramItem::setItemSizing(int w, int h)
{
    // set width to defaultSize if 0 is passed for width
    if(w == 0)
        this->setWidth(defaultWidth);
    else
        this->setWidth(w);

    // set height to default size of 0 is passed for height
    if(h == 0)
        this->setHeight(defaultHeight);
    else
        this->setHeight(h);
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
    return this->pos() + QPoint(this->boundingRect().left() + this->getCircleRadius(),
                                this->boundingRect().center().y()) +
            this->getInputPointOffset();
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
    this->location = this->pos();
    QGraphicsItem::mouseReleaseEvent(mouseEvent);
}


/*
 *  ATTRIBUTE GETTERS AND SETTERS
 */

// id

QString DiagramItem::id() const
{
    return itemId;
}

void DiagramItem::setItemId(const QString &value)
{
    itemId = value;
}

// width

int DiagramItem::width() const
{
    return itemWidth;
}

// QGraphicsItem::update() may have to be called afterwards
void DiagramItem::setWidth(int value)
{
    itemWidth = value;
}

// height

int DiagramItem::height() const
{
    return itemHeight;
}

// QGraphicsItem::update() may have to be called afterwards
void DiagramItem::setHeight(int value)
{
    itemHeight = value;
}

// is this item a block or gate?

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

// get circle radius for extension lines endpoints

int DiagramItem::getCircleRadius() const
{
    return circleRadius;
}

void DiagramItem::setCircleRadius(int value)
{
    circleRadius = value;
}

// the extensions lines' length

int DiagramItem::getLineLength() const
{
    return lineLength;
}

void DiagramItem::setLineLength(int value)
{
    lineLength = value;
}


// setters and getters for statusInfoData

// text color
QColor DiagramItem::getTextColor() const
{
    return currentStatusInfo.textColor;
}

void DiagramItem::setTextColor(QColor value)
{
    currentStatusInfo.textColor = value;
}

QString DiagramItem::getTitle() const
{
    return currentStatusInfo.title;
}

void DiagramItem::setTitle(QString value)
{
    currentStatusInfo.title = value;
}

QString DiagramItem::getDescription() const
{
    return currentStatusInfo.description;
}

void DiagramItem::setDescription(QString value)
{
    currentStatusInfo.description = value;
}

QString DiagramItem::getStatus() const
{
    return currentStatus;
}

void DiagramItem::setStatus(const QString &value, QMap<QString, StatusTypes> colorMap)
{
    //qDebug() << value;
    currentStatus = value;
    currentStatusInfo = statusInfoDataList[currentStatus];

    //qDebug() << colorMap[status];
    currentStatusInfo.color = QColor(colorMap[currentStatus].color);
    currentStatusInfo.textColor = QColor(colorMap[currentStatus].textColor);
    currentStatusInfo.italics = colorMap[currentStatus].italics;
    currentStatusInfo.bold = colorMap[currentStatus].bold;
    currentStatusInfo.underline = colorMap[currentStatus].underline;

    this->updateStatusInfo();
}

void DiagramItem::updateStatusInfo() {
    this->setTitle(currentStatusInfo.title);
    this->setDescription(currentStatusInfo.description);
    this->setToolTip(currentStatusInfo.hovertext);
    this->setTextColor(currentStatusInfo.textColor);
    this->setItalics(currentStatusInfo.italics);
    this->setUnderline(currentStatusInfo.underline);
    this->setBold(currentStatusInfo.bold);
}

QColor DiagramItem::getColor() const
{
    return currentStatusInfo.color;
}

void DiagramItem::setColor(const QColor &value)
{
    currentStatusInfo.color = value;
}

void DiagramItem::setItalics(bool b)
{
    font.setItalic(b);
}

void DiagramItem::setBold(bool b)
{
    font.setBold(b);
}

void DiagramItem::setUnderline(bool b)
{
    font.setUnderline(b);
}

Subdiagram *DiagramItem::getParentSubdiagram() const
{
    return parentSubdiagram;
}

void DiagramItem::setParentSubdiagram(Subdiagram *value)
{
    parentSubdiagram = value;
}

QPointF DiagramItem::getLocation() const
{
    return location;
}

bool DiagramItem::isTransparent()
{
    return transparentTitle;
}

void DiagramItem::setTransparent(bool value)
{
    transparentTitle = value;
}

QPointF DiagramItem::getInputPointOffset() const
{
    return inputPointOffset;
}

void DiagramItem::setInputPointOffset(const QPointF &value)
{
    inputPointOffset = value;
}

QString DiagramItem::getSourceId() const
{
    return sourceId;
}

void DiagramItem::setSourceId(const QString &value)
{
    sourceId = value;
}

void DiagramItem::setLocation(const QPointF &value)
{
    location = value;
    this->setPos(value);      // position the item
}

int DiagramItem::getDefaultWidth() const
{
    return defaultWidth;
}

void DiagramItem::setDefaultWidth(int value)
{
    defaultWidth = value;
}

int DiagramItem::getDefaultHeight() const
{
    return defaultHeight;
}

void DiagramItem::setDefaultHeight(int value)
{
    defaultHeight = value;
}










void DiagramItemData::setForStatus(const QString &value)
{
    forStatus = value;
}

void DiagramItemData::setTitle(const QString &value)
{
    title = value;
}

void DiagramItemData::setDescription(const QString &value)
{
    description = value;
}

void DiagramItemData::setHovertext(const QString &value)
{
    hovertext = value;
}

void DiagramItemData::setDefaultStatus(const QString &value)
{
    defaultStatus = value;
}
