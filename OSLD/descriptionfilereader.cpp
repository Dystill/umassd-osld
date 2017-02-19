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

                QString currentTag = xmlReader.name().toString();
                qDebug()<< "Found element:" << currentTag;

                if(currentTag == "diagram") {
                    qDebug()<< "Setting diagram name";
                    this->setDiagramName();
                }
                else if(currentTag == "description") {
                    qDebug()<< "do description stuff";
                    /*
                    qDebug()<< "Found description element";
                    QXmlStreamAttributes attributes = xmlReader.attributes();
                    xmlReader.readNext();
                    outBuff += attributes.value("desc").toString();
                    qDebug()<< "OutBuff2:" << outBuff;
                    xmlReader.readNext();
                    */
                }
                else if(currentTag == "common_source") {
                    qDebug()<< "do common_source stuff";
                }
                else if(currentTag == "status_types") {
                    qDebug()<< "do status_types stuff";
                }
            }
        }
        qDebug()<< "End reading";
    }
}

QString DescriptionFileReader::getDiagramName() const
{
    return DiagramName;
}

void DescriptionFileReader::setDiagramName()
{
    QXmlStreamAttributes attributes = xmlReader.attributes();
    xmlReader.readNext();

    DiagramName = attributes.value("name").toString();

    qDebug()<< "Diagram Name:" << DiagramName;
}

QString DescriptionFileReader::getDescription() const
{
    return Description;
}

void DescriptionFileReader::setDescription()
{


}

