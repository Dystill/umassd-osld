#include "osldisplay.h"
#include "ui_osldisplay.h"

OSLDisplay::OSLDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OSLDisplay)
{
    ui->setupUi(this);

    // create an instance of the graphics engine
    scene = new OSLDGraphicsEngine(parent);

    // display the scene in the window
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->viewport()->installEventFilter(this);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);

    // starts the application in full screen mode
    // enterFullScreen();
    QMainWindow::setWindowTitle("Operational Sequence Logic Diagram");
}

OSLDisplay::~OSLDisplay()
{
    delete ui;
}

void OSLDisplay::on_actionFullScreen_triggered()
{
    if(this->isFullScreen()) {
        exitFullScreen();
    }
    else {
        enterFullScreen();
    }
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
    case Qt::Key_F11:                   // f11
        if(mod == Qt::NoModifier) {
            if(this->isFullScreen())
                exitFullScreen();
            else
                enterFullScreen();
        }
    case Qt::Key_Return:                // enter
        if(mod == Qt::AltModifier) {
            if(this->isFullScreen())
                exitFullScreen();
            else
                enterFullScreen();
        }
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
    if(px > 0 && scaleAmount < 150) {
        ui->graphicsView->scale(1.1, 1.1);
        scaleAmount *= 1.1;
    }
    else if (px < 0 && scaleAmount > 50) {
        ui->graphicsView->scale(0.90, 0.90);
        scaleAmount *= 0.9;
    }
    //qDebug() << scaleAmount;
}

void OSLDisplay::on_actionShowGrid_triggered()
{
    scene->showGrid(ui->actionShowGrid->isChecked(),
                    QRectF(ui->graphicsView->mapToScene(
                               ui->graphicsView->rect()).boundingRect()));
    ui->graphicsView->viewport()->update();
}
