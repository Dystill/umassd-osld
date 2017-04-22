#include "osldisplay.h"
#include "ui_osldisplay.h"

OSLDisplay::OSLDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OSLDisplay)
{
    ui->setupUi(this);
    this->setParent(parent);
    this->addMenuBarActionsToDisplay();

    // resize the window to be a certain amount smaller than the screen
    this->resize(QDesktopWidget().availableGeometry(this).size() * windowSizePercent);

    // create an instance of the OSLD graphics engine
    // scene = new OSLDGraphicsEngine("", ui->graphicsView, 1000, false, "horizontal", true, false, true);
    scene = new OSLDGraphicsEngine("", ui->graphicsView);

    // set flags and event filters for the graphicsView
    this->prepareGraphicsView();

    this->displayDiagram();

    // adjust display based on environment variables
    this->readEnvironmentVariables();

    // starts the application in full screen mode
    //enterFullScreen();
    QMainWindow::setWindowTitle("Operational Sequence Logic Diagram");

    // signal slot to change subdiagrams on block press
    connect(scene, SIGNAL(subdiagramChanged()), this, SLOT(fitDiagramToWindow()));

    // signal slots to update root view
    connect(this, SIGNAL(updateRootList(PathAlignment,QGraphicsView*)),
            scene, SLOT(alignRootScene(PathAlignment,QGraphicsView*)));
    connect(this, SIGNAL(fitRootList()), scene, SLOT(fitRootSceneToView()));
    connect(this, SIGNAL(setRootListPadding(int)), scene, SLOT(resizeRootScenePadding(int)));
}

OSLDisplay::~OSLDisplay()
{
    delete ui;
}

// adds actions in the menu bar to the display
// allows shortcuts to work while menu bar is hidden
void OSLDisplay::addMenuBarActionsToDisplay() {
    this->addAction(ui->actionShowGrid);
    this->addAction(ui->actionFitDiagramToWindow);
    this->addAction(ui->actionFullScreen);
    this->addAction(ui->actionHideBlockTitles);
    this->addAction(ui->actionHideButtons);
    this->addAction(ui->actionSwitchOrientation);
}

void OSLDisplay::prepareGraphicsView()
{
    // set different flags
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);

    // filter mouse scrolling to perform custom functions
    ui->graphicsView->viewport()->installEventFilter(this);
}

void OSLDisplay::prepareRootView(QString orientation) {

    // set which scrollbars to show and remove
    ui->rootHGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->rootVGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->rootHGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->rootVGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    if(orientation.startsWith('v',Qt::CaseInsensitive)) {
        // hide the horizontal root view on start
        ui->rootHGraphicsView->hide();

        // signal OSLDGraphicsEngine to realign root view
        emit updateRootList(Vertical, ui->rootVGraphicsView);

        // put the root scene into the vertical root view
        ui->rootVGraphicsView->setScene(scene->getRootScene());

        rootAlignment = Vertical;
    }
    else if(orientation.startsWith('h',Qt::CaseInsensitive)) {

        // hide the horizontal root view on start
        ui->rootVGraphicsView->hide();

        // signal OSLDGraphicsEngine to realign root view
        emit updateRootList(Horizontal, ui->rootHGraphicsView);

        // put the root scene into the vertical root view
        ui->rootHGraphicsView->setScene(scene->getRootScene());

        rootAlignment = Horizontal;
    }
    else {
        // hide both views
        ui->rootHGraphicsView->hide();
        ui->rootVGraphicsView->hide();
    }
}

void OSLDisplay::displayDiagram() {
    // set the diagram title and description
    ui->titleLabel->setText(scene->getDiagramName());

    // display the scene from the graphics engine in the graphicsView
    ui->graphicsView->setScene(scene);

    this->prepareRootView(scene->getRootViewOrientation());

    // resize the scene to fit in the window
    this->fitDiagramAndRootToWindow();
}

void OSLDisplay::readEnvironmentVariables()
{
    // show or hide the controls
    this->on_actionHideButtons_triggered(scene->getHideControls());

    // show or hide block titles
    this->on_actionHideBlockTitles_triggered(scene->getHideBlockTitles());

    // set to fullscreen
    if(scene->getFullscreen()) {
        this->enterFullScreen();
    }
    else {
        this->exitFullScreen();
    }

    // show the grid
    ui->actionShowGrid->setChecked(scene->getShowGridBackground());
    this->on_actionShowGrid_triggered(scene->getShowGridBackground());
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

void OSLDisplay::fitDiagramAndRootToWindow() {
    // update scene rect to fit the items
    scene->setSceneRect(scene->itemsBoundingRect().adjusted(-36, -36, 36, 36));

    // resize the view contents to match the window size
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    // fit root list to graphics view
    emit fitRootList();
}

void OSLDisplay::fitDiagramToWindow()
{
    // update scene rect to fit the items
    scene->setSceneRect(scene->itemsBoundingRect().adjusted(-36, -36, 36, 36));

    // resize the view contents to match the window size
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    qDebug() << "testing fit";
}

/*
 *  USER INPUT EVENTS
 */

// code to execute when the window is resized
void OSLDisplay::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);    // call parent resize event

    // set the width for the vertical graphics view
    ui->rootVGraphicsView->setMinimumWidth(this->size().width() * 0.20);
    ui->rootVGraphicsView->setMaximumWidth(this->size().width() * 0.20);

    // set the height for the horizontal graphics view
    ui->rootHGraphicsView->setMinimumHeight(this->size().height() * 0.15);
    ui->rootHGraphicsView->setMaximumHeight(this->size().height() * 0.15);

    // fit root list to graphics view
    emit fitRootList();

    // this->fitDiagramAndRootToWindow();
}

