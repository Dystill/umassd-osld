#ifndef DESCRIPTIONFILEREADER_H
#define DESCRIPTIONFILEREADER_H

#include <QWidget>
#include <QObject>

#include <QXmlSimpleReader>
#include <QtCore>
#include <QMainWindow>

class QPushButton;
class QLineEdit;

namespace Ui {
class descriptionfilereader;
}

class DescriptionFileReader: public QMainWindow
{
    Q_OBJECT

public:
    DescriptionFileReader(QWidget *parent = 0);
    ~DescriptionFileReader();

    //Methods
    void Read(QString filepath);

protected:
    QString path;
private:
    QPushButton *loadButton;
    QLineEdit *filePathLine;
    QXmlSimpleReader xmlReader;
};

#endif // DESCRIPTIONFILEREADER_H
//Disregard
