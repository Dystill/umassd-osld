#include "osldgraphicsengine.h"

OSLDGraphicsEngine::OSLDGraphicsEngine(QWidget *parent)
{
    this->parent = parent;

    QList<Block *> blocks1;

    blocks1.append(new Block(parent, "Interlocks Closed", "description",
                             "Block 1 Hovertext", Invalid, false, true));
    blocks1.append(new Block(parent, "Standby", "description",
                             "Block 2 Hovertext", Valid));
    blocks1.append(new Block(parent, "Fire", "description",
                             "Block 3 Hovertext", Warning));
    blocks1.append(new Block(parent, "ITL", "description",
                             "Block 4 Hovertext", Pending, true));
    blocks1.append(new Block(parent, "Missile Enabled", "description",
                             "Block 5 Hovertext", Valid));

    Block *output = new Block(parent, "Missile Away", "description",
                             "Block Out Hovertext", Unknown);

    QList<Block *> blocks2;
    blocks2.append(new Block(parent, "Launcher Ready", "description",
                             "Block 1 Hovertext", Valid));
    blocks2.append(new Block(parent, "Within Limits", "description",
                             "Block 2 Hovertext", Invalid, true));
    blocks2.append(new Block(parent, "Tube Selected", "description",
                             "Block 3 Hovertext", Pending));
    blocks2.append(new Block(parent, "Inputs Matched", "description",
                             "Block 4 Hovertext", Invalid));
    blocks2.append(new Block(parent, "Booster Prearmed", "description",
                             "Block 5 Hovertext", Valid));
    blocks2.append(new Block(parent, "CSPL Prearmed (Vertical Only)", "description",
                             "Block 6 Hovertext", Warning));

    // create the gate
    Gate *gate1 = new Gate(parent, blocks1, output, AndGate);
    Gate *gate2 = new Gate(parent, blocks2, gate1->getInputBlocks().at(0), OrGate);

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
    QList<Block *> inputBlocks = gate->getInputBlocks();
    int numOfBlocks = inputBlocks.count();
    QList<QColor> connColors;
    int blockSpacing = inputBlocks.at(0)->height() + inputBlocks.at(0)->verticalMargin();

    // loop through each block to draw and record the status color for the connectors
    for (int i = 0; i < numOfBlocks; i++) {
        Block *block = inputBlocks.at(i);                // get each block
        connColors.append(Block::parseColor(block->getBroadcastStatus()));   // record the status color
        itemLayout->addItem(block, i, 1, Qt::AlignCenter);          // draw the block
    }

    // space out all drawn items properly
    itemLayout->setSpacing(0);
    itemLayout->setVerticalSpacing(0);

    // create and draw the connections between the gate and blocks in the second column
    Connector *blockToGate = new Connector(parent, blockSpacing, connColors);
    itemLayout->addItem(blockToGate, 0, 2, numOfBlocks, 1, Qt::AlignCenter);

    // add the gate to the third column
    itemLayout->addItem(gate, 0, 3, numOfBlocks, 1, Qt::AlignCenter);

    // add the gate's output block in the fourth column
    itemLayout->addItem(gate->getOutputBlock(), 0, 4, numOfBlocks, 1, Qt::AlignCenter);


    return itemHolder;  // return the widget holding the entire drawn subdiagram
}


