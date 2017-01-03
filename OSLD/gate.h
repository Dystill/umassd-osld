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

public:
    static const int AND = 1;
    static const int OR = 2;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    Gate(int type = AND);
    Gate(QList<Block *> blocks, Block *outputBlock, int type = AND);
    void addBlock(Block *b);
    void removeBlock(QString title);
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
