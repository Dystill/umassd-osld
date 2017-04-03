#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    osld = new OSLDGraphicsEngine();

}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionOpen_Diagram_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                QObject::tr("Open File"),
                                                QCoreApplication::applicationDirPath(),
                                                QObject::tr("XML File(*.xml)"));

    osld->readFileAndRunOSLD(filePath);

    ui->graphicsView->setScene(osld);
}
