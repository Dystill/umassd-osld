#include "subdiagram.h"

/*
 *  CONSTRUCTORS
 */

// empty constructor
Subdiagram::Subdiagram()
{

}

// constructor to set the root block, subdiagram name, and subdiagram decription
Subdiagram::Subdiagram(Block *root, QString name, QString description)
{
    this->root = root;
    this->root->setChildSubdiagram(this);
    this->name = name;
    this->description = description;
}

// creates a connector between any two diagram items
void Subdiagram::connectItems(DiagramItem *input, DiagramItem *output)
{
    QPointF startPoint = input->outputPoint();  // get the output point from the start item
    QPointF endPoint = output->inputPoint();    // get the input point from the end item
    QColor color = input->getColor();           // get the item's color

    //qDebug() << "Connecting Block to Item:" << startPoint << "to" << endPoint;

    // create the connector
    Connector *conn = new Connector(startPoint, endPoint, color);

    input->addOutputConnector(conn);    // keep track of the output connectors in the start item
    output->addInputConnector(conn);    // keep track of the input connectors in the end item

    connectors.append(conn);    // keep track of all connectors in this
}

// get the name of this subdiagram
QString Subdiagram::getName() const
{
    return name;
}

// set the name of this subdiagram
void Subdiagram::setName(const QString &value)
{
    name = value;
}

// get the description
QString Subdiagram::getDescription() const
{
    return description;
}

// set the description
void Subdiagram::setDescription(const QString &value)
{
    description = value;
}

// get the root item for this subdiagram
Block *Subdiagram::getRoot() const
{
    return root;
}

// set the root item for this subdiagram
void Subdiagram::setRoot(Block *value)
{
    root = value;
}

// get all other non-root items from this diagram
QList<DiagramItem *> Subdiagram::getInputItems() const
{
    return inputItems;
}

// set all other non-root items for this subdiagram
void Subdiagram::setInputItems(const QList<DiagramItem *> &value)
{
    inputItems = value;
}

// add an item to the subdiagram
void Subdiagram::addInputItem(DiagramItem *value) {
    inputItems.append(value);
    value->setParentSubdiagram(this);
}

// get the list of all connectors in this subdiagram
QList<Connector *> Subdiagram::getConnectors() const
{
    return connectors;
}

// set the list of all connectors in this subdiagram
void Subdiagram::setConnectors(const QList<Connector *> &value)
{
    connectors = value;
}

// add a connector to this subdiagram
void Subdiagram::addConnector(Connector *value) {
    connectors.append(value);
}



