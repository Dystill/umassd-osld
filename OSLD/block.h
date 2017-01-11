#ifndef BLOCK_H
#define BLOCK_H

#include <QPainter>
#include <QGraphicsWidget>
#include <QDesktopWidget>
#include <QDebug>

enum BlockStatus {
    Valid,
    Invalid,
    Pending,
    Warning,
    Unknown
};

class Block : public QGraphicsWidget
{
private:
    QWidget *parent;
    QString title;          // the name of the step this block represents
    QString description;    // the description of this block
    QString hovertext;      // the text that shows when the user hovers over the block
    BlockStatus status;     // the current status of the block
    QColor color;           // the color of the block as determined by the status
    bool containsSub;          // whether or not the block contains a subdiagram
    bool negated;           // whether or not the block is connected to a NOT gate

    int blockWidth;
    int blockHeight;
    int lineLength;
    int vMargin;

    // for painting the NOT gate
    QPainterPath *drawNOTGatePath();
    void setBlockSizing(QWidget *parent);

public:
    // Block dimensions
    static const int WIDTH = 160;
    static const int HEIGHT = 40;
    static const int LINE_LENGTH = 48;
    static const int V_MARGIN = 8;

    // constructors
    Block(QWidget *parent,
          QString t  = "Default title",
          QString d  = "Default description",
          QString ht = "Default hovertext",
          BlockStatus st = Unknown, bool n = 0, bool c = 0);

    // QGraphicsItem stuff
    QRectF boundingRect() const;
    void setGeometry(const QRectF &rect);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    // return a color from a status
    QColor static parseColor(BlockStatus value);


    // Getters and Setters

    QString getTitle() const;                   // get and set the block's title
    void setTitle(const QString &value);

    QString getDescription() const;             // get and set the block's description
    void setDescription(const QString &value);

    QString getHovertext() const;               // get and set the block's hovertext
    void setHovertext(const QString &value);

    bool contains() const;                      // get and set the block's containment status
    void setContains(bool value);

    bool isNegated() const;                     // get and set the negated status
    void setNegated(bool value);

    BlockStatus getOriginalStatus() const;      // get and set the block's initial status
    void setOriginalStatus(BlockStatus value);

    BlockStatus getBroadcastStatus() const;     // get the new status after applying NOT logic

    QColor getColor() const;                    // get the color for a status

    int width() const;
    int height() const;
    int verticalMargin() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

signals:

public slots:
};

#endif // BLOCK_H