void OSLDisplay::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);

    emit setRootListPadding(8);

    this->fitDiagramAndRootToWindow();
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
    int yMovement = pixels.y(); // get the vertical distance the wheel was moved
    int xMovement = pixels.x(); // get the horizontal distance the wheel was moved

    // if ctrl was held while moving the mouse wheel
    if(event->modifiers() == Qt::ControlModifier) {
        // zoom in or out depending on the direction the mouse was moved
        this->zoom(yMovement);
    }
    // else if nothing was held
    else if(event->modifiers() == Qt::NoModifier){
        // scroll the view vertically
        QScrollBar *vBar = ui->graphicsView->verticalScrollBar();
        QScrollBar *hBar = ui->graphicsView->horizontalScrollBar();

        vBar->setValue(vBar->value() - (yMovement / 2));
        hBar->setValue(hBar->value() - (xMovement / 2));
    }
    // else if shift or alt was held
    else if(event->modifiers() == Qt::ShiftModifier ||
            event->modifiers() == Qt::AltModifier) {
        // scroll the view horizontally
        QScrollBar *hBar = ui->graphicsView->horizontalScrollBar();
        hBar->setValue(hBar->value() - (xMovement / 2));
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

// when the close window button is pressed
void OSLDisplay::on_closeButton_clicked()
{
    this->destroy();
}

void OSLDisplay::mouseReleaseEvent(QMouseEvent *event) {
    QMainWindow::mouseReleaseEvent(event);
}

void OSLDisplay::mouseMoveEvent(QMouseEvent *event) {
    QMainWindow::mouseMoveEvent(event);
    if(event->pos().y() <= 50 && !ui->menuBar->isVisible()) {
        ui->menuBar->setVisible(true);
    }
}

void OSLDisplay::on_actionFitDiagramToWindow_triggered()
{
    this->fitDiagramAndRootToWindow();
}

void OSLDisplay::on_actionHideBlockTitles_triggered(bool checked)
{
    scene->hideAllItemTitleText(checked);
}

void OSLDisplay::on_actionSwitchOrientation_triggered()
{
    // hide the horizontal root view on start
    if(rootAlignment == Vertical) {
        ui->rootVGraphicsView->hide();

        // put the root scene into the horizontal root view
        ui->rootHGraphicsView->setScene(scene->getRootScene());

        // send the horizontal root view to the root scene
        emit updateRootList(Horizontal, ui->rootHGraphicsView);
        rootAlignment = Horizontal;

        ui->rootHGraphicsView->show();
    }
    else if(rootAlignment == Horizontal) {
        ui->rootHGraphicsView->hide();

        // put the root scene into the vertical root view
        ui->rootVGraphicsView->setScene(scene->getRootScene());

        // send the vertical root view to the root scene
        emit updateRootList(Vertical, ui->rootHGraphicsView);
        rootAlignment = Vertical;

        ui->rootVGraphicsView->show();
    }

    this->fitDiagramAndRootToWindow();
}

void OSLDisplay::on_actionOpenDescriptionFile_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                QObject::tr("Open File"),
                                                QCoreApplication::applicationDirPath(),
                                                QObject::tr("XML File(*.xml)"));

    scene->readFileAndRunOSLD(filePath);

    this->displayDiagram();
}

void OSLDisplay::on_actionHideButtons_triggered(bool checked)
{
    if(checked) {
        ui->closeButton->setVisible(false);
        ui->titleLabel->setVisible(false);
        ui->menuBar->setVisible(false);
    }
    else {
        ui->closeButton->setVisible(true);
        ui->titleLabel->setVisible(true);
        ui->menuBar->setVisible(true);
    }
    this->fitDiagramAndRootToWindow();
}

void OSLDisplay::on_actionShowGrid_triggered(bool checked)
{
    scene->showGrid(checked,
                    QRectF(ui->graphicsView->mapToScene(
                               ui->graphicsView->rect()).boundingRect()));
    ui->graphicsView->viewport()->update();
}
