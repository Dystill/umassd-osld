#include "osldgraphicsengine.h"

OSLDGraphicsEngine::OSLDGraphicsEngine(QObject *parent)
{
    // create a new instance of QGraphicsScene
    scene = new QGraphicsScene(parent);

    // TEST: creating and displaying Blocks
    QGraphicsLinearLayout *linear = new QGraphicsLinearLayout(Qt::Vertical);
    QGraphicsWidget *form = new QGraphicsWidget;
    form->setLayout(linear);

    block = new Block("Block 1", "description", "Block 1 Hovertext", Block::STATUS_INVALID);
    linear->addItem(block);

    block = new Block("Block 2", "description", "Block 2 Hovertext", Block::STATUS_VALID);
    linear->addItem(block);

    block = new Block("Block 3", "description", "Block 3 Hovertext", Block::STATUS_WARNING);
    linear->addItem(block);

    block = new Block("Block 4", "description", "Block 4 Hovertext", Block::STATUS_PENDING);
    linear->addItem(block);

    gate = new Gate(Gate::AND);
    linear->addItem(gate);

    scene->addItem(form);

}




// return the generated diagram scene
QGraphicsScene *OSLDGraphicsEngine::getDiagramScene()
{
    return scene;
}


