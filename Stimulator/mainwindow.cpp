#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  osld = new OSLDGraphicsEngine();

  connect(osld, SIGNAL(itemSelected(DiagramItem *)), this,
          SLOT(onItemSelected(DiagramItem *)));
  connect(ui->lineEditId, SIGNAL(returnPressed()), this,
          SLOT(on_pushButtonUpdate_clicked()));
  connect(ui->comboBoxStatus, SIGNAL(currentIndexChanged(const QString &)),
          this, SLOT(on_pushButtonUpdate_clicked()));
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
