#include "osldgraphicsengine.h"

OSLDGraphicsEngine::OSLDGraphicsEngine(QObject *parent)
{

    // create the gate
    Gate *gate = new Gate(Gate::OR);

    // add some blocks
    gate->addBlock(new Block("Interlocks Closed", "description",
                             "Block 1 Hovertext", Valid, false, true));
    gate->addBlock(new Block("Standby", "description",
                             "Block 2 Hovertext", Invalid));
    gate->addBlock(new Block("Fire", "description",
                             "Block 3 Hovertext", Warning));
    gate->addBlock(new Block("ITL", "description",
                             "Block 4 Hovertext", Pending, true));
    gate->addBlock(new Block("Missile Enabled", "description",
                             "Block 5 Hovertext", Invalid));

    QGraphicsWidget *gateGroup = drawGateGroup(gate);
    this->addItem(gateGroup);

    qDebug() << gate->getInputBlocks().at(1)->pos();
}

QGraphicsWidget *OSLDGraphicsEngine::drawGateGroup(Gate *gate)
{

    // create a widget to hold all of the blocks of the gate
    QGraphicsWidget *itemHolder = new QGraphicsWidget;

    // create a layout for the widget to align the blocks vertically
    QGraphicsGridLayout *itemLayout
            = new QGraphicsGridLayout(itemHolder);

    itemLayout->setHorizontalSpacing(0);
    itemLayout->setVerticalSpacing(Block::V_MARGIN);

    // add all of the gate's blocks to the blockLayout
    for (int i = 0; i < gate->getInputBlocks().count(); i++) {
        Block *block = gate->getInputBlocks().at(i);
        itemLayout->addItem(block, i, 0, Qt::AlignCenter);
        qDebug() << block->mapFromScene(0,0);
        qDebug() << block->mapToScene(0,0);
        qDebug() << block->pos();
    }

    itemLayout->addItem(gate, 0, 2, gate->getInputBlocks().count(), 1, Qt::AlignCenter);

    // gateGroup->setFlag(QGraphicsItem::ItemIsMovable);


    qDebug() << itemHolder->preferredHeight();

    return itemHolder;
}


