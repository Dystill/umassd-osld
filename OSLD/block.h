#ifndef BLOCK_H
#define BLOCK_H

#include <QDebug>
#include "diagramitem.h"

class Subdiagram;

// builder structure that holds block data
// used to store a block's data before passing it into a function
// makes function parameters neater and smaller
struct BlockData {
    QString title;
    QString description;
    QString hovertext;
    QString status;
    QColor textColor = QColor(Qt::white);
};

class Block : public DiagramItem
{
private:
    Subdiagram *subdiagram;

public:
    // constructor
    Block(QWidget *parent, QString id, QPointF loc,     // blocks must have the parent object, id, and location, which is handled by the parent class
          QString t = "Block Title",
          QString desc = "Block Description",
          QString ht = "Block Hovertext");

    // QGraphicsItem stuff
    QRectF boundingRect() const;    // returns the rectagular container for this item
    void setGeometry(const QRectF &rect);   // used by QGraphicsItem to resize and update graphics elements
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;    // gives default sizes for items to use
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,   // paints the graphics to use for the object
               QWidget *widget);

    Subdiagram *getSubdiagram() const;
    void setSubdiagram(Subdiagram *value);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void setBlockSizing(QString title);

signals:

public slots:
};

#endif // BLOCK_H
