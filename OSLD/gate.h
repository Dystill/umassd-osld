#ifndef GATE_H
#define GATE_H

#include <QPainter>
#include <QGraphicsWidget>
#include <QList>
#include <block.h>

class Gate : public QGraphicsWidget
{
private:
    QList<Block *> inputBlocks;
    QList<int> blockStatuses;
    Block *outputBlock;
    int outputStatus;
    int gateType;

    const int WIDTH = 128;
    const int HEIGHT = 128;

public:
    static const int AND = 1;
    static const int OR = 2;

    QRectF boundingRect() const;
    void setGeometry(const QRectF &rect);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    Gate(int type = AND);
    Gate(QList<Block *> blocks, Block *outputBlock, int type = AND);
    void addBlock(Block *b);
    void removeBlock(int pos);
    void removeBlock(QString title);
    QList<Block *> getInputBlocks() const;
    Block *getOutputBlock() const;
    int getGateStatus();
    QString getGateStatusAsString();
    int getGateType() const;
    void setGateType(int value);
    void updateOutputStatus();
    int sizeOfBlocks(QList<Block *> blocks);

signals:

public slots:
};

#endif // GATE_H
