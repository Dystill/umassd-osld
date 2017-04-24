#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ui->graphicsView->setRenderHint(QPainter::Antialiasing);
  ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);

  osld = new OSLDGraphicsEngine();

  connect(osld, SIGNAL(itemSelected(DiagramItem *)), this,
          SLOT(onItemSelected(DiagramItem *)));
  connect(ui->comboBoxStatus, SIGNAL(currentIndexChanged(const QString &)),
          this, SLOT(on_pushButtonUpdate_clicked()));

  this->setWindowTitle("The Stimulator Status Testing System");

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
  // Do not send signals while updating the combo box for the selected item.
  ui->comboBoxStatus->blockSignals(true);
  ui->comboBoxStatus->clear();
  ui->comboBoxStatus->addItems(item->getStatuses());
  ui->comboBoxStatus->setCurrentText(item->getStatus());
  ui->comboBoxStatus->blockSignals(false);

  // Specify selected item's id.
  ui->lineEditId->setText(item->id());
}

// Update the selected status.
void MainWindow::on_pushButtonUpdate_clicked() {
  if (DiagramItem *selectedItem = osld->getAllItems()[ui->lineEditId->text()]) {
    StatusData statusData;
    statusData.id = selectedItem->id();
    statusData.status = ui->comboBoxStatus->currentText();
    osld->updateStatus(statusData);
  }
}

// Update selected item if valid item has been typed.
void MainWindow::on_lineEditId_textChanged(const QString &text) {
  if (DiagramItem *item = osld->getAllItems()[text]) {
    this->onItemSelected(item);
  } else {
    ui->comboBoxStatus->clear();
  }
}
