#ifndef SUBDIAGRAM_H
#define SUBDIAGRAM_H

#include <QtCore>
#include <QGraphicsWidget>
#include "block.h"
#include "gate.h"
#include "connector.h"

class Subdiagram
{
private:
    QString name;
    QString description;
    Block *root;                  // the final item for the diagram
    QList<DiagramItem *> inputItems;    // all other diagram items in the subdiagram
    QList<Connector *> connectors;      // a list of all connector objects for this diagram

public:
    Subdiagram();
    Subdiagram(Block *root,
               QString name = "Default Subdiagram name",
               QString description = "Default Subdiagram description");

    void connectItems(DiagramItem *input, DiagramItem *output);    // creates a connector from a gate to another item


    QString getName() const;
    void setName(const QString &value);
    QString getDescription() const;
    void setDescription(const QString &value);
    Block *getRoot() const;
    void setRoot(Block *value);
    QList<DiagramItem *> getInputItems() const;
    void setInputItems(const QList<DiagramItem *> &value);
    void addInputItem(DiagramItem *value);
    QList<Connector *> getConnectors() const;
    void setConnectors(const QList<Connector *> &value);
    void addConnector(Connector *value);
protected:
};

#endif // SUBDIAGRAM_H
