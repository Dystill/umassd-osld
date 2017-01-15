#ifndef GATE_H
#define GATE_H

#include <QPainter>
#include <QGraphicsWidget>
#include <QList>
#include <block.h>

enum GateType {
    AndGate,
    OrGate,
    NotGate
};

class Gate : public DiagramItem
{
private:
    GateType gateType;

    QPainterPath *drawANDGatePath();
    QPainterPath *drawORGatePath();
    QPainterPath *drawNOTGatePath();

public:
    QRectF boundingRect() const;
    void setGeometry(const QRectF &rect);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    Gate(QWidget *parent, QString id, QPointF loc, GateType type = AndGate);

    void setGateSizing(QWidget *parent);

signals:

public slots:
};

#endif // GATE_H
