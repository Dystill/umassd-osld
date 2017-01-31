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


using namespace std;

DescriptionFileReader::DescriptionFileReader(QWidget *parent) :
    QMainWindow(parent)
{

    QString pathAndName;
    QString fileName;

    fileName = "/descriptionFileMockupVer3(grouped-alt).xml"; //NEED TO FIND A WAY TO MAKE THIS DYNAMIC!!

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


    std::string inBuff;
   QString outBuff;
   QString title;
  // hope = xmlReader.parse (source);

  // qDebug()<<"Parse: "<<hope; //If returns true, it is open.

   xmlReader.setDevice(&xmlFile);
   //xmlReader.readNext();
qDebug()<< "TEST1";
   while(!xmlReader.atEnd())
   {
       qDebug()<< "TEST2";

       QXmlStreamReader::TokenType token = xmlReader.readNext();

       if(token == QXmlStreamReader::StartDocument){
       //we don’t want any of this data, it isn’t any element
       //we need.
       continue;
       }

       if(token == QXmlStreamReader::StartElement)
       {
           qDebug()<< "TEST3";

           //inBuff = (xmlReader.readElementText()).toStdString();
           //outBuff = QString::fromStdString(inBuff); // Converts data types to make things workable

           if (xmlReader.name() == "diagram")
           {
                qDebug()<< "TEST4";
                xmlReader.readNext();
                //this->title = xmlReader.text().toString();
               outBuff = xmlReader.text().toString();
                qDebug()<< "TEST5";
                qDebug()<< " Diagram's name is: "<< outBuff;
                qDebug()<< "TEST6";
           }
       }
       else
       {
           xmlReader.readNext();
       }
   }
}



