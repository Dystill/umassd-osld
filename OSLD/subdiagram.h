#ifndef SUBDIAGRAM_H
#define SUBDIAGRAM_H

#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include "block.h"
#include "gate.h"
#include "connector.h"

class Subdiagram : public QGraphicsScene
{
private:
    QString name;
    QString description;
    Block *root;                  // the final item for the diagram
    QList<DiagramItem *> inputItems;    // all other diagram items in the subdiagram
    QList<Connector *> connectors;      // a list of all connector objects for this diagram

    QVarLengthArray<QLineF> backgroundGrid;
    QVarLengthArray<QPointF> backgroundDots;

    int gridUnitSize = 20;
    bool showGridBackground = false;

    QGraphicsItem *clickedItem;
    QPointF clickPosition;

public:
    Subdiagram();
    Subdiagram(Block *root, QString name, QString description);

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
    void showGrid(bool show, QRectF area);

    void drawAllItems();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SUBDIAGRAM_H
