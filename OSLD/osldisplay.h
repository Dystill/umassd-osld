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
private slots:
    void on_actionFullScreen_triggered();
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    bool eventFilter(QObject *object, QEvent *event);
    void resizeEvent(QResizeEvent *event);

    void on_actionShowGrid_triggered();

    void on_closeButton_clicked();

    void on_actionFitDiagramToWindow_triggered();

    void on_actionHideCloseButton_triggered();

    void on_actionHideBlockTitles_triggered(bool checked);

private:
    Ui::OSLDisplay *ui;
    OSLDGraphicsEngine *scene;

    qreal windowSizePercent = 0.75;
    qreal scaleAmount = 100;
    bool initScaleFix = false;  // cannot figure out why the scene becomes really small initially, so this helps fix it

    void prepareGraphicsView();
    void enterFullScreen();
    void exitFullScreen();
    void zoom(int px);
    void fitToWindow();
};

#endif // OSLDISPLAY_H
