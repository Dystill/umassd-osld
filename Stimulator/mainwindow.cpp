#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // Initialize tool bar widgets.
  lineEditTitle = new QLineEdit();
  lineEditHoverText = new QLineEdit();
  lineEditStatus = new QLineEdit();
  plainTextEditDescription = new QPlainTextEdit();

  labelTitle = new QLabel("Title");
  labelHoverText = new QLabel("Hover Text");
  labelStatus = new QLabel("Status");
  labelDescription = new QLabel("Description");

  // Add widgets to tool bar.
  ui->mainToolBar->addWidget(labelTitle);
  ui->mainToolBar->addWidget(lineEditTitle);

  ui->mainToolBar->addWidget(labelHoverText);
  ui->mainToolBar->addWidget(lineEditHoverText);

  ui->mainToolBar->addWidget(labelStatus);
  ui->mainToolBar->addWidget(lineEditStatus);

  ui->mainToolBar->addWidget(labelDescription);
  ui->mainToolBar->addWidget(plainTextEditDescription);
}

MainWindow::~MainWindow() { delete ui; }
