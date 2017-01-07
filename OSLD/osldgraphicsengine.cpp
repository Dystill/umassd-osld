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
                             "Block 4 Hovertext", Pending, true));/*
    gate->addBlock(new Block("Standby", "description",
                             "Block 2 Hovertext", Invalid));
    gate->addBlock(new Block("Fire", "description",
                             "Block 3 Hovertext", Warning));
    gate->addBlock(new Block("ITL", "description",
                             "Block 4 Hovertext", Pending, true));
    gate->addBlock(new Block("Standby", "description",
                             "Block 2 Hovertext", Invalid));
    gate->addBlock(new Block("Fire", "description",
                             "Block 3 Hovertext", Warning));
    gate->addBlock(new Block("ITL", "description",
                             "Block 4 Hovertext", Pending, true));
    gate->addBlock(new Block("Standby", "description",
                             "Block 2 Hovertext", Invalid));
    gate->addBlock(new Block("Fire", "description",
                             "Block 3 Hovertext", Warning));
    gate->addBlock(new Block("ITL", "description",
                             "Block 4 Hovertext", Pending, true));/**/

    QGraphicsWidget *gateGroup = drawGateGroup(gate);
    this->addItem(gateGroup);
}

QGraphicsWidget *OSLDGraphicsEngine::drawGateGroup(Gate *gate)
{
    // create a widget to hold all of the blocks of the gate
    QGraphicsWidget *itemHolder = new QGraphicsWidget;

    // create a layout for the widget to align the blocks vertically
    QGraphicsGridLayout *itemLayout
            = new QGraphicsGridLayout(itemHolder);

    // add all of the gate's blocks to the blockLayout
    int numOfBlocks = gate->getInputBlocks().count();
    qDebug() << numOfBlocks;
    for (int i = 0; i < numOfBlocks; i++) {
        qDebug() << "test";
        Block *block = gate->getInputBlocks().at(i);
        itemLayout->addItem(block, i, 1, Qt::AlignCenter);
    }

    itemLayout->setSpacing(0);
    itemLayout->setVerticalSpacing(Block::V_MARGIN);

    // add gate to the second column
    itemLayout->addItem(gate, 0, 3, numOfBlocks, 1, Qt::AlignCenter);

    Connector *blockToGate = new Connector(numOfBlocks);

    itemLayout->addItem(blockToGate, 0, 2, numOfBlocks, 1, Qt::AlignCenter);

    qDebug() << itemHolder->preferredHeight();

    return itemHolder;
}


