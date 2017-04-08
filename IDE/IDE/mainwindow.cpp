#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    osld = new OSLDGraphicsEngine();

    QFont font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    font.setFixedPitch(true);
    font.setPointSize(8);

    ui->textEdit->setFont(font);
    ui->textEdit->setUndoRedoEnabled(true);
    ui->textEdit->setWordWrapMode(QTextOption::NoWrap);

    ui->textEdit->setTabStopWidth(3 * ui->textEdit->fontMetrics().width(' '));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_Description_File_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this,
                                                QObject::tr("Open File"),
                                                QCoreApplication::applicationDirPath(),
                                                QObject::tr("XML File(*.xml)"));
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
       {
        qDebug()<< "Error" <<endl;
       }
    QTextStream in(&file);
    ui->textEdit->setText(in.readAll());
    ui->textEdit->selectAll();
    //ui->textEdit->setTextCursor();

    osld->readFileAndRunOSLD(filePath);
    ui->graphicsView->setScene(osld);
}
