#include "osldisplay.h"
#include "ui_osldisplay.h"

OSLDisplay::OSLDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OSLDisplay)
{
    ui->setupUi(this);

    // set different flags
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);

    // filter mouse scrolling to perform custom functions
    ui->graphicsView->viewport()->installEventFilter(this);

    // create an instance of the OSLD graphics engine
    scene = new OSLDGraphicsEngine(parent);

    // display the scene from the graphics engine in the window
    scene->setSceneRect(scene->itemsBoundingRect().adjusted(-50, -50, 50, 50));
    ui->graphicsView->setScene(scene);

    this->adjustSize();

    // starts the application in full screen mode
    //enterFullScreen();
    QMainWindow::setWindowTitle("Operational Sequence Logic Diagram");
}

OSLDisplay::~OSLDisplay()
{
    delete ui;
}

void OSLDisplay::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    int mod = event->modifiers();

    switch(key) {
    case Qt::Key_Escape:                // esc
        if(this->isFullScreen())
            exitFullScreen();
        break;
    case Qt::Key_Equal:                 // =
        if(mod == Qt::ControlModifier){zoom(1);zoom(1);}
        break;
    case Qt::Key_Minus:                 // -
        if(mod == Qt::ControlModifier){zoom(-1);zoom(-1);}
        break;
    }
}

void OSLDisplay::wheelEvent(QWheelEvent *event)
{
    QPoint pixels = event->angleDelta();
    int delta = pixels.y();

    if(event->modifiers() == Qt::ControlModifier) {
        this->zoom(delta);
    }
    else if(event->modifiers() == Qt::ShiftModifier ||
            event->modifiers() == Qt::AltModifier) {
        QScrollBar *hBar = ui->graphicsView->horizontalScrollBar();
        hBar->setValue(hBar->value() - (delta / 2));
    }
    else if(event->modifiers() == Qt::NoModifier){
        QScrollBar *vBar = ui->graphicsView->verticalScrollBar();
        vBar->setValue(vBar->value() - (delta / 2));
    }
}

bool OSLDisplay::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->graphicsView->viewport() &&
        event->type() == QEvent::Wheel) {
        return true;
    }
    return false;
}

// code to execute when the window is resized
void OSLDisplay::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);    // call parent resize event

    on_actionFitDiagramToWindow_triggered();

    // fitInView initially scales the view contents down dramatically -- to 0.0410959 in matrix points m11 & m22
    // I couldn't figure out a reason as to why, so this fixes it
    if(initScaleFix == false) { // flagged so this only triggers once during initialization

        QTransform transformer; // robot in disguise
        /* transformer is a matrix specifying the transformations made to the shape of the view (e.g. scale, rotate, shear, etc.)
         * it initializes to a normal & untouched shape, and that's what we want here.
         */
        ui->graphicsView->setTransform(transformer);    // set the graphics view contents back to normal

        initScaleFix = true;    // update the flag so this part isn't executed again
    }
}

void OSLDisplay::enterFullScreen()
{
    QMainWindow::showFullScreen();
    ui->actionFullScreen->setChecked(true);
}

void OSLDisplay::exitFullScreen()
{
    QMainWindow::showNormal();
    ui->actionFullScreen->setChecked(false);
}

void OSLDisplay::zoom(int px) {
    if(px > 0) {
        ui->graphicsView->scale(1.1, 1.1);
        scaleAmount *= 1.1;
    }
    else if (px < 0) {
        ui->graphicsView->scale(0.90, 0.90);
        scaleAmount *= 0.9;
    }
    //qDebug() << scaleAmount;
    qDebug() << "z" << ui->graphicsView->matrix();
}

// when the full screen menu button is pressed
void OSLDisplay::on_actionFullScreen_triggered()
{
    if(this->isFullScreen()) {
        exitFullScreen();
    }
    else {
        enterFullScreen();
    }
}

// when the show grid button is pressed
void OSLDisplay::on_actionShowGrid_triggered()
{
    scene->showGrid(ui->actionShowGrid->isChecked(),
                    QRectF(ui->graphicsView->mapToScene(
                               ui->graphicsView->rect()).boundingRect()));
    ui->graphicsView->viewport()->update();
}

// when the close window button is pressed
void OSLDisplay::on_closeButton_clicked()
{
    this->destroy();
}

void OSLDisplay::on_actionShowCloseButton_triggered()
{
    if(ui->closeButton->isHidden()) {
        ui->closeButton->show();
        ui->actionShowCloseButton->setText("Hide On-Screen Buttons");
    }
    else {
        ui->closeButton->hide();
        ui->actionShowCloseButton->setText("Show On-Screen Buttons");
    }
}

void OSLDisplay::mouseReleaseEvent(QMouseEvent *event) {
    QMainWindow::mouseReleaseEvent(event);
}

void OSLDisplay::on_actionFitDiagramToWindow_triggered()
{
    // update scene rect to fit the items
    scene->setSceneRect(scene->itemsBoundingRect().adjusted(-50, -50, 50, 50));

    // resize the view contents to match the window size
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}
