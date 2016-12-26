#include "osld.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OSLD osld;
    osld.show();

    return a.exec();
}
