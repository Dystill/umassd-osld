#include "descriptionfilereader.h"
#include "parser.h"
#include <iostream>
#include <QXml.h>
#include <string>
#include <QXmlDefaultHandler>


DescriptionFileReader::DescriptionFileReader()
{

   Parser handler;
   QXmlSimpleReader xmlReader; //Intialize xmlReader
   xmlReader.setContentHandler(&handler);
   for (int i=1; i<10;i++)
   {
       QFile xmlFile ("descriptionFileMockup(NoComments).xml");
       QXmlInputSource source (&xmlFile);
        xmlReader.parse (source);
   }


}
