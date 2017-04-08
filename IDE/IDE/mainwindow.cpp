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

    this->setWindowTitle("IDE Description File Maker");
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
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<< "Error" <<endl;
    }
    QTextStream in(&file);
    ui->textEdit->setText(in.readAll());
    ui->textEdit->selectAll();

    osld->readFileAndRunOSLD(filePath);

    if(osld->getXmlError() == QXmlStreamReader::NoError) {
        ui->graphicsView->setScene(osld);
    }
    else {
        qDebug() << "IDE" << osld->getXmlErrorString();
    }
}

void MainWindow::on_actionNew_Description_File_triggered()
{
    QFile file(":/templates/new.xml");

    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<< "Error" << endl;
    }

    QTextStream in(&file);

    ui->textEdit->setText(in.readAll());

    osld->readFileAndRunOSLD(":/templates/new.xml");
    ui->graphicsView->setScene(osld);
}
