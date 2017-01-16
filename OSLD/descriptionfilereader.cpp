#include "descriptionfilereader.h"
#include "parser.h"
#include <iostream>
#include <QXml.h>
#include <string>
#include <QXmlDefaultHandler>
using namespace std;

DescriptionFileReader::DescriptionFileReader()
{

}

DescriptionFileReader::~DescriptionFileReader()
{

}



void DescriptionFileReader::Read()
{

   Parser handler;
   QXmlSimpleReader xmlReader; //Intialize xmlReader
   cout<< "test a";
   xmlReader.setContentHandler(&handler);
   for (int i=1; i<1;i++)//It should only read the first 10 lines.
   {
       cout<< "test "<< i;
       QFile xmlFile ("descriptionFileMockupVer2.xml");
       QXmlInputSource source (&xmlFile);
        xmlReader.parse (source);
   }


}
//Disregard
