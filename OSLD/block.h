#ifndef BLOCK_H
#define BLOCK_H

#include <QPainter>
#include <QGraphicsItem>

class Block : public QGraphicsItem
{
private:
    QString title;          // the name of the step this block represents
    QString description;    // the description of this block
    QString hovertext;      // the text that hsows when the user hovers over the block
    int status;             // the current status of the block
    QColor color;           // the color of the block as determined by the status
    QColor textColor;       // the color of the text to make it readable with the color
    bool contains;          // whether or not the block contains a subdiagram
    bool negated;           // whether or not the block is connected to a NOT gate

public:
    static const int STATUS_VALID = 1;
    static const int STATUS_INVALID = 2;
    static const int STATUS_PENDING = 3;
    static const int STATUS_WARNING = 4;

    Block(QString t, QString d, QString ht, int st, bool c, bool n);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    bool pressed;

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
    void setStatus(int value);
    QColor getColor() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

signals:

public slots:
};

#endif // BLOCK_H
