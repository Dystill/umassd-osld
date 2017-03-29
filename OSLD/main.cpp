#include "osldisplay.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // DescriptionFileReader instance has been moved into OSLDGraphicsEngine

    OSLDisplay w(new QWidget);
    w.show();

    return a.exec();
}



