#include "stimulator.h"

namespace stimulator {

/*!
 * \fn Stimulator::Stimulator()
 * Constructor
 */
Stimulator::Stimulator() {
  // Open database connection.
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(
      "/Users/pryderi/Documents/College/CIS "
      "498/umassd-osld/Stimulator/stimulator.sqlite3");
  db.open();
}

}  // namespace stimulator
