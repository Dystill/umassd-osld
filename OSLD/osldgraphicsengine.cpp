#include "osldgraphicsengine.h"

OSLDGraphicsEngine::OSLDGraphicsEngine(QObject *parent)
{
    // create a new instance of QGraphicsScene
    scene = new QGraphicsScene(parent);

    // TEST: creating and displaying a gate group

    // create the gate
    Gate *gate = new Gate(Gate::OR);

    // add some blocks
    gate->addBlock(new Block("Interlocks Closed", "description",
                             "Block 1 Hovertext", Block::STATUS_INVALID, false, true));
    gate->addBlock(new Block("Standby", "description",
                             "Block 2 Hovertext", Block::STATUS_VALID));
    gate->addBlock(new Block("Fire", "description",
                             "Block 3 Hovertext", Block::STATUS_WARNING));
    gate->addBlock(new Block("ITL", "description",
                             "Block 4 Hovertext", Block::STATUS_PENDING, true));
    gate->addBlock(new Block("Missile Enabled", "description",
                             "Block 5 Hovertext", Block::STATUS_INVALID));

    // draw the gate and display it in the scene
    scene->addItem(drawGateGroup(gate));

}

QGraphicsWidget *OSLDGraphicsEngine::drawGateGroup(Gate *gate){

    // create a widget to hold all of the blocks of the gate
    QGraphicsWidget *blockHolder = new QGraphicsWidget;
    QGraphicsWidget *gateHolder = new QGraphicsWidget;

    // create a layout for the widget to align the blocks vertically
    QGraphicsLinearLayout *blockLayout
            = new QGraphicsLinearLayout(Qt::Vertical);

    // add all of the gate's blocks to the blockLayout
    for (int i = 0; i < gate->getInputBlocks().count(); i++) {
        blockLayout->addItem(gate->getInputBlocks().at(i));
    }

    blockLayout->setContentsMargins(0,0,0,0);
    blockHolder->setLayout(blockLayout);

    QGraphicsLinearLayout *gateLayout
            = new QGraphicsLinearLayout(Qt::Vertical);

    gateLayout->addItem(gate);

    gateLayout->setContentsMargins(0,0,0,0);
    gateHolder->setLayout(gateLayout);

    // create a widget to hold the blocks, connectors, and gate
    QGraphicsWidget *gateGroup = new QGraphicsWidget;

    // create a layout to align them horizontally
    QGraphicsLinearLayout *groupLayout
            = new QGraphicsLinearLayout(Qt::Horizontal);

    groupLayout->addItem(blockHolder);
    groupLayout->addItem(gateHolder);

    groupLayout->setContentsMargins(0,0,0,0);

    gateGroup->setLayout(groupLayout);

    gateGroup->setFlag(QGraphicsItem::ItemIsMovable);

    return gateGroup;
}

// return the generated diagram scene
QGraphicsScene *OSLDGraphicsEngine::getDiagramScene()
{
    return scene;
}


