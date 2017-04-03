#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    QString filePath = QFileDialog::getOpenFileName(parent,
                                                QObject::tr("Open File"),
                                                QCoreApplication::applicationDirPath(),
                                                QObject::tr("XML File(*.xml)"));

    osld = new OSLDGraphicsEngine(filePath);

    ui->graphicsView->setScene(osld);

}

MainWindow::~MainWindow() { delete ui; }
