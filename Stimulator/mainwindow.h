#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <osldgraphicsengine.h>

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

private:
  Ui::MainWindow *ui;

  OSLDGraphicsEngine *osld;
};

#endif  // MAINWINDOW_H
