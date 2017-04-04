#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontDatabase>
#include <osldgraphicsengine.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLoad_Description_File_triggered();

private:
    Ui::MainWindow *ui;

    OSLDGraphicsEngine *osld;
};

#endif // MAINWINDOW_H
