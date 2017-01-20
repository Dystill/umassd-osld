#include "parser.h"
#include <stdio.h>
#include <qstring.h>
#include <qxml.h>
#include <QTextStream>
#include<qDebug>
QTextStream cout (stdout);

//qName = expected tag


    bool Parser::startDocument()
    {
       indent = " "; //Set indent ot an empty string because root element needs to be printed without any indentation.
        return true; //return true so parser continues without reporting errors.
    }

    bool Parser::endDocument()
    {
        return true;
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
        qDebug()<< "Start of element" << qName;
        for(int i = 0; i<atts.length(); i++)
        {
            qDebug()<< atts.type(i) << "=" << atts.value(i);
        }
        return true;
    }

    bool Parser::endElement( const QString&, const QString&, const QString& qName)
    {
        qDebug() << "End of element" << qName;
        return true;
    }
//Disregard
