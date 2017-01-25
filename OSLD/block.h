#ifndef BLOCK_H
#define BLOCK_H

#include <QDebug>
#include "diagramitem.h"

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
    QFont font;         // font for the title text

    QString status = "No Status Available";     // holds the text of the block's status, which is used to access a QMap of status/color combos
    QColor color = QColor("#888888");           // the color of the block is stored here for easier access
    QColor textColor;
    QString title;                              // the name of the step this block represents
    QString description;                        // the description of this block
    QString hovertext;                          // the text that shows when the user hovers over the block

    void setBlockSizing(QString title);         // private function used to generate a size for this block that contains the title text

    int maxWidth;                               // the maximum width of the block before word wraping the title

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

    // getter and setter functions
    QString getTitle() const;
    void setTitle(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getStatus() const;
    QColor getColor() const;

    void setStatus(const QString &value, QMap<QString, QString> colorMap);  // sets both status and color. color cannot be changed directly

    QColor getTextColor() const;
    void setTextColor(const QColor &value);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:

public slots:
};

#endif // BLOCK_H
