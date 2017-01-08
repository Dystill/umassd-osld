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

private slots:
    void on_actionFullScreen_triggered();
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    bool eventFilter(QObject *object, QEvent *event);

private:
    Ui::OSLDisplay *ui;
    OSLDGraphicsEngine *scene;
    void enterFullScreen();
    void exitFullScreen();
};

#endif // OSLDISPLAY_H
