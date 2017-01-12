#include "descriptionfilereader.h"
#include <iostream>
#include <QXml.h>
#include <string>
#include <QXmlDefaultHandler>


DescriptionFileReader::DescriptionFileReader()
{

   QXmlInputSource* source = new QXmlInputSource(new QFile("descriptionFileMockup(NoComments).xml")); //Shows what file to use.
   QXmlSimpleReader xmlReader; //Intialize xmlReader
   Parser* handler = new Parser();
   xmlReader.setContentHandler(handler);
   xmlReader.parse (source);
            //Parse XML until end

        //Close reader and flush


}
