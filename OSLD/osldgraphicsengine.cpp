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
    // create a layout for the widget to align the blocks vertically
    QGraphicsWidget *itemHolder = new QGraphicsWidget;
    QGraphicsGridLayout *itemLayout
            = new QGraphicsGridLayout(itemHolder);

    // store the number of blocks connected to the gate in this subdiagram
    // store the status color of each block leading into the gate
    int numOfBlocks = gate->getInputBlocks().count();
    QList<QColor> connColors;

    // loop through each block to draw and record the status color for the connectors
    for (int i = 0; i < numOfBlocks; i++) {
        Block *block = gate->getInputBlocks().at(i);                // get each block
        connColors.append(Block::parseColor(block->getBroadcastStatus()));   // record the status color
        itemLayout->addItem(block, i, 1, Qt::AlignCenter);          // draw the block
    }

    // space out all drawn items properly
    itemLayout->setSpacing(0);
    itemLayout->setVerticalSpacing(Block::V_MARGIN);

    // add the gate to the third column
    itemLayout->addItem(gate, 0, 3, numOfBlocks, 1, Qt::AlignCenter);

    // create and draw the connections between the gate and blocks in the second column
    Connector *blockToGate = new Connector(connColors);
    itemLayout->addItem(blockToGate, 0, 2, numOfBlocks, 1, Qt::AlignCenter);

    // add the gate's output block in the fourth column
    itemLayout->addItem(gate->getOutputBlock(), 0, 4, numOfBlocks, 1, Qt::AlignCenter);


    return itemHolder;  // return the widget holding the entire drawn subdiagram
}


