#include <QApplication>
#include "mainwindow.h"
#include "stimulator.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  stimulator::Stimulator stim;
  qDebug() << stim.getItemData("ABC123")["a"].toString();

  return a.exec();
}
