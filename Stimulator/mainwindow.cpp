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
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionOpen_Diagram_triggered() {
  QString filePath = QFileDialog::getOpenFileName(
      this, QObject::tr("Open File"), QCoreApplication::applicationDirPath(),
      QObject::tr("XML File(*.xml)"));

  osld->readFileAndRunOSLD(filePath);
  ui->graphicsView->setScene(osld);
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
