#include "osldisplay.h"
#include "ui_osldisplay.h"

OSLDisplay::OSLDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OSLDisplay)
{
    ui->setupUi(this);
    this->setParent(parent);

    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth = desktop->width();
    int screenHeight = desktop->height();

    qDebug() << screenWidth << "x" << screenHeight;

    this->prepareGraphicsView();

    // create an instance of the OSLD graphics engine
    scene = new OSLDGraphicsEngine(ui->graphicsView);

    // display the scene from the graphics engine in the window
    ui->graphicsView->setScene(scene);
    this->resize(QDesktopWidget().availableGeometry(this).size() * windowSizePercent);
    this->fitToWindow();

    // starts the application in full screen mode
    //enterFullScreen();
    QMainWindow::setWindowTitle("Operational Sequence Logic Diagram");
}

OSLDisplay::~OSLDisplay()
{
    delete ui;
}

void OSLDisplay::prepareGraphicsView()
{
    // set different flags
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);

    // filter mouse scrolling to perform custom functions
    ui->graphicsView->viewport()->installEventFilter(this);
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
    }
    else if (px < 0) {
        ui->graphicsView->scale(0.90, 0.90);
    }
    //qDebug() << scaleAmount;
    //qDebug() << "z" << ui->graphicsView->matrix();
}

void OSLDisplay::fitToWindow() {
    // update scene rect to fit the items
    scene->setSceneRect(scene->itemsBoundingRect().adjusted(-36, -36, 36, 36));

    // resize the view contents to match the window size
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

/*
 *  USER INPUT EVENTS
 */

// code to execute when the window is resized
void OSLDisplay::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);    // call parent resize event

    this->fitToWindow();

    // fitInView initially scales the view contents down dramatically -- to 0.0410959 in matrix points m11 & m22
    // I couldn't figure out a reason as to why, so this fixes it
    if(initScaleFix == false) { // flagged so this only triggers once during initialization

        QTransform transformer; // robot in disguise

        int windowWidth = QDesktopWidget().availableGeometry(this).size().width() * windowSizePercent;
        int windowHeight = QDesktopWidget().availableGeometry(this).size().height() * windowSizePercent;

        int sceneWidth = scene->sceneRect().width();
        int sceneHeight = scene->sceneRect().height();

        qreal widthRatio = qreal(windowWidth) / sceneWidth;
        qreal heightRatio = qreal(windowHeight) / sceneHeight;

        qreal scaleFactor = widthRatio <= heightRatio ? widthRatio : heightRatio;

        qDebug() << windowWidth << "x" << windowHeight;
        qDebug() << sceneWidth << "x" << sceneHeight;
        qDebug() << widthRatio << "x" << heightRatio;
        qDebug() << scaleFactor;

        transformer.setMatrix(scaleFactor, 0, 0, 0, scaleFactor, 0, 0, 0, 1);

        // transformer is a matrix specifying the transformations made to the shape of the view (e.g. scale, rotate, shear, etc.)
        // it initializes to a normal & untouched shape, and that's what we want here.
        ui->graphicsView->setTransform(transformer);    // set the graphics view contents back to normal
        initScaleFix = true;    // update the flag so this part isn't executed again
    }
}

// code executed when a specific key is pressed
void OSLDisplay::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();         // get the pressed key
    int mod = event->modifiers();   // get any modifier that was held (shift, ctrl, alt)

    switch(key) {
    case Qt::Key_Escape:                // esc to exit fullscreen
        if(this->isFullScreen())
            exitFullScreen();
        break;
    case Qt::Key_Equal:                 // ctrl+= to zoom in
        if(mod == Qt::ControlModifier){zoom(1);zoom(1);}
        break;
    case Qt::Key_Minus:                 // ctrl+- to zoom out
        if(mod == Qt::ControlModifier){zoom(-1);zoom(-1);}
        break;
    }
}

// code executed when the mouse wheel is manipulated
void OSLDisplay::wheelEvent(QWheelEvent *event)
{
    // get the angle and distance the wheel was moved
    QPoint pixels = event->angleDelta();
    int delta = pixels.y(); // get the vertical distance the wheel was moved

    // if ctrl was held while moving the mouse wheel
    if(event->modifiers() == Qt::ControlModifier) {
        // zoom in or out depending on the direction the mouse was moved
        this->zoom(delta);
    }
    // else if nothing was held
    else if(event->modifiers() == Qt::NoModifier){
        // scroll the view vertically
        QScrollBar *vBar = ui->graphicsView->verticalScrollBar();
        vBar->setValue(vBar->value() - (delta / 2));
    }
    // else if shift or alt was held
    else if(event->modifiers() == Qt::ShiftModifier ||
            event->modifiers() == Qt::AltModifier) {
        // scroll the view horizontally
        QScrollBar *hBar = ui->graphicsView->horizontalScrollBar();
        hBar->setValue(hBar->value() - (delta / 2));
    }
}

// prevent the view from scrolling on any mouse wheel interaction
bool OSLDisplay::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->graphicsView->viewport() &&
        event->type() == QEvent::Wheel) {
        return true;
    }
    return false;
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

void OSLDisplay::mouseReleaseEvent(QMouseEvent *event) {
    QMainWindow::mouseReleaseEvent(event);
}

void OSLDisplay::on_actionHideCloseButton_triggered()
{
    if(ui->closeButton->isHidden()) {
        ui->closeButton->show();
        ui->actionHideCloseButton->setChecked(false);
    }
    else {
        ui->closeButton->hide();
        ui->actionHideCloseButton->setChecked(true);
    }
}

void OSLDisplay::on_actionFitDiagramToWindow_triggered()
{
    this->fitToWindow();
}

void OSLDisplay::on_actionHideBlockTitles_triggered(bool checked)
{
    scene->hideAllItemTitleText(checked);
}
