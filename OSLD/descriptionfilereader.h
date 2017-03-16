#ifndef DESCRIPTIONFILEREADER_H
#define DESCRIPTIONFILEREADER_H

#include <QtCore>
#include <QFileDialog>
#include <QDebug>


// holds data source information
struct CommonSource {
    QString sourceNum;
    QString name;
    QString type;
};

struct statusTypes {
    QString status;
    QString color;
    QString textColor;
    QString typeFaceFlagString;
    bool    typeFaceFlag;
};



class DescriptionFileReader: public QXmlStreamReader
{
public:
    DescriptionFileReader(QWidget *parent = 0);
    ~DescriptionFileReader();

    QMap <QString, statusTypes> statuses;



    //Methods
    void readFile(QString filepath);

    QString getDiagramName() const;
    void setDiagramName();

    QString getDescription() const;

    QString cleanString(QString s);
    void storeStatusData(QString s, statusTypes t, QString currentTag, QXmlStreamAttributes a);
    bool StringConvert (statusTypes t);
    void multiReadNext(int i);

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
