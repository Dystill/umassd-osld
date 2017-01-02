#ifndef OSLDISPLAY_H
#define OSLDISPLAY_H

#include <QMainWindow>
#include <QtCore>
#include "block.h"  // testing block

namespace Ui {
class OSLDisplay;
}

class OSLDisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit OSLDisplay(QWidget *parent = 0);
    ~OSLDisplay();

private:
    Ui::OSLDisplay *ui;
    QGraphicsScene *scene;  // testing block
    Block *block;           // testing block
};

#endif // OSLDISPLAY_H
