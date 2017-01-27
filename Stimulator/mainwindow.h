#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

 private:
  Ui::MainWindow *ui;

  QLabel *labelTitle;
  QLabel *labelHoverText;
  QLabel *labelStatus;
  QLabel *labelDescription;

  QLineEdit *lineEditTitle;
  QLineEdit *lineEditHoverText;
  QLineEdit *lineEditStatus;
  QPlainTextEdit *plainTextEditDescription;
};

#endif  // MAINWINDOW_H
