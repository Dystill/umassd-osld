#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  osld = new OSLDGraphicsEngine();

  connect(osld, SIGNAL(itemSelected(DiagramItem *)), this,
          SLOT(onItemSelected(DiagramItem *)));
  connect(ui->lineEditStatus, SIGNAL(returnPressed()), this,
          SLOT(on_pushButtonUpdate_clicked()));

  // center osld when changing subdiagrams
  connect(osld, SIGNAL(subdiagramChanged()), this, SLOT(fitDiagramToWindow()));

}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::fitDiagramToWindow()
{
    // update scene rect to fit the items
    osld->setSceneRect(osld->itemsBoundingRect().adjusted(-36, -36, 36, 36));

    // resize the view contents to match the window size
    ui->graphicsView->fitInView(osld->sceneRect(), Qt::KeepAspectRatio);

    // qDebug() << "testing fit";
}

void MainWindow::on_actionOpen_Diagram_triggered() {
  QString filePath = QFileDialog::getOpenFileName(
      this, QObject::tr("Open File"), QCoreApplication::applicationDirPath(),
      QObject::tr("XML File(*.xml)"));

  osld->readFileAndRunOSLD(filePath);
  ui->graphicsView->setScene(osld);
  this->fitDiagramToWindow();
}

// Updates the selectedItem and provides it's id and status.
void MainWindow::onItemSelected(DiagramItem *item) {
  selectedItem = item;
  ui->lineEditStatus->setText(item->getStatus());
  ui->labelItemName->setText("'" + item->id() + "' Selected");
}

// Update the selected status.
void MainWindow::on_pushButtonUpdate_clicked() {
  StatusData statusData;
  statusData.id = selectedItem->id();
  statusData.status = ui->lineEditStatus->text();

  osld->updateStatus(statusData);
}
