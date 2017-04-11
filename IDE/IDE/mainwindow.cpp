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
    font.setPointSize(fontSize);

    ui->textEdit->setFont(font);
    ui->textEdit->setUndoRedoEnabled(true);
    ui->textEdit->setWordWrapMode(QTextOption::NoWrap);

    ui->textEdit->setTabStopWidth(tabSize * ui->textEdit->fontMetrics().width(' '));

    this->setWindowTitle("IDE Description File Maker");

    connect(osld, SIGNAL(subdiagramChanged()), this, SLOT(fitDiagramToWindow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_Description_File_triggered()
{
    // open window for user to choose file
    currentFile = QFileDialog::getOpenFileName(this,
                                                QObject::tr("Open File"),
                                                QCoreApplication::applicationDirPath(),

                                               QObject::tr("XML File(*.xml)"));

    // create the file object
    QFile file(currentFile);

    // open the file
    if(file.open(QIODevice::ReadOnly)) {
        // read the file
        QTextStream in(&file);

        // add text to textedit window
        ui->textEdit->setText(in.readAll());

        // run the graphics
        this->runOSLD(currentFile);
    }
}

void MainWindow::on_actionNew_Description_File_triggered()
{
    QFile file(":/templates/new.xml");

    if(file.open(QIODevice::ReadOnly)) {
        // read the file
        QTextStream in(&file);

        // add text to textedit window
        ui->textEdit->setText(in.readAll());

        // run the graphics
        osld->readFileAndRunOSLD(":/templates/new.xml");
        ui->graphicsView->setScene(osld);
    }

    currentFile = "";
}

void MainWindow::runOSLD(QString filePath)
{
    // read and run the file in the specified path
    osld->readFileAndRunOSLD(filePath);

    // check for any errors
    if(osld->getXmlError() == QXmlStreamReader::NoError) {
        ui->graphicsView->setScene(osld);   // display graphics if no errors
        this->fitDiagramToWindow();
    }
    else {
        // notify about error if there is one
        QMessageBox::warning(this,"Error",osld->getXmlErrorString());
    }
}

void MainWindow::fitDiagramToWindow()
{
    // update scene rect to fit the items
    osld->setSceneRect(osld->itemsBoundingRect().adjusted(-36, -36, 36, 36));

    // resize the view contents to match the window size
    ui->graphicsView->fitInView(osld->sceneRect(), Qt::KeepAspectRatio);

    qDebug() << "testing fit";
}

void MainWindow::displayCopyTextWindow(QString filePath)
{
    CopyDialog *dialog = new CopyDialog(filePath, this);
    dialog->exec();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    this->fitDiagramToWindow();
}

void MainWindow::on_actionShow_Block_XML_triggered()
{
    this->displayCopyTextWindow(":/templates/block.xml");
}

void MainWindow::on_actionShow_Gate_XML_triggered()
{
    this->displayCopyTextWindow(":/templates/gate.xml");
}

void MainWindow::on_actionShow_Subdiagram_XML_triggered()
{
    this->displayCopyTextWindow(":/templates/subdiagram.xml");
}


void MainWindow::on_actionShow_Example_triggered()
{
    this->displayCopyTextWindow(":/templates/example.xml");
}

void MainWindow::on_actionShow_Template_triggered()
{
    this->displayCopyTextWindow(":templates/new.xml");
}

void MainWindow::on_updateButton_clicked()
{
    QFile file(currentFile);

    // open the file
    if(file.open(QIODevice::ReadOnly)) {
        // read the file
        QTextStream in(&file);

        // add text to textedit window
        ui->textEdit->setText(in.readAll());

        // run the graphics
        this->runOSLD(currentFile);
    }
}

void MainWindow::on_actionSave_Description_File_As_triggered()
{
   // QString fileName = QFileDialog::getSaveFileName(this,"IDE - Save as",)
}

void MainWindow::on_saveButton_clicked()
{

    QFile file(currentFile);
    if(file.open(QFile::WriteOnly))
    {
        file.write(ui->textEdit->toPlainText().toUtf8());
    }
    else
    {
        //QMessageBox::warning(this,"mainwindow",tr("Cannot write file %1.\nError: %2"))
         //       .arg(currentFile)
         //       .arg(file.errorString());
    }
    /*if(currentFile.isEmpty()) {
        // if the file does not exists
    }
    else {
        // if a file needs to be overwritten
    }*/
}
