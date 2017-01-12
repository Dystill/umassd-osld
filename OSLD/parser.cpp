#include "parser.h"

Parser::Parser()
{

}

    bool Parser::startDocument()
    {
        cout<< "Searching Document";
        return true;
    }

    bool Parser (startElement(const QString&, const Qstring&, const Qstring& qName, const QXmlAttributes& att))
    {
        cout<<"Found Element" <<qName;
        return true;
    }
