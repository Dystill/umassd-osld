#ifndef STIMULATOR_H
#define STIMULATOR_H

#include "stimulatorinterface.h"

namespace stimulator {

/*!
 * \class Stimulator
 * \brief The Stimulator class implements the StimulatorInterface class
 * and provides the functionality to retrieve and add data to a database source.
 * \ingroup stimulator
 */
class Stimulator : StimulatorInterface {
 public:
  Stimulator();
  bool searchFor(QString key);
  QList<QString> getBlockData(QString key);
  QList<QString> getDiagramData(QString key);
  int getPollingRate();
  bool getBlockVisibility();
  bool getDiagramTextVisibility();
  void addBlockData(QList<QString> data);
  void removeBlockData(QString id);
  void addDiagramData(QList<QString> data);
  void removeDiagramData(QString id);

 private:
  int pollingRate;
  bool hideBlockText;
  bool hideDiagramText;
};

}  // namespace stimulator

#endif  // STIMULATOR_H
