#include "osldisplay.h"
#include "ui_osldisplay.h"

OSLDisplay::OSLDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OSLDisplay)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    block = new Block("title", "description", "hovertext", Block::STATUS_VALID, false, false);
}

OSLDisplay::~OSLDisplay()
{
    delete ui;
}
