#ifndef DESCRIPTIONFILEREADER_H
#define DESCRIPTIONFILEREADER_H

#include <QtCore>
#include <QFileDialog>

#include <QDebug>

class DescriptionFileReader: public QXmlStreamReader
{
public:
    DescriptionFileReader(QWidget *parent = 0);
    ~DescriptionFileReader();

    //Methods
    void readFile(QString filepath);

    QString getDiagramName() const;
    void setDiagramName();

    QString getDescription() const;

    QString cleanString(QString s);

    void readMetaData(QString tag);
    void readBlocks();
    void readGates();
    void readSubdiagrams();

protected:
    QString path;

private:
    TokenType currentToken;
    QString diagramName;
    QString description;

};

#endif // DESCRIPTIONFILEREADER_H
//Disregard
