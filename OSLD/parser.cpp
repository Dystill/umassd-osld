#include "parser.h"
#include <stdio.h>
#include <qstring.h>
#include <qxml.h>
#include <QTextStream>
QTextStream cout (stdout);


    bool Parser::startDocument()
    {
       indent = " "; //Set indent ot an empty string because root element needs to be printed without any indentation.
        return true; //return true so parser continues without reporting errors.
    }

    bool Parser::characters(const QString& text)
    {
        QString t = text;
        cout << t.remove('\n');
        return true;
    }

    bool Parser::startElement(const QString&, const QString&,
                              const QString& qName,
                              const QXmlAttributes& atts)
    {
        QString str = QString("\n%1\\%2").arg(indent).arg(qName);
        cout << str;
        if (atts.length()>0)
        {
            QString fieldName = atts.qName(0);
            QString fieldValue = atts.value(0);
            cout << QString("(%2=%3)").arg(fieldName).arg(fieldValue);
        }
        cout << "{";
        indent += "    ";
        return true;
    }
    bool Parser::endElement( const QString&, const QString&, const QString& )
    {
        indent.remove( (uint)0, 4 );
        return true;
    }
//Disregard
