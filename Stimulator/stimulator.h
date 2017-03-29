#ifndef STIMULATOR_H
#define STIMULATOR_H

#include "stimulatorinterface.h"
#include <QtSql>

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
  QMap<QString, QVariant> getItemData(QString id);
  QMap<QString, QVariant> getDiagramData();
  int getPollingRate();
  bool getBlockVisibility();
  bool getDiagramTextVisibility();
  void addBlockData(QMap<QString, QVariant> data);
  void removeBlockData(QString id);
  void addDiagramData(QMap<QString, QVariant> data);
  void removeDiagramData(QString id);

 private:
  int pollingRate;
  bool hideBlockText;
  bool hideDiagramText;
  QMap<QString, QVariant> recordToQMap(QSqlRecord record);
};

}  // namespace stimulator

#endif  // STIMULATOR_H
