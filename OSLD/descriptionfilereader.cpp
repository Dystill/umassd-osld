#include "descriptionfilereader.h"

DescriptionFileReader::DescriptionFileReader(QWidget *parent)
{
    qDebug() << "Asking user for description file location";
    // Opens explorer to browse for location of XML file
    QString filePath = QFileDialog::getOpenFileName(parent,
                                                    QObject::tr("Open File"),
                                                    QCoreApplication::applicationDirPath(),
                                                    QObject::tr("XML File(*.xml)"));

    //QFile file(filePath); // represents file that was opened
    // file.open(QIODevice::ReadOnly);
    //Double Checks FilePath
    //qDebug()<<"File path of the file is:" << path;
    //qDebug()<<"File name of the file is:" << pathAndName;

    this->readFile(filePath);
}

DescriptionFileReader::~DescriptionFileReader()
{

}


void DescriptionFileReader::readFile(QString filepath)
{
    //Parser handler;
    //bool hope; //determines if file is open and able to be parsed
    //this->setContentHandler(&handler);
    //this->setErrorHandler(&handler);

    qDebug() << ">> QXmlStreamReader";
    qDebug()<< "Reading file:" << filepath;
    QFile xmlFile(filepath);

    if(xmlFile.open(QIODevice::ReadOnly)) {
        qDebug()<< "File Opened";

        // QXmlInputSource source (&xmlFile);
        // QXmlStreamReader xmlReader(xmlFile);

        // std::string inBuff;

        qDebug()<< "Setting device to XML file";
        this->setDevice(&xmlFile);

        qDebug()<< "Begin reading";
        while(!this->atEnd()) {

            // get the type of xml element currently being read
            currentToken = this->readNext();
            qDebug() << ">> Found Token:" << (this->tokenString().replace("Characters", "String"));

            // start of document
            if(currentToken == QXmlStreamReader::StartDocument){
                qDebug()<< "Start of document";
                continue;
            }

            // start of element
            if(currentToken == QXmlStreamReader::StartElement) {

                // get the name of the current tag
                QString currentTag = this->name().toString();
                qDebug()<< "Reading in element:" << currentTag;

                // diagram tag
                if(currentTag == "diagram") {           // diagram tag
                    qDebug()<< "Setting diagram name";
                    this->setDiagramName();
                }
                else if(currentTag == "meta") {         // meta tag
                    qDebug()<< "Setting diagram name";
                    this->readMetaData();
                }
                if(currentTag == "description") {       // *test* delete this, move to readMetaData
                    qDebug()<< "Description:" << this->cleanString(this->readElementText());
                }
                else if(currentTag == "blocks") {       // blocks tag
                    qDebug()<< "do blocks stuff";
                    this->readBlocks();
                }
                else if(currentTag == "gates") {        // gates tag
                    qDebug()<< "do gates stuff";
                    this->readGates();
                }
                else if(currentTag == "subdiagrams") { // status types tag
                    qDebug()<< "do gates stuff";
                    this->readSubdiagrams();
                }
            }
        }
        qDebug()<< "End reading";
    }
}

// removes newlines and tabs from a string
QString DescriptionFileReader::cleanString(QString s) {
    return s.replace(QRegExp("\t|\n|\r"),"");
}

void DescriptionFileReader::readMetaData()
{
    // loop through each line in the meta element

    // get description text

    // get and save common sources to a QMap

    // get and save status types to another QMap

    // end loop when currentToken is EndElement and element name is "meta"
}

void DescriptionFileReader::readBlocks()
{
    // loop through each line in the blocks element
        // **be careful not to overuse "currentToken = this->readNext();"

    // for each block - NEED TO CHECK STIMULATOR AS WELL

        // create a block object pointer

        // get id and source attributes and save to block object

        // loop through each line in block

        // get dimensions - handle situation when width and height are empty

        // get location, save as QPointF object, set block location

        // *check stimulator for block status*
            // otherwise get status_info default_status attribute

        // loop through each line in status_info

            // get data element with correct for_status attribute

            // for each of name, description, hovertext

                // save column attribute to array if present

                // check for hard-coded text
                    // if present, save text to block object
                    // otherwise, go to stimulator

            // end loop when currentToken is EndElement and element name is "status_info"

        // end loop when currentToken is EndElement and element name is "block"

        // append block object pointer to a QList

    // end loop when currentToken is EndElement and element name is "blocks"

}

void DescriptionFileReader::readGates()
{
    // do basically the same thing as in readBlocks
    // make sure to save the type attribute as well
}

void DescriptionFileReader::readSubdiagrams()
{
    // loop through each line in the subdiagrams element
        // **be careful not to overuse "currentToken = this->readNext();"

    // for each subdiagram element

        // create a subdiagram object pointer

        // get root_item_id and main_diagram attributes

        // find root item by searching through block pointer list

        // set subdiagram root item to the block and the block's parent diagram to this subdiagram

        // i forgot how how we're handling main diagrams, remind me to check when you get here

        // loop through each line in subdiagram

            // go through subdiagram_data
                // get subdiagram name and description similarly to blocks
                // get root_item_location, save as QPointF object, set root block's rootlocation

            // loop through each line in connections

                // for each connect element
                    // get input and output item ids
                    // find items in either block or gate QList
                    // call subdiagram's connectItems function to connect the items
                    // add input item to subdiagram's inputItem list

            // end loop when currentToken is EndElement and element name is "connections"

        // end loop when currentToken is EndElement and element name is "subdiagram"

    // end loop when currentToken is EndElement and element name is "subdiagrams"
}

QString DescriptionFileReader::getDiagramName() const
{
    return diagramName;
}

// obtains the name attribute from the diagram tag
void DescriptionFileReader::setDiagramName()
{
    QXmlStreamAttributes attributes = this->attributes();   // get all attribute keys

    diagramName = attributes.value("name").toString();  // get the value of the name attribute
    this->readNext();   // go to the next element

    qDebug()<< "Diagram Name:" << diagramName;
}

QString DescriptionFileReader::getDescription() const
{
    return description;
}

