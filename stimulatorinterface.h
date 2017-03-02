#ifndef STIMULATORINTERFACE_H
#define STIMULATORINTERFACE_H

#include <QList>
#include <QString>

namespace stimulator {

class StimulatorInterface {
 public:
  virtual ~StimulatorInterface();
  virtual bool searchFor(QString key) = 0;
  virtual QList<QString> getBlockData(QString key) = 0;
  virtual QList<QString> getDiagramData(QString key) = 0;
  virtual int getPollingRate() = 0;
  virtual bool getBlockVisibility() = 0;
  virtual bool getDiagramTextVisibility() = 0;
};

}  // namespace stimulator

#endif  // STIMULATORINTERFACE_H
