#include "osldisplay.h"
#include "descriptionfilereader.h"
#include "parser.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOverrideCursor(Qt::ArrowCursor);

    //OSLDisplay w(new QWidget);
    DescriptionFileReader x;

    //w.show();

    return a.exec();
}



