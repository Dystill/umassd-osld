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


            // qDebug string to print current token type
            // prints every line read in the xml file

            QString tString = (this->tokenString().replace("Characters", "String") +
                               (this->tokenString().contains("Element") ? " " : "") + this->name().toString());
            qDebug() << ">> Found Token:" << tString;


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
                    qDebug()<< "calling readMetaData function"<<endl;
                    this->readMetaData(currentTag);
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
                    qDebug()<< "do subdiagram stuff";
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

void DescriptionFileReader::multiReadNext(int i)
{
    int x;
    for(x = 0; x<i; x++)
    {
        this->readNext();
    }
}

bool DescriptionFileReader::StringConvert (statusTypes t)
{
    if(t.typeFaceFlagString == "true")
        return true;
    else
        return false;
}

void DescriptionFileReader::storeStatusData(QString s, statusTypes t, QString currentTag, QXmlStreamAttributes a)
{
    t.status = s;
    qDebug()<<"Status is: "<< t.status;
    this->multiReadNext(2);
    currentTag = this->name().toString();
    if(currentTag == "color")
    {
        this->readNext();
        t.color = cleanString(QXmlStreamReader::text().toString());
        qDebug()<<"Color is: "<< t.color;
        this->readNext();
    }

    this->multiReadNext(2);
    currentTag = this->name().toString();
    if(currentTag == "textcolor")
    {
        this->readNext();
        t.textColor = cleanString(QXmlStreamReader::text().toString());
        qDebug()<<"TextColor is: "<< t.textColor;
        this->readNext();
    }
    this->multiReadNext(2);
    currentTag = this->name().toString();

    if(currentTag == "italics")
    {
        qDebug()<<"Typeface type: " << currentTag;
        this->readNext();
        t.typeFaceFlagString = cleanString(QXmlStreamReader::text().toString());
        qDebug()<<"Typeface flag: " << t.typeFaceFlagString << endl;
        t.typeFaceFlag = StringConvert (t);
        this->readNext();
        currentTag = this->name().toString();
    }

    if(currentTag == "bold")
    {
        qDebug()<<"Typeface type: " << currentTag;
        this->readNext();
        t.typeFaceFlagString = cleanString(QXmlStreamReader::text().toString());
        qDebug()<<"Typeface flag: " << t.typeFaceFlagString << endl;
        t.typeFaceFlag = StringConvert (t);
        this->readNext();
        currentTag = this->name().toString();
    }

    if(currentTag == "underline")
    {
        qDebug()<<"Typeface type: " << currentTag;
        this->readNext();
        t.typeFaceFlagString = cleanString(QXmlStreamReader::text().toString());
        qDebug()<<"Typeface flag: " << t.typeFaceFlagString << endl;
        t.typeFaceFlag = StringConvert (t);
        this->readNext();
        currentTag = this->name().toString();
    }

}

