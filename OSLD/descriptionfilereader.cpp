#include "descriptionfilereader.h"
#include <iostream>


DescriptionFileReader::DescriptionFileReader()
{



        xmlFile = newQFile("descriptionFileMockup(NoComments).xml");

            // Check to see if file is ready to use
            if(!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QMessageBox::critical(this,
                                      "XML File Load FFailure",
                                      "Could not open the XML file",
                                      QMessageBox::Ok);
                return;
            }

            xmlReader = new QXmlStreamReader(xmlFile);

            //Parse XML until end
            while(!xmlReader->atEnd() && !xmlReader->hasError())
            {
                //Read next element
                QXmlStreamReader::TokenType token = xmlReader->readNext();
                //If token is at the start, go to next
                if (token == QXmlStreamReader::StartDocument)
                {
                  continue;
                }

                //if token is Start Element, then read it
                if (token == StartElement)
                {
                    if(xmlReader->name() == "name") //Tries to read in data in the name metatage
                    {
                      DataStore = xmlReader->();
                      cout << DataStore;
                     continue;
                    }
                }
            }


            if(xmlReader->hasError())
        {
            QMessageBox::critical (this,
                                "descriptionFileMockup(NoComments).xml Parse Error",
                               xmlReader-errorString(),
                               QMessageBox::Ok);

            return;
        }

        //Close reader and flush
        xmlReader->clear();
        xmlFile->close();

}
