#ifndef BLOCK_H
#define BLOCK_H

#include <QPainter>
#include <QGraphicsWidget>
#include <QDebug>

enum BlockStatus {
    Valid,
    Invalid,
    Pending,
    Warning
};

class Block : public QGraphicsWidget
{
private:
    QString title;          // the name of the step this block represents
    QString description;    // the description of this block
    QString hovertext;      // the text that shows when the user hovers over the block
    BlockStatus status;     // the current status of the block
    QColor color;           // the color of the block as determined by the status
    bool contains;          // whether or not the block contains a subdiagram
    bool negated;           // whether or not the block is connected to a NOT gate

    // Block colors
    const QColor validColor = QColor("#8BC34A");
    const QColor invalidColor = QColor("#EF5350");
    const QColor pendingColor = QColor("#9575CD");
    const QColor warningColor = QColor("#FF7043");

public:

    // Block dimensions
    static const int WIDTH = 160;
    static const int HEIGHT = 32;
    static const int LINE_LENGTH = 64;
    static const int V_MARGIN = 12;

    // constructors
    Block(QString t  = "Default title",
          QString d  = "Default description",
          QString ht = "Default hovertext",
          BlockStatus st = Valid, bool n = 0, bool c = 0);

    // QGraphicsItem stuff
    QRectF boundingRect() const;
    void setGeometry(const QRectF &rect);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    // get and set the block's title
    QString getTitle() const;
    void setTitle(const QString &value);

    // get and set the block's description
    QString getDescription() const;
    void setDescription(const QString &value);

    // get and set the block's hovertext
    QString getHovertext() const;
    void setHovertext(const QString &value);

    // get and set the block's containment status
    bool isContaining() const;
    void setContains(bool value);

    // get and set the negated status
    bool isNegated() const;
    void setNegated(bool value);

    // get and set the block's status
    int getStatus() const;
    void setStatus(BlockStatus value);
    QColor getColor() const;

    // for painting the not gate
    QPainterPath *drawNOTGatePath();

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

signals:

public slots:
};

#endif // BLOCK_H
