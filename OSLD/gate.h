#ifndef GATE_H
#define GATE_H

#include <QPainter>
#include <QGraphicsWidget>
#include <QList>
#include <block.h>

enum GateType {
    AndGate,
    OrGate
};

class Gate : public QGraphicsWidget
{
private:
    QList<Block *> inputBlocks;
    QList<int> blockStatuses;
    Block *outputBlock;
    int outputStatus;
    GateType gateType;

    const int WIDTH = 64;
    const int HEIGHT = 64;
    const int LINE_LENGTH = 24;

public:
    QRectF boundingRect() const;
    void setGeometry(const QRectF &rect);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    Gate(GateType type = AndGate);
    Gate(QList<Block *> blocks, Block *outputBlock, GateType type = AndGate);
    void addBlock(Block *b);
    void removeBlock(int pos);
    void removeBlock(QString title);
    QList<Block *> getInputBlocks() const;
    Block *getOutputBlock() const;
    int getGateStatus();
    QString getGateStatusAsString();
    GateType getGateType() const;
    void setGateType(GateType value);
    void updateOutputStatus();
    int sizeOfBlocks(QList<Block *> blocks);
    int getBlockCount();

    QPainterPath *drawANDGatePath();
    QPainterPath *drawORGatePath();


signals:

public slots:
};

#endif // GATE_H
