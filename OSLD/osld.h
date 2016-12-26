#ifndef OSLD_H
#define OSLD_H

#include <QMainWindow>
#include <string>
#include <vector>

namespace Ui {
    class OSLD;
    // class Block;
}

class OSLD : public QMainWindow
{
    Q_OBJECT

public:
    explicit OSLD(QWidget *parent = 0);
    ~OSLD();
    void expandSubdiagram();
    void closeSubdiagram();
    void updateTextVisibility();
    void refresh();

private:
    Ui::OSLD *ui;
    std::string title;
    std::string description;
    //std::vector<Ui::Block> blocks;
    int numOfGates;
};

#endif // OSLD_H
