#ifndef PARSER_H
#define PARSER_H

#include <qxml.h>


class Parser : public QXmlDefaultHandler
{
public:
    bool startDocument();
    bool endDocument();

    bool startElement( const QString & namespaceURI, const QString & localName, const QString & qName ,
                       const QXmlAttributes & atts );
    bool characters(const QString& text);
    bool endElement ( const QString & namespaceURI, const QString & localName, const QString & qName);
    /**
    void setDiagramName(QString input);
    void setDescription(QString input);
    void setCommonSource(QString input, QString input);
    void setDimensions(int dpi, int minWidth, int minHeight, int maxWidth, int maxHeight);
    void setStatusId(QString statusId1, QString statusId1Color, QString statusId2, QString statusId2Color, QString statusId3, QString statusId3Color);

    void setBlockLocation(QString BlockID, int X, int Y);
    void setBlockInfo(QString dataId, QString nameColumn, QString descriptionColumn);

    void setSubdiagramData(QString gateID, QString source, QString type,
    QList<QString> getBlockInfo();
    */
private:
    QString indent; //Use this to get indentation.

};

#endif // PARSER_H
//Disregard
