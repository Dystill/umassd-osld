#include "osldgraphicsengine.h"

OSLDGraphicsEngine::OSLDGraphicsEngine(QObject *parent)
{
    // create a new instance of QGraphicsScene
    scene = new QGraphicsScene(parent);

    // TEST: creating and displaying a gate group

    // create the gate
    Gate *gate = new Gate(Gate::AND);

    // add some blocks
    gate->addBlock(new Block("Block 1", "description",
                             "Block 1 Hovertext", Block::STATUS_INVALID));
    gate->addBlock(new Block("Block 2", "description",
                             "Block 2 Hovertext", Block::STATUS_VALID));
    gate->addBlock(new Block("Block 3", "description",
                             "Block 3 Hovertext", Block::STATUS_WARNING));
    gate->addBlock(new Block("Block 4", "description",
                             "Block 4 Hovertext", Block::STATUS_PENDING));

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
        qDebug() << "Block" << i << gate->getInputBlocks().at(i)->preferredHeight();
    }

    blockHolder->setLayout(blockLayout);


    QGraphicsLinearLayout *gateLayout
            = new QGraphicsLinearLayout(Qt::Vertical);
    gateLayout->setMinimumHeight(blockHolder->preferredHeight());
    gateLayout->addItem(gate);
    gateLayout->setAlignment(gateLayout->itemAt(0), Qt::AlignCenter);
    gateHolder->setLayout(gateLayout);

    // create a widget to hold the blocks, connectors, and gate
    QGraphicsWidget *gateGroup = new QGraphicsWidget;

    // create a layout to align them horizontally
    QGraphicsLinearLayout *groupLayout
            = new QGraphicsLinearLayout(Qt::Horizontal);

    groupLayout->addItem(blockHolder);
    groupLayout->addItem(gateHolder);


    qDebug() << "gate layout" << gateLayout->preferredHeight();
    qDebug() << "gate layout" << gateLayout->preferredWidth();
    qDebug() << "block layout" << blockLayout->preferredHeight();
    qDebug() << "block layout" << blockLayout->preferredWidth();
    qDebug() << "group layout" << groupLayout->preferredHeight();
    qDebug() << "group layout" << groupLayout->preferredWidth();

    gateGroup->setLayout(groupLayout);

    return gateGroup;
}

// return the generated diagram scene
QGraphicsScene *OSLDGraphicsEngine::getDiagramScene()
{
    return scene;
}


