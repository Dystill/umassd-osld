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
                if(currentTag == "diagram") {   // diagram tag
                    qDebug()<< "Setting diagram name";
                    this->setDiagramName();
                }
                if(currentTag == "meta") {   // diagram tag
                    qDebug()<< "Setting diagram name";
                    this->readMetaData();
                }
                else if(currentTag == "description") {  // *ANY* description tag
                    qDebug()<< "Description:" << this->cleanString(this->readElementText());
                }
                else if(currentTag == "common_source") {    // common source tag
                    qDebug()<< "do common_source stuff";
                }
                else if(currentTag == "status_types") { // status types tag
                    qDebug()<< "do status_types stuff";
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

}

void DescriptionFileReader::readBlocks()
{

}

void DescriptionFileReader::readGates()
{

}

void DescriptionFileReader::readSubdiagrams()
{

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