void DescriptionFileReader::readMetaData(QString tag)
{
    statusTypes status1;
    statusTypes status2;
    statusTypes status3;
    int statCount = 1; //Will be incremented for each status type read, being able to check for another status after scanning through the current one
    tag = this->name().toString();
    bool processed = false;
    ////////V-Magic Starts Here-V////////
    while (!processed)
    {
        currentToken = this->readNext();
        QString tString = (this->tokenString().replace("Characters", "String") +
                               (this->tokenString().contains("Element") ? " " : "") + this->name().toString());
        if(currentToken == QXmlStreamReader::StartElement)
        {
            // get the name of the current tag
            QString currentTag = this->name().toString();
            //qDebug()<<"-------------------------TAG 2 is: " << currentTag << endl;

                if(currentTag == "description")
                {
                    this->readNext();
                    //   // get all attribute keys
                    description = cleanString(QXmlStreamReader::text().toString());  // get the value of the name attribute
                    this->readNext();   // go to the next element
                    qDebug()<<"Description: " << description <<endl;
                }
                ///////////////////////////////////////////////////
                if(currentTag == "source")
                {
                    CommonSource A;
                    CommonSource B;
                    QXmlStreamAttributes attributes = this->attributes();
                    if(attributes.value("id").toString() == "source1")
                    {

                        A.sourceNum = attributes.value("id").toString();
                        qDebug()<<"Source is: "<< A.sourceNum;
                        this->multiReadNext(2); //Needs to readNext() twice because it parse to the next start element tag to the actual body of the start element tag.
                        currentTag = this->name().toString();

                        if(currentTag == "name")
                        {
                            this->readNext();
                            A.name = cleanString(QXmlStreamReader::text().toString());
                            this->readNext();
                            qDebug()<<"Name is: "<< A.name;
                        }
                        this->multiReadNext(2);//Needs to readNext() twice because it parse to the next start element tag to the actual body of the start element tag.
                        currentTag = this->name().toString();

                        if(currentTag == "type")
                        {
                            this->readNext();
                            A.type = cleanString(QXmlStreamReader::text().toString());
                            this->readNext();
                            qDebug()<<"Type is: "<< A.type<<endl;
                        }

                    }
                    if(attributes.value("id").toString() == "source2")
                    {

                        B.sourceNum = attributes.value("id").toString();
                        qDebug()<<"Source is: "<< B.sourceNum;
                        this->multiReadNext(2);
                        currentTag = this->name().toString();

                        if(currentTag == "name")
                        {
                            this->readNext();
                            B.name = cleanString(QXmlStreamReader::text().toString());
                            this->readNext();
                            qDebug()<<"Name is: "<< B.name;
                        }
                        this->multiReadNext(2);
                        currentTag = this->name().toString();

                        if(currentTag == "type")
                        {
                            this->readNext();
                            B.type = cleanString(QXmlStreamReader::text().toString());
                            this->readNext();
                            qDebug()<<"Type is: "<< B.type<<endl;
                        }

                    }
                }
                ///////////////////////////////////////////////////
                if(currentTag == "status")
                {
                    if(statCount == 1)
                    {
                        QXmlStreamAttributes attributes;
                        attributes = this->attributes();
                        currentTag = this->name().toString();
                            if(attributes.value("id").toString() == "Valid")//Need way to make "attributes.value("id").toString()" able to be compared with a variable beforehand to make it fully dynamic for status naming. Needs a pre-scanning
                            {
                                storeStatusData(attributes.value("id").toString(), status1, currentTag, attributes);
                                statCount = statCount + 1;
                            }
                        this->multiReadNext(4);
                        statuses.insert(status1.status,status1);
                    }
                    if(statCount == 2)
                    {
                        QXmlStreamAttributes attributes;
                        attributes = this->attributes();
                        currentTag = this->name().toString();
                        if(attributes.value("id").toString() == "Invalid")
                        {
                            storeStatusData(attributes.value("id").toString(), status2, currentTag, attributes);
                            statCount = statCount + 1;
                        }
                        this->multiReadNext(4);
                        statuses.insert(status2.status,status2);
                    }
                    if(statCount == 3)
                    {
                        QXmlStreamAttributes attributes;
                        attributes = this->attributes();
                        currentTag = this->name().toString();
                        if(attributes.value("id").toString() == "Unknown")
                        {
                            storeStatusData(attributes.value("id").toString(), status3, currentTag, attributes);
                            statCount = statCount + 1;
                        }
                        statuses.insert(status3.status,status3);
                    }
                }
                ///////////////////////////////////////////////////
            }

            if(currentToken == QXmlStreamReader::EndElement && tString == "EndElement meta")
            {
                qDebug() << "FINISHED PROCESSING META" << endl;
                processed = true;
            }
        }


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

    // loop through each line in the blocks element
        // **be careful not to overuse "currentToken = this->readNext();"


    // update token and tag
    currentToken = this->readNext();
    QString currentTag = this->name().toString();
    QString tString = "";
    QXmlStreamAttributes attributes;

    qDebug() << "==================================START GATE==================================";
    while(currentTag != "gates" || currentToken != QXmlStreamReader::EndElement) {

        Gate *gate;

        // print to qdebug the current token type
        tString = (this->tokenString().replace("Characters", "String") +
                               (this->tokenString().contains("Element") ? " " : "") + this->name().toString());
        //qDebug() << ">> Found Token:" << tString;

        // get gate attributes
        if(currentTag == "gate" && currentToken == QXmlStreamReader::StartElement) {
            qDebug() << "------ Start reading gate ------";
            attributes = this->attributes();

            if(attributes.hasAttribute("id")) {
                attributes.value("type").toString();
                gate = new Gate(attributes.value("id").toString());
                qDebug() << "Found gate id" << gate->id();

            }
            if(attributes.hasAttribute("type")) {
                gate->setGateType(attributes.value("type").toString());
                qDebug() << "Found gate type" << attributes.value("type").toString();
            }
            if(attributes.hasAttribute("source")) {
                gate->setSourceId(attributes.value("source").toString());
                qDebug() << "Found gate source" << gate->getSourceId();

                // CONTACT STIMULATOR HERE

                // gate->setXXX
            }
        }
        // get dimensions data
        else if(currentTag == "dimensions" && currentToken == QXmlStreamReader::StartElement) {
            QMap<QString, int> dimension = this->getDimensions();
            gate->setGateSizing(dimension["width"],dimension["height"]);
            qDebug() << "Dimensions Set!" << gate->width() << gate->height();
        }
        // get location data
        else if(currentTag == "location" && currentToken == QXmlStreamReader::StartElement) {
            QPointF location = this->getLocationPoint();
            gate->setLocation(location);
            qDebug() << "Location Set!" << gate->pos();
        }
        // get status info
        else if(currentTag == "status_info" && currentToken == QXmlStreamReader::StartElement) {
            this->getStatusInfo();
        }
        // at end of gate element
        else if(currentTag == "gate" && currentToken == QXmlStreamReader::EndElement) {
            allGates.append(gate);
            qDebug() << "------ Stored gate! ------";
        }

        // update token and tag
        currentToken = this->readNext();
        currentTag = this->name().toString();
    }

    qDebug() << "Gates stored:" << allGates.count();

    qDebug() << "===================================END GATE===================================";
    // for each gate - NEED TO CHECK STIMULATOR AS WELL

        // create a gate object pointer

        // get id and source attributes and save to gate object

        // loop through each line in gate

        // get dimensions - handle situation when width and height are empty

        // get location, save as QPointF object, set gate location

        // *check stimulator for gate status*
            // otherwise get status_info default_status attribute

        // loop through each line in status_info

            // get data element with correct for_status attribute

            // for each of name, description, hovertext

                // save column attribute to array if present

                // check for hard-coded text
                    // if present, save text to gate object
                    // otherwise, go to stimulator

            // end loop when currentToken is EndElement and element name is "status_info"

        // end loop when currentToken is EndElement and element name is "gate"

        // append gate object pointer to a QList

    // end loop when currentToken is EndElement and element name is "gates"
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

void DescriptionFileReader::getStatusInfo() {

    qDebug() << "--\nStart reading status_info tag";

    currentToken = this->readNext();
    QString currentTag = this->name().toString();

    while(!(currentTag == "status_info" && currentToken == QXmlStreamReader::EndElement)) {
        if(currentTag == "data" && currentToken == QXmlStreamReader::StartElement) {
            qDebug() << "Found data tag";
        }

        // update token and tag
        currentToken = this->readNext();
        currentTag = this->name().toString();
    }

    qDebug() << "End reading status_info tag\n--";
}

// function to read a dimensions tag with a X and Y subtag
QPointF DescriptionFileReader::getLocationPoint() {

    qDebug() << "--\nStart reading location tag";

    // goes to next xml item
    currentToken = this->readNext();
    QString currentTag = this->name().toString();

    // store the x and y values
    int x = 0, y = 0;

    // loop until end of dimensions tag
    while(currentTag != "location" || currentToken != QXmlStreamReader::EndElement) {
        qDebug() << "Looping through location";

        // get width text and save as int
        if(currentTag == "X") {
            x = this->readElementText().toInt();
            qDebug() << "found x value" << x;
        }
        // get height text and save as int
        else if(currentTag == "Y") {
            y = this->readElementText().toInt();
            qDebug() << "found y value" << y;
        }

        // goes to next xml item with each loop
        currentToken = this->readNext();
        currentTag = this->name().toString();
    }

    qDebug() << "End reading location tag\n--";

    return QPointF(x,y);
}

// function to read a dimensions tag with a width and height subtag
QMap<QString, int> DescriptionFileReader::getDimensions() {

    qDebug() << "--\nStart reading dimensions tag";

    // to store the dimensions
    QMap<QString, int> dimension;

    // goes to next xml item
    currentToken = this->readNext();
    QString currentTag = this->name().toString();

    // loop until end of dimensions tag
    while(currentTag != "dimensions" || currentToken != QXmlStreamReader::EndElement) {
        qDebug() << "Looping through dimensions";

        // get width text and save as int
        if(currentTag == "width") {
            dimension["width"] = this->readElementText().toInt();
            qDebug() << "found width" << dimension["width"];
        }
        // get height text and save as int
        else if(currentTag == "height") {
            dimension["height"] = this->readElementText().toInt();
            qDebug() << "found height" << dimension["height"];
        }

        // goes to next xml item with each loop
        currentToken = this->readNext();
        currentTag = this->name().toString();
    }

    qDebug() << "End reading dimensions tag\n--";

    return dimension;
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


QList<Subdiagram *> DescriptionFileReader::getAllSubdiagrams() const
{
    return allSubdiagrams;
}

QList<Block *> DescriptionFileReader::getAllBlocks() const
{
    return allBlocks;
}

QList<Gate *> DescriptionFileReader::getAllGates() const
{
    return allGates;
}

QList<DiagramItem *> DescriptionFileReader::getAllItems() const
{
    return allItems;
}

