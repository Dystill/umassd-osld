#include "descriptionfilereader.h"

/*
 * CONSTRUCTORS
 */

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


/*
 * INIT FUNCTION
 */

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
            qDebug() << ">> Found Token (not in function):" << tString;


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
                    diagramName = this->attributes().value("name").toString();  // get the value of the name attribute

                    qDebug()<< "Diagram Name:" << diagramName;
                }
                else if(currentTag == "meta") {         // meta tag
                    qDebug()<< "calling readMetaData function"<<endl;
                    this->readMetaData();
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


/*
 * UTILITIES
 */

// removes newlines and tabs from a string
QString DescriptionFileReader::cleanString(QString s) {
    return s.replace(QRegExp("\t|\n|\r"),"");
}

// converts a string to a bool
bool DescriptionFileReader::stringToBool(QString boolString)
{
    if(boolString == "true")
        return true;
    else
        return false;
}


/*
 * MAIN SECTION FUNCTIONS
 */

// read meta section of description file
void DescriptionFileReader::readMetaData()
{
    currentToken = this->readNext();
    QString currentTag = this->name().toString();
    QXmlStreamAttributes attributes;
    QString tString;

    qDebug() << "==================================START META==================================";
    while(currentTag != "meta" || currentToken != QXmlStreamReader::EndElement) {

        tString = (this->tokenString().replace("Characters", "String") +
                           (this->tokenString().contains("Element") ? " " : "") + this->name().toString());
        //qDebug() << ">> Found Token in meta:" << tString;

        // description
        if(currentTag == "description" && currentToken == QXmlStreamReader::StartElement) {
            this->diagramDescription = cleanString(this->readElementText());
        }
        // common_source
        else if(currentTag == "common_source" && currentToken == QXmlStreamReader::StartElement) {

            // keep reading elements until the end of the common_source tag
            while(currentTag != "common_source" || currentToken != QXmlStreamReader::EndElement) {
                // for a given source
                if(currentTag == "source" && currentToken == QXmlStreamReader::StartElement) {

                    CommonSource source;
                    QString sourceid;

                    // get the source's id
                    attributes = this->attributes();
                    if(attributes.hasAttribute("id")) {
                        sourceid = attributes.value("id").toString();
                    }

                    // keep reading elements until the end of this source tag
                    while(currentTag != "source" || currentToken != QXmlStreamReader::EndElement) {
                        // get the source name
                        if(currentTag == "name" && currentToken == QXmlStreamReader::StartElement) {
                            source.name = this->readElementText();
                        }
                        // get the source type
                        if(currentTag == "type" && currentToken == QXmlStreamReader::StartElement) {
                            source.type = this->readElementText();
                        }

                        // update token and tag to read next element in common_source
                        currentToken = this->readNext();
                        currentTag = this->name().toString();
                    }

                    // add this source to the sources QMap
                    sources[sourceid] = source;
                }

                // update token and tag to read next element in common_source
                currentToken = this->readNext();
                currentTag = this->name().toString();
            }
        }
        // status_types
        else if(currentTag == "status_types" && currentToken == QXmlStreamReader::StartElement) {

            // keep reading elements until the end of the status_types tag
            while(currentTag != "status_types" || currentToken != QXmlStreamReader::EndElement) {
                // for a given status
                if(currentTag == "status" && currentToken == QXmlStreamReader::StartElement) {

                    StatusTypes status;
                    QString statusid;

                    // get the status's id
                    attributes = this->attributes();
                    if(attributes.hasAttribute("id")) {
                        statusid = attributes.value("id").toString();
                    }

                    // keep reading elements until the end of this status tag
                    while(currentTag != "status" || currentToken != QXmlStreamReader::EndElement) {
                        // get the status color
                        if(currentTag == "color" && currentToken == QXmlStreamReader::StartElement) {
                            status.color = this->readElementText();
                        }
                        // get the status text color
                        else if(currentTag == "textcolor" && currentToken == QXmlStreamReader::StartElement) {
                            status.textColor = this->readElementText();
                        }
                        // get the status text color
                        else if(currentTag == "italics" && currentToken == QXmlStreamReader::StartElement) {
                            status.italics = this->stringToBool(this->readElementText());
                        }
                        // get the status text color
                        else if(currentTag == "bold" && currentToken == QXmlStreamReader::StartElement) {
                            status.bold = this->stringToBool(this->readElementText());
                        }
                        // get the status text color
                        else if(currentTag == "underline" && currentToken == QXmlStreamReader::StartElement) {
                            status.underline = this->stringToBool(this->readElementText());
                        }

                        // update token and tag to read next element in common_source
                        currentToken = this->readNext();
                        currentTag = this->name().toString();
                    }

                    // add this source to the sources QMap
                    statuses[statusid] = status;
                }

                // update token and tag to read next element in common_source
                currentToken = this->readNext();
                currentTag = this->name().toString();
            }
        }

        // update token and tag to read next element
        currentToken = this->readNext();
        currentTag = this->name().toString();
    }

    qDebug() << "Sources:" << sources.count() << sources.keys();
    qDebug() << "Statuses:" << statuses.count() << statuses.keys();

    qDebug() << "===================================END META===================================";

}

// read blocks section of description file
void DescriptionFileReader::readBlocks()
{
    currentToken = this->readNext();
    QString currentTag = this->name().toString();
    QXmlStreamAttributes attributes;

    qDebug() << "==================================START BLOCKS==================================";
    while(currentTag != "blocks" || currentToken != QXmlStreamReader::EndElement) {

        Block *block; // block pointer

        // get gate attributes
        if(currentTag == "block" && currentToken == QXmlStreamReader::StartElement) {
            qDebug() << "------ Start reading block ------";
            // get the block attributes
            attributes = this->attributes();

            // create a block object with the id
            if(attributes.hasAttribute("id")) {
                block = new Block(attributes.value("id").toString()); // create a new block
                qDebug() << "Found block id" << block->id();

            }
            // get and save the source id to the block
            if(attributes.hasAttribute("source")) {
                block->setSourceId(attributes.value("source").toString());
                qDebug() << "Found block source" << block->getSourceId();

                // CONTACT STIMULATOR HERE -> save and use ref_id if available
            }
        }
        // get dimensions data
        else if(currentTag == "dimensions" && currentToken == QXmlStreamReader::StartElement) {
            // call function to save the dimensions as a QMap
            QMap<QString, int> dimension = this->getDimensions();

            // set the block's width and height
            block->setItemSizing(dimension["width"],dimension["height"]);

            // print to make sure they were save properly
            qDebug() << "Dimensions Set!" << block->width() << block->height();
        }
        // get location data
        else if(currentTag == "location" && currentToken == QXmlStreamReader::StartElement) {
            QPointF location = this->getLocationPoint();    // call get location point function
            block->setLocation(location);                    // set the gate's location
            qDebug() << "Location Set!" << block->pos();     // print
        }
        // get status info
        else if(currentTag == "status_info" && currentToken == QXmlStreamReader::StartElement) {
            this->getStatusInfo();  // call get status info function
        }
        // at end of gate element
        else if(currentTag == "block" && currentToken == QXmlStreamReader::EndElement) {
            allBlocks.append(block);  // add gate pointer to allGates list in header file
            qDebug() << "------ Stored Block! ------";
        }

        // update token and tag to read next element
        currentToken = this->readNext();
        currentTag = this->name().toString();
    }

    // print amount of items in allGates list
    qDebug() << "Blocks stored:" << allBlocks.count();

    qDebug() << "===================================END BLOCKS===================================";
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

// read gates section of description file
void DescriptionFileReader::readGates()
{

    // update token and tag
    currentToken = this->readNext();
    QString currentTag = this->name().toString();
    QXmlStreamAttributes attributes;

    qDebug() << "==================================START GATES==================================";
    while(currentTag != "gates" || currentToken != QXmlStreamReader::EndElement) {

        Gate *gate; // gate pointer

        // get gate attributes
        if(currentTag == "gate" && currentToken == QXmlStreamReader::StartElement) {
            qDebug() << "------ Start reading gate ------";
            // get the gate attributes
            attributes = this->attributes();

            // create a gate object with the id
            if(attributes.hasAttribute("id")) {
                gate = new Gate(attributes.value("id").toString()); // create a new gate
                qDebug() << "Found gate id" << gate->id();

            }
            // get and save the gate type to the gate
            if(attributes.hasAttribute("type")) {
                gate->setGateType(attributes.value("type").toString());
                qDebug() << "Found gate type" << attributes.value("type").toString();
            }
            // get and save the source id to the gate
            if(attributes.hasAttribute("source")) {
                gate->setSourceId(attributes.value("source").toString());
                qDebug() << "Found gate source" << gate->getSourceId();

                // CONTACT STIMULATOR HERE -> save and use ref_id if available

                // gate->setXXX
            }
        }
        // get dimensions data
        else if(currentTag == "dimensions" && currentToken == QXmlStreamReader::StartElement) {
            // call function to save the dimensions as a QMap
            QMap<QString, int> dimension = this->getDimensions();

            // set the gate's width and height
            gate->setGateSizing(dimension["width"],dimension["height"]);

            // print to make sure they were save properly
            qDebug() << "Dimensions Set!" << gate->width() << gate->height();
        }
        // get location data
        else if(currentTag == "location" && currentToken == QXmlStreamReader::StartElement) {
            QPointF location = this->getLocationPoint();    // call get location point function
            gate->setLocation(location);                    // set the gate's location
            qDebug() << "Location Set!" << gate->pos();     // print
        }
        // get status info
        else if(currentTag == "status_info" && currentToken == QXmlStreamReader::StartElement) {
            this->getStatusInfo();  // call get status info function
        }
        // at end of gate element
        else if(currentTag == "gate" && currentToken == QXmlStreamReader::EndElement) {
            allGates.append(gate);  // add gate pointer to allGates list in header file
            qDebug() << "------ Stored gate! ------";
        }

        // update token and tag to read next element
        currentToken = this->readNext();
        currentTag = this->name().toString();
    }

    // print amount of items in allGates list
    qDebug() << "Gates stored:" << allGates.count();

    qDebug() << "===================================END GATES===================================";

}

// read subdiagrams section of description file
void DescriptionFileReader::readSubdiagrams()
{
    // loop through each line in the subdiagrams element
        // **be careful not to overuse "currentToken = this->readNext();"


    // update token and tag
    currentToken = this->readNext();
    QString currentTag = this->name().toString();
    QString tString;
    QXmlStreamAttributes attributes;

    qDebug() << "==================================START SUBDIAGRAMS==================================";

    while(currentTag != "subdiagrams" || currentToken != QXmlStreamReader::EndElement) {


        tString = (this->tokenString().replace("Characters", "String") +
                           (this->tokenString().contains("Element") ? " " : "") + this->name().toString());
        qDebug() << ">> Found Token:" << tString;

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

        // update token and tag to read next element
        currentToken = this->readNext();
        currentTag = this->name().toString();
    }
    // print amount of items in allSubdiagrams list
    qDebug() << "Subdiagrams stored:" << allSubdiagrams.count();

    qDebug() << "===================================END SUBDIAGRAMS===================================";
}



/*
 * INDIVIDUAL TAG FUNCTIONS
 */

// read status_info of a block or gate
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

// function to read a location tag with a X and Y subtag
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


/*
 * GETTERS
 */

QString DescriptionFileReader::getDiagramName() const
{
    return diagramName;
}

QString DescriptionFileReader::getDescription() const
{
    return diagramDescription;
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
