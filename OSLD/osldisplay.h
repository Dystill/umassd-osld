#ifndef OSLDISPLAY_H
#define OSLDISPLAY_H

#include <QMainWindow>

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
};

#endif // OSLDISPLAY_H
