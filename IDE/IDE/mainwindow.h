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


    QString getCurrentFile() const;
    void setCurrentFile(const QString &value);

private slots:
    void on_actionLoad_Description_File_triggered();

    void on_actionNew_Description_File_triggered();

    void on_actionSave_Description_File_As_triggered();

    void on_actionShow_Block_XML_triggered();

    void on_actionShow_Gate_XML_triggered();

    void on_actionShow_Subdiagram_XML_triggered();

    void on_saveButton_clicked();


    void on_updateButton_clicked();

    void on_actionShow_Template_triggered();

    void on_actionShow_Example_triggered();


    void fitDiagramToWindow();

    void resizeEvent(QResizeEvent *event);

    void on_updateButton_pressed();

    void on_updateButton_released();

    void on_actionSave_Description_File_triggered();

private:
    Ui::MainWindow *ui;

    OSLDGraphicsEngine *osld;

    int fontSize = 10;
    int tabSize = 3;

    QString currentFile;
    QString directory;

    void runOSLD(QString filePath);

    void displayCopyTextWindow(QString filePath);
    QString displayNewFileWindow();

};

#endif // MAINWINDOW_H
