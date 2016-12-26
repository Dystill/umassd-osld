#include "osld.h"
#include "ui_osld.h"

OSLD::OSLD(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::OSLD)
{

    ui->setupUi(this);

}

OSLD::~OSLD()
{
    delete ui;
}

void OSLD::expandSubdiagram() {

}

void OSLD::closeSubdiagram() {

}

void OSLD::updateTextVisibility() {

}

void OSLD::refresh() {

}


