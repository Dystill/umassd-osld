#include "osldgraphicsengine.h"

OSLDGraphicsEngine::OSLDGraphicsEngine(QObject *parent)
{
    // create a new instance of QGraphicsScene
    scene = new QGraphicsScene(parent);

    // TEST: creating and displaying Blocks
    block = new Block("Block 1", "description", "Block 1 Hovertext", Block::STATUS_INVALID);
    scene->addItem(block);

    block = new Block("Block 2", "description", "Block 2 Hovertext", Block::STATUS_VALID);
    scene->addItem(block);

    block = new Block("Block 3", "description", "Block 3 Hovertext", Block::STATUS_WARNING);
    scene->addItem(block);

    block = new Block("Block 4", "description", "Block 4 Hovertext", Block::STATUS_PENDING);
    scene->addItem(block);

}

// return the generated diagram scene
QGraphicsScene *OSLDGraphicsEngine::getDiagramScene()
{
    return scene;
}


