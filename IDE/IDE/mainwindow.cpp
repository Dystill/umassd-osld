#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFont font = QFont();
    font.setFamily("Courier");
    font.setStyleHint(QFont::TypeWriter);
    font.setFixedPitch(true);
    font.setPointSize(12);

    ui->textEdit->setFont(font);
}

MainWindow::~MainWindow()
{
    delete ui;
}
