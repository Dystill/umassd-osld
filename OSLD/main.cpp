#include "osldisplay.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOverrideCursor(Qt::ArrowCursor);

    // DescriptionFileReader x(new QWidget);

    OSLDisplay w(new QWidget);
    w.show();

    return a.exec();
}



