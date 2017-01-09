#include "osldgraphicsengine.h"

OSLDGraphicsEngine::OSLDGraphicsEngine(QObject *parent)
{
    QList<Block *> blocks1;
    blocks1.append(new Block("Interlocks Closed", "description",
                             "Block 1 Hovertext", Valid, false, true));
    blocks1.append(new Block("Standby", "description",
                             "Block 2 Hovertext", Invalid));
    blocks1.append(new Block("Fire", "description",
                             "Block 3 Hovertext", Warning));
    blocks1.append(new Block("ITL", "description",
                             "Block 4 Hovertext", Pending, true));
    blocks1.append(new Block("Missile Enabled", "description",
                             "Block 5 Hovertext", Invalid));

    Block *output = new Block("Missile Away", "description",
                             "Block 5 Hovertext");

    QList<Block *> blocks2;
    blocks2.append(new Block("Launcher Ready", "description",
                             "Block 1 Hovertext", Valid, false, true));
    blocks2.append(new Block("Within Limits", "description",
                             "Block 2 Hovertext", Invalid));
    blocks2.append(new Block("Tube Selected", "description",
                             "Block 3 Hovertext", Warning));
    blocks2.append(new Block("Inputs Matched", "description",
                             "Block 4 Hovertext", Pending, true));
    blocks2.append(new Block("Booster Prearmed", "description",
                             "Block 5 Hovertext", Invalid));
    blocks2.append(new Block("CSPL Prearmed (Vertical Only)", "description",
                             "Block 6 Hovertext", Invalid));

    // create the gate
    Gate *gate1 = new Gate(blocks1, output, AndGate);
    Gate *gate2 = new Gate(blocks1, output, OrGate);

    gates.append(gate1);
    gates.append(gate2);

    QGraphicsWidget *gateGroup1 = drawGateGroup(gates.at(0));

    this->addItem(gateGroup1);
}

QGraphicsWidget *OSLDGraphicsEngine::drawGateGroup(Gate *gate)
{
    // create a widget to hold all of the blocks of the gate
    QGraphicsWidget *itemHolder = new QGraphicsWidget;

    // create a layout for the widget to align the blocks vertically
    QGraphicsGridLayout *itemLayout
            = new QGraphicsGridLayout(itemHolder);

    // get the number of blocks connected to this gate
    int numOfBlocks = gate->getInputBlocks().count();

    // holds the colors to use for the connectors
    QList<QColor> connColors;

    qDebug() << numOfBlocks;

    // loop through each block to draw and record the status color for the connectors
    for (int i = 0; i < numOfBlocks; i++) {
        qDebug() << "test";
        Block *block = gate->getInputBlocks().at(i);                // get each block
        connColors.append(Block::parseColor(block->getBroadcastStatus()));   // record the status color
        itemLayout->addItem(block, i, 1, Qt::AlignCenter);          // draw the block
    }

    // space out all drawn items properly
    itemLayout->setSpacing(0);
    itemLayout->setVerticalSpacing(Block::V_MARGIN);

    // add the gate to the theird column
    itemLayout->addItem(gate, 0, 3, numOfBlocks, 1, Qt::AlignCenter);

    // create the connections between the gate and blocks
    Connector *blockToGate = new Connector(connColors);

    // draw the connections
    itemLayout->addItem(blockToGate, 0, 2, numOfBlocks, 1, Qt::AlignCenter);

    qDebug() << itemHolder->preferredHeight();

    return itemHolder;
}


