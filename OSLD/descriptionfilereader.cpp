#include <QtWidgets>
#include <iostream>
#include <stdio.h>
#include <QXml.h>
#include <string>
#include "descriptionfilereader.h"
#include "parser.h"
#include <QXmlDefaultHandler>
#include<qDebug>
#include <QStringList>
#include <QXmlStreamReader>


using namespace std;

DescriptionFileReader::DescriptionFileReader(QWidget *parent) :
    QMainWindow(parent)
{

    QString pathAndName;
    QString fileName;

    fileName = "/descriptionFileMockupVer3(grouped-alt-no-comments)proto.xml"; //NEED TO FIND A WAY TO MAKE THIS DYNAMIC!!

    //Opens explorer to browse for location of XML file
    QString filePath = QFileDialog::getOpenFileName(this,tr("Open File"),"/home",tr("XML File(*.xml)"));




    QDir d = QFileInfo(filePath).absoluteDir();
    QString path = d.absolutePath(); //Gets path of file from the directory

    QFile file(filePath); //represents file that was opened


    //file.open(QIODevice::ReadOnly);
    file.setFileName(fileName);

    pathAndName = path + fileName; //Concatinates location of the file + the name of the file

    //Double Checks FilePath
    //qDebug()<<"File path of the file is:" << path;
    //qDebug()<<"File name of the file is:" << pathAndName;

    this->Read(pathAndName);
}

DescriptionFileReader::~DescriptionFileReader()
{

}


void DescriptionFileReader::Read(QString filepath)
{

   Parser handler;
   //bool hope; //determines if file is open and able to be parsed
   //xmlReader.setContentHandler(&handler);
   //xmlReader.setErrorHandler(&handler);

   QFile xmlFile (filepath);
   xmlFile.open(QIODevice::ReadOnly);
   QXmlInputSource source (&xmlFile);

    //QXmlStreamReader xmlReader(xmlFile);

    std::string inBuff;
   QString outBuff;
   QString title;
   xmlReader.setDevice(&xmlFile);

   while(!xmlReader.atEnd())
   {
       QXmlStreamReader::TokenType token = xmlReader.readNext();
       if(token == QXmlStreamReader::StartDocument)
       {
        continue;
       }

       if(token == QXmlStreamReader::StartElement)
       {

           if (xmlReader.name() == "diagram")
           {

                setDiagramName();
                 xmlReader.readNext();
           }

           if(xmlReader.name() == "description")
           {
               QString outBuff;
               QXmlStreamAttributes attributes = xmlReader.attributes();
               xmlReader.readNext();
               outBuff += attributes.value("desc").toString();
               qDebug()<< "OutBuff2:" << outBuff;
               xmlReader.readNext();
           }
       }
       else
       {
           xmlReader.readNext();
       }
   }
}

QString DescriptionFileReader::getDiagramName() const
{
    return DiagramName;
}

void DescriptionFileReader::setDiagramName()
{
    QString outBuff;
    QXmlStreamAttributes attributes = xmlReader.attributes();
    xmlReader.readNext();
    outBuff += attributes.value("name").toString();
    DiagramName = outBuff;
    qDebug()<< "OutBuff1:" << outBuff;
}

QString DescriptionFileReader::getDescription() const
{
    return Description;
}

void DescriptionFileReader::setDescription()
{


}

