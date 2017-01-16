#ifndef PARSER_H
#define PARSER_H

#include <qxml.h>


class Parser : public QXmlDefaultHandler
{
public:
    bool startDocument();
    bool startElement( const QString & namespaceURI, const QString & localName, const QString & qName ,
                       const QXmlAttributes & atts );
    bool characters(const QString& text);
    bool endElement ( const QString & namespaceURI, const QString & localName, const QString & qName);

private:
    QString indent; //Use this to get indentation.

};

#endif // PARSER_H
