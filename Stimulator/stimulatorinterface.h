#ifndef STIMULATORINTERFACE_H
#define STIMULATORINTERFACE_H

#include <QMap>
#include <QString>
#include <QVariant>

namespace stimulator {

class StimulatorInterface {
 public:
  virtual ~StimulatorInterface();
  virtual bool searchFor(QString id) = 0;
  virtual QMap<QString, QVariant> getItemData(QString id) = 0;
  virtual QMap<QString, QVariant> getDiagramData() = 0;
  virtual int getPollingRate() = 0;
  virtual bool getBlockVisibility() = 0;
  virtual bool getDiagramTextVisibility() = 0;
};

}  // namespace stimulator

#endif  // STIMULATORINTERFACE_H
