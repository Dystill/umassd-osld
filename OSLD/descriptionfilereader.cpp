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

    fileName = "/descriptionFileMockupVer2.xml"; //NEED TO FIND A WAY TO MAKE THIS DYNAMIC!!

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
   xmlReader.readNext();
qDebug()<< "TEST1";
   while(!xmlReader.atEnd())
   {
       qDebug()<< "TEST2";
       if(xmlReader.isStartElement())
       {
           qDebug()<< "TEST3";

           //inBuff = (xmlReader.readElementText()).toStdString();
           //outBuff = QString::fromStdString(inBuff); // Converts data types to make things workable
           if (outBuff == "diagram")
           {
                qDebug()<< "TEST4";
                title = outBuff;
                qDebug()<< "TEST5";
                qDebug()<< " Diagram's name is: "<< title;
                qDebug()<< "TEST6";
           }
       }
       else
       {
           xmlReader.readNext();
       }
   }
}



