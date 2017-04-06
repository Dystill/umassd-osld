#ifndef STIMULATOR_H
#define STIMULATOR_H

#include <QtSql>
#include <QObject>
#include "stimulatorinterface.h"

namespace stimulator {

/*!
 * \struct StatusData
 * \brief Provides the members needed to send and recieve status data between an
 * external system and the stimulator.
 * \note The stimulator must send the id and the ref_id of the block it wishes
 * to retrieve the updated status for.
 * The external system must then send back the entire struct filled out with the
 * up to date status data.
 * \ingroup stimulator
 */
struct StatusData {
  QString id;
  QString ref_id;
  QString status;
  QString name;
  QString description;
  QString hovertext;
  QString nameQuery;
  QString descriptionQuery;
  QString hovertextQuery;
};

/*!
 * \class Stimulator
 * \brief The Stimulator class implements the StimulatorInterface class
 * and provides the functionality to retrieve and add data to a database source.
 * \ingroup stimulator
 */
class Stimulator : QObject {
 public:
  Stimulator();
};

}  // namespace stimulator

#endif  // STIMULATOR_H
