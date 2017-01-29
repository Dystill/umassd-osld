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
    value->setPartOfSubdiagram(this);
}

QList<Connector *> Subdiagram::getConnectors() const
{
    return connectors;
}

void Subdiagram::setConnectors(const QList<Connector *> &value)
{
    connectors = value;
}

void Subdiagram::addConnector(Connector *value) {
    connectors.append(value);
}



