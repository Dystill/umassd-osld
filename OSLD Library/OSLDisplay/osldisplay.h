#ifndef OSLDISPLAY_H
#define OSLDISPLAY_H

#include <QMainWindow>
#include <QScrollBar>
#include <QtCore>
#include "osldgraphicsengine.h"

namespace Ui {
class OSLDisplay;
}

class OSLDisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit OSLDisplay(QWidget *parent = 0);
    ~OSLDisplay();
protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private slots:
    void on_actionFullScreen_triggered();
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    bool eventFilter(QObject *object, QEvent *event);
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);

    void on_closeButton_clicked();

    void on_actionFitDiagramToWindow_triggered();

    void on_actionHideBlockTitles_triggered(bool checked);

    void on_actionSwitchOrientation_triggered();

    void on_actionOpenDescriptionFile_triggered();

    void on_actionHideButtons_triggered(bool checked);

    void on_actionShowGrid_triggered(bool checked);

private:
    Ui::OSLDisplay *ui;
    OSLDGraphicsEngine *scene;

    qreal windowSizePercent = 0.50;
    qreal rootViewWidth = 1.8;
    qreal scaleAmount = 100;
    bool initScaleFix = false;  // cannot figure out why the scene becomes really small initially, so this helps fix it

    void prepareGraphicsView();
    void prepareRootView(QString orientation);
    void enterFullScreen();
    void exitFullScreen();
    void zoom(int px);
    void fitDiagramAndRootToWindow();
    void addMenuBarActionsToDisplay();
    void displayDiagram();
    void readEnvironmentVariables();

public slots:
    void fitDiagramToWindow();

};

#endif // OSLDISPLAY_H
