#include "osldisplay.h"
#include "ui_osldisplay.h"

OSLDisplay::OSLDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OSLDisplay)
{
    ui->setupUi(this);

    // create an instance of the graphics engine
    OSLDGraphicsEngine osld(this);

    // get the full diagram scene from the graphics engine
    scene = osld.getDiagramScene();

    // display the scene in the window
    ui->graphicsView->setBackgroundBrush(QBrush(QColor("#EEEEEE")));
    ui->graphicsView->setScene(scene);
}

OSLDisplay::~OSLDisplay()
{
    delete ui;
}
