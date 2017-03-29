#include "stimulator.h"

namespace stimulator {

/*!
 * \fn Stimulator::Stimulator()
 * Constructor
 */
Stimulator::Stimulator() {
  // Open database connection.
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("stimulator.sqlite3");
  db.open();
}

bool Stimulator::searchFor(QString id) {
  QSqlQuery query;

  query.prepare("SELECT id FROM Item WHERE id = ?");
  query.addBindValue(id);
  query.exec();

  return query.next();
}

QMap<QString, QVariant> Stimulator::getItemData(QString id) {
  QMap<QString, QVariant> result;
  QSqlQuery query;

  query.prepare(
      "SELECT (ref_id, source, type, width, height, x, y, default_status) FROM "
      "Item WHERE id = ?");
  query.addBindValue(id);
  query.exec();

  if (query.next()) {
    result = recordToQMap(query.record());
  }

  return result;
}

QMap<QString, QVariant> Stimulator::getDiagramData() {
  QMap<QString, QVariant> result;
  QSqlQuery query;

  query.exec("SELECT (name, description) FROM Diagram");

  if (query.next()) {
    result = recordToQMap(query.record());
  }

  return result;
}

int Stimulator::getPollingRate() { return 0; }

bool Stimulator::getBlockVisibility() { return true; }

bool Stimulator::getDiagramTextVisibility() { return true; }

void Stimulator::addBlockData(QMap<QString, QVariant> data) {}

void Stimulator::removeBlockData(QString id) {}

void Stimulator::addDiagramData(QMap<QString, QVariant> data) {}

void Stimulator::removeDiagramData(QString id) {}

QMap<QString, QVariant> Stimulator::recordToQMap(QSqlRecord record) {
  QMap<QString, QVariant> qMap;

  for (int i = 0; i < record.count(); i++) {
    qMap.insert(record.fieldName(i), record.value(i));
  }

  return qMap;
}

}  // namespace stimulator
