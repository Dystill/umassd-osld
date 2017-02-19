#include "descriptionfilereader.h"

using namespace std;

DescriptionFileReader::DescriptionFileReader(QWidget *parent) :
    QMainWindow(parent)
{
    qDebug() << "Asking user for description file location";
    // Opens explorer to browse for location of XML file
    QString filePath = QFileDialog::getOpenFileName(this,tr("Open File"),QCoreApplication::applicationDirPath(),tr("XML File(*.xml)"));

    QFile file(filePath); // represents file that was opened


    // file.open(QIODevice::ReadOnly);
    //Double Checks FilePath
    //qDebug()<<"File path of the file is:" << path;
    //qDebug()<<"File name of the file is:" << pathAndName;

    qDebug() << "Calling QXmlStreamReader";
    this->Read(filePath);
}

DescriptionFileReader::~DescriptionFileReader()
{

}


void DescriptionFileReader::Read(QString filepath)
{
    //Parser handler;
    //bool hope; //determines if file is open and able to be parsed
    //xmlReader.setContentHandler(&handler);
    //xmlReader.setErrorHandler(&handler);

    qDebug() << ">> QXmlStreamReader";
    qDebug()<< "Reading file:" << filepath;
    QFile xmlFile(filepath);

    if(xmlFile.open(QIODevice::ReadOnly)) {
        qDebug()<< "File Opened";

        // QXmlInputSource source (&xmlFile);
        // QXmlStreamReader xmlReader(xmlFile);

        // std::string inBuff;

        qDebug()<< "Setting device to XML file";
        xmlReader.setDevice(&xmlFile);

        QString outBuff;
        qDebug()<< "Begin reading";
        while(!xmlReader.atEnd()) {

            QXmlStreamReader::TokenType token = xmlReader.readNext();
            qDebug() << ">> Found Token:" << xmlReader.tokenString();

            // start of document
            if(token == QXmlStreamReader::StartDocument){
                qDebug()<< "Start of document";
                continue;
            }

            // start of element
            if(token == QXmlStreamReader::StartElement) {

                // get the name of the current tag
                QString currentTag = xmlReader.name().toString();
                qDebug()<< "Reading in tag:" << currentTag;

                if(currentTag == "diagram") {   // diagram tag
                    qDebug()<< "Setting diagram name";
                    this->setDiagramName();
                }
                else if(currentTag == "description") {  // *ANY* description tag
                    qDebug()<< "Description:" << this->cleanString(xmlReader.readElementText());
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

QString DescriptionFileReader::getDiagramName() const
{
    return diagramName;
}

// obtains the name attribute from the diagram tag
void DescriptionFileReader::setDiagramName()
{
    QXmlStreamAttributes attributes = xmlReader.attributes();   // get all attribute keys

    diagramName = attributes.value("name").toString();  // get the value of the name attribute
    xmlReader.readNext();   // go to the next element

    qDebug()<< "Diagram Name:" << diagramName;
}

// removes newlines and tabs from a string
QString DescriptionFileReader::cleanString(QString s) {
    return s.replace(QRegExp("\t|\n|\r"),"");
}

QString DescriptionFileReader::getDescription() const
{
    return Description;
}

void DescriptionFileReader::setDescription()
{


}

