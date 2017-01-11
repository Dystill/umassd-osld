#include "osldisplay.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOverrideCursor(Qt::ArrowCursor);

    OSLDisplay w(new QWidget);
    w.show();

    return a.exec();
}
