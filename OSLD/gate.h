#ifndef GATE_H
#define GATE_H

#include <QPainter>
#include <QGraphicsWidget>
#include <QList>
#include <block.h>

// enumeration to hold all of the gate types
enum GateType {
    AndGate,
    OrGate,
    NotGate
};

class Gate : public DiagramItem
{
private:
    GateType gateType;  // holds this gate's type (AND, OR, NOT)
    int defaultSize = 64;

    QPainterPath *drawANDGatePath(int width, int height);    // returns a path to draw the shape of an AND gate
    QPainterPath *drawORGatePath(int width, int height);     //                  "   "                 OR gate
    QPainterPath *drawNOTGatePath(int width, int height);    //                  "   "                 NOT gate


public:
    // constructor
    Gate(QString id, GateType type = AndGate, QPointF loc = QPointF(0,0));

    // QGraphicsItem stuff
    QRectF boundingRect() const;
    void setGeometry(const QRectF &rect);
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void setGateType(QString type);

    // functions to set the size for the gate
    void setGateSizing(int size = 64);
    void setGateSizing(int w, int h);
protected:

signals:

public slots:
};

#endif // GATE_H
