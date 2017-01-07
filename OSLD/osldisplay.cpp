#include "osldisplay.h"
#include "ui_osldisplay.h"

OSLDisplay::OSLDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OSLDisplay)
{
    ui->setupUi(this);

    // create an instance of the graphics engine
    scene = new OSLDGraphicsEngine(this);

    // display the scene in the window
    ui->graphicsView->setBackgroundBrush(QBrush(QColor("#EEEEEE")));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->viewport()->installEventFilter(this);

    // starts the application in full screen mode
    //QMainWindow::showFullScreen();
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
    if(this->isFullScreen() &&
            (event->key() == Qt::Key_Escape ||
             (event->key() == Qt::Key_Return && event->modifiers() == Qt::AltModifier))) {
        exitFullScreen();
    }
    else if (event->key() == Qt::Key_Return && event->modifiers() == Qt::AltModifier) {
        enterFullScreen();
    }
}

void OSLDisplay::wheelEvent(QWheelEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier) {
        QPoint pixels = event->angleDelta();

        if(pixels.y() > 0) {
            ui->graphicsView->scale(1.1, 1.1);
        }
        else if (pixels.y() < 0) {
            ui->graphicsView->scale(0.90, 0.90);
        }
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
    ui->actionFullScreen->setText("Exit Full Screen");
    ui->actionFullScreen->setToolTip("Exit Full Screen");
}

void OSLDisplay::exitFullScreen()
{
    QMainWindow::showNormal();
    ui->actionFullScreen->setText("Enter Full Screen");
    ui->actionFullScreen->setToolTip("Enter Full Screen");
}


