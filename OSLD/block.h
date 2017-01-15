#ifndef BLOCK_H
#define BLOCK_H

#include <diagramitem.h>
#include <QDebug>

class Block : public DiagramItem
{
private:
    QString status;
    QColor color;
    QString title;          // the name of the step this block represents
    QString description;    // the description of this block
    QString hovertext;      // the text that shows when the user hovers over the block

    void setBlockSizing(QWidget *parent);

public:

    // constructors
    Block(QWidget *parent, QString id, QPointF loc,
          QString t = "Block Title",
          QString desc = "Block Description",
          QString ht = "Block Hovertext");

    // QGraphicsItem stuff
    QRectF boundingRect() const;
    void setGeometry(const QRectF &rect);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    QString getTitle() const;
    void setTitle(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getHovertext() const;
    void setHovertext(const QString &value);

    QString getStatus() const;
    void setStatus(const QString &value);

    QColor getColor() const;
    void setColor(const QColor &value);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

signals:

public slots:
};

#endif // BLOCK_H
