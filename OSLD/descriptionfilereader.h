#ifndef DESCRIPTIONFILEREADER_H
#define DESCRIPTIONFILEREADER_H

#include <QtCore>
#include <QtWidgets>
#include <QWidget>
#include <QObject>
#include <QTextStream>
#include <QStringList>
#include <QXmlDefaultHandler>
#include <QXmlStreamReader>

#include <QDebug>
#include "parser.h"

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

    QString getDiagramName() const;
    void setDiagramName();

    QString getDescription() const;
    void setDescription();

    QString cleanString(QString s);
protected:
    QString path;

private:
    QPushButton *loadButton;
    QLineEdit *filePathLine;
    QXmlStreamReader xmlReader;
    QXmlStreamWriter xmlWriter;
    QString Buff;
    QString diagramName;
    QString Description;
};

#endif // DESCRIPTIONFILEREADER_H
//Disregard
