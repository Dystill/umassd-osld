#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontDatabase>
#include <osldgraphicsengine.h>
#include <copydialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void printFileToScreen(QString filepath);
    ~MainWindow();


private slots:
    void on_actionLoad_Description_File_triggered();

    void on_actionNew_Description_File_triggered();

    void on_actionShow_Block_XML_triggered();

    void on_actionShow_Gate_XML_triggered();

    void on_actionShow_Subdiagram_XML_triggered();

    void on_saveButton_clicked();

private:
    Ui::MainWindow *ui;

    OSLDGraphicsEngine *osld;

    int fontSize = 10;
    int tabSize = 3;

    QString currentFile;

    void runOSLD(QString filePath);

    void displayCopyTextWindow(QString filePath);


};

#endif // MAINWINDOW_H
