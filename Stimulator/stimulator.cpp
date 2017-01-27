#include "stimulator.h"

namespace stimulator {

/*!
 * \fn Stimulator::Stimulator()
 * Constructor
 */
Stimulator::Stimulator() {}

bool Stimulator::searchFor(QString key) {
 return true;
}

QList<QString> Stimulator::getBlockData(QString key) {
 return QList<QString>();
}

QList<QString> Stimulator::getDiagramData(QString key) {
 return QList<QString>();
}

int Stimulator::getPollingRate() {
 return 0;
}

bool Stimulator::getBlockVisibility() {
 return true;
}

bool Stimulator::getDiagramTextVisibility() {
 return true;
}

void Stimulator::addBlockData(QList<QString> data) {

}

void Stimulator::removeBlockData(QString id) {

}

void Stimulator::addDiagramData(QList<QString> data) {

}

void Stimulator::removeDiagramData(QString id) {

}

}  // namespace stimulator
