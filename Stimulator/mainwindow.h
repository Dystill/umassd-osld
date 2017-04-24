#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <osldgraphicsengine.h>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPlainTextEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

 private slots:
  void on_actionOpen_Diagram_triggered();
  void onItemSelected(DiagramItem *item);

  void on_pushButtonUpdate_clicked();

  void fitDiagramToWindow();

private:
  Ui::MainWindow *ui;

  OSLDGraphicsEngine *osld;
  DiagramItem *selectedItem;
};

#endif  // MAINWINDOW_H
