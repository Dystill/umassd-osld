#include "descriptionfilereader.h"

/*
 * CONSTRUCTORS
 */

DescriptionFileReader::DescriptionFileReader(QWidget *parent)
{
    // qDebug() << "Asking user for description file location";
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

    // qDebug() << ">> QXmlStreamReader";
    // qDebug() << "Reading file:" << filepath;
    QFile xmlFile(filepath);

    if(xmlFile.open(QIODevice::ReadOnly)) {
        // qDebug() << "File Opened";

        // QXmlInputSource source (&xmlFile);
        // QXmlStreamReader xmlReader(xmlFile);

        // std::string inBuff;

        // qDebug() << "Setting device to XML file";
        this->setDevice(&xmlFile);

        // qDebug() << "Begin reading";
        while(!this->atEnd()) {

            // get the type of xml element currently being read
            currentToken = this->readNext();


            // qDebug string to print current token type
            // prints every line read in the xml file

            QString tString = (this->tokenString().replace("Characters", "String") +
                               (this->tokenString().contains("Element") ? " " : "") + this->name().toString());
            // qDebug() << ">> Found Token (not in function):" << tString;


            // start of document
            if(currentToken == QXmlStreamReader::StartDocument){
                // qDebug() << "Start of document";
                continue;
            }

            // start of element
            if(currentToken == QXmlStreamReader::StartElement) {

                // get the name of the current tag
                QString currentTag = this->name().toString();
                // qDebug() << "Reading in element:" << currentTag;

                // diagram tag
                if(currentTag == "diagram") {           // diagram tag
                    // qDebug() << "Setting diagram name";
                    diagramName = this->attributes().value("name").toString();  // get the value of the name attribute

                    // qDebug() << "Diagram Name:" << diagramName;
                }
                else if(currentTag == "meta") {         // meta tag
                    // qDebug() << "calling readMetaData function"<<endl;
                    this->readMetaData();
                }
                else if(currentTag == "blocks") {       // blocks tag
                    // qDebug() << "do blocks stuff";
                    this->readBlocks();
                }
                else if(currentTag == "gates") {        // gates tag
                    // qDebug() << "do gates stuff";
                    this->readGates();
                }
                else if(currentTag == "subdiagrams") { // status types tag
                    // qDebug() << "do subdiagram stuff";
                    this->readSubdiagrams();
                }
            }
        }
        // qDebug() << "End reading";
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

// find an item in allItems list by id
DiagramItem *DescriptionFileReader::findDiagramItemById(QString itemid) {
    // go through all items in allItems
    for(int i = 0; i < allItems.count(); i++) {
        if(allItems.at(i)->id().compare(itemid) == 0) { // if item was found
            // qDebug() << allItems.at(i)->id() << "equals" << itemid;
            return allItems.at(i);
        }
    }

    return 0;
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

    // qDebug() << "==================================START META==================================";
    while(currentTag != "meta" || currentToken != QXmlStreamReader::EndElement) {

        tString = (this->tokenString().replace("Characters", "String") +
                           (this->tokenString().contains("Element") ? " " : "") + this->name().toString());
        // qDebug() << ">> Found Token in meta:" << tString;

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

    // qDebug() << "Sources:" << sources.count() << sources.keys();
    // qDebug() << "Statuses:" << statuses.count() << statuses.keys();

    // qDebug() << "===================================END META===================================";

}

// read blocks section of description file
void DescriptionFileReader::readBlocks()
{
    currentToken = this->readNext();
    QString currentTag = this->name().toString();
    QXmlStreamAttributes attributes;
    Block *block = 0; // block pointer

    // qDebug() << "==================================START BLOCKS==================================";
    while(currentTag != "blocks" || currentToken != QXmlStreamReader::EndElement) {

        // get block attributes
        if(currentTag == "block" && currentToken == QXmlStreamReader::StartElement) {
            // qDebug() << "------ Start reading block ------";
            // get the block attributes
            attributes = this->attributes();

            // create a block object with the id
            if(attributes.hasAttribute("id")) {
                block = new Block(attributes.value("id").toString()); // create a new block
                // qDebug() << "Found block id" << block->id();

            }
            // get and save the source id to the block
            if(attributes.hasAttribute("source")) {
                block->setSourceId(attributes.value("source").toString());
                // qDebug() << "Found block source" << block->getSourceId();

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
            // qDebug() << "Dimensions Set!" << block->width() << block->height();
        }
        // get location data
        else if(currentTag == "location" && currentToken == QXmlStreamReader::StartElement) {
            QPointF location = this->getLocationPoint("location");    // call get location point function
            block->setLocation(location);                    // set the block's location
            // qDebug() << "Location Set!" << block->pos();     // print
        }
        // get status info
        else if(currentTag == "status_info" && currentToken == QXmlStreamReader::StartElement) {
            // get the default status value
            QString defaultStatus;
            if(this->attributes().hasAttribute("default_status")) {
                defaultStatus = this->attributes().value("default_status").toString();
            }
            block->setStatusInfoDataList(this->getStatusInfo());
            block->setStatus(defaultStatus, statuses);
            // this->getStatusInfo(block);
        }
        // at end of block element
        else if(currentTag == "block" && currentToken == QXmlStreamReader::EndElement) {
            allBlocks.append(block);  // add block pointer to allGates list in header file
            allItems.append(block);
            // qDebug() << "------ Stored Block! ------";
        }

        // update token and tag to read next element
        currentToken = this->readNext();
        currentTag = this->name().toString();
    }

    // print amount of items in allBlocks list
    // qDebug() << "Blocks stored:" << allBlocks.count();

    // qDebug() << "===================================END BLOCKS===================================";

}

// read gates section of description file
void DescriptionFileReader::readGates()
{

    // update token and tag
    currentToken = this->readNext();
    QString currentTag = this->name().toString();
    QXmlStreamAttributes attributes;
    Gate *gate = 0; // gate pointer

    // qDebug() << "==================================START GATES==================================";
    while(currentTag != "gates" || currentToken != QXmlStreamReader::EndElement) {

        // get gate attributes
        if(currentTag == "gate" && currentToken == QXmlStreamReader::StartElement) {
            // qDebug() << "------ Start reading gate ------";
            // get the gate attributes
            attributes = this->attributes();

            // create a gate object with the id
            if(attributes.hasAttribute("id")) {
                gate = new Gate(attributes.value("id").toString()); // create a new gate
                // qDebug() << "Found gate id" << gate->id();

            }
            // get and save the gate type to the gate
            if(attributes.hasAttribute("type")) {
                gate->setGateType(attributes.value("type").toString());
                // qDebug() << "Found gate type" << attributes.value("type").toString();
            }
            // get and save the source id to the gate
            if(attributes.hasAttribute("source")) {
                gate->setSourceId(attributes.value("source").toString());
                // qDebug() << "Found gate source" << gate->getSourceId();

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
            // qDebug() << "Dimensions Set!" << gate->width() << gate->height();
        }
        // get location data
        else if(currentTag == "location" && currentToken == QXmlStreamReader::StartElement) {
            QPointF location = this->getLocationPoint("location");    // call get location point function
            gate->setLocation(location);                    // set the gate's location
            // qDebug() << "Location Set!" << gate->pos();     // print
        }
        // get status info
        else if(currentTag == "status_info" && currentToken == QXmlStreamReader::StartElement) {
            QString defaultStatus;
            if(this->attributes().hasAttribute("default_status")) {
                defaultStatus = this->attributes().value("default_status").toString();
            }
            gate->setStatusInfoDataList(this->getStatusInfo());
            gate->setStatus(defaultStatus, statuses);
        }
        // at end of gate element
        else if(currentTag == "gate" && currentToken == QXmlStreamReader::EndElement) {
            allGates.append(gate);  // add gate pointer to allGates list in header file
            allItems.append(gate);
            // qDebug() << "------ Stored gate! ------";
        }

        // update token and tag to read next element
        currentToken = this->readNext();
        currentTag = this->name().toString();
    }

    // print amount of items in allGates list
    // qDebug() << "Gates stored:" << allGates.count();

    // qDebug() << "===================================END GATES===================================";

}

// read subdiagrams section of description file
void DescriptionFileReader::readSubdiagrams()
{
    // loop through each line in the subdiagrams element
        // **be careful not to overuse "currentToken = this->readNext();"

    // update token and tag
    currentToken = this->readNext();
    QString currentTag = this->name().toString();
    Subdiagram *subdiagram = 0;
    Block *root = 0;

    // qDebug() << "==================================START SUBDIAGRAMS==================================";

    // go through all elements in subdiagrams tag
    while(currentTag != "subdiagrams" || currentToken != QXmlStreamReader::EndElement) {

        // Subdiagram(Block *root, QString name, QString description);

        // create a subdiagram object pointer
        bool isMainDiagram = false;

        // get subdiagram attributes
        if(currentTag == "subdiagram" && currentToken == QXmlStreamReader::StartElement) {
            // qDebug() << "------ Start reading subdiagram ------";

            // qDebug() << "Reading attributes";

            if(attributes().hasAttribute("root_item_id")) {
                // qDebug() << "Reading root id";
                QString rootId(attributes().value("root_item_id").toString());
                for(int i = 0; i < allBlocks.count(); i++) {
                    if(allBlocks.at(i)->id().compare(rootId) == 0) {
                        // qDebug() << allBlocks.at(i)->id() << "equals" << rootId;
                        root = allBlocks.at(i);
                    }
                }
            }
            if(attributes().hasAttribute("main_diagram")) {
                // qDebug() << "Reading main diagram";
                isMainDiagram = stringToBool(attributes().value("main_diagram").toString());
            }

            // create a new subdiagram
            subdiagram = new Subdiagram(root);
        }
        // get subdiagram data
        else if(currentTag == "subdiagram_data" && currentToken == QXmlStreamReader::StartElement) {
            // qDebug() << "Reading subdiagram data";
            while(currentTag != "subdiagram_data" || currentToken != QXmlStreamReader::EndElement) {

                if(currentTag == "name" && currentToken == QXmlStreamReader::StartElement) {
                    QString name = this->readElementText();
                    subdiagram->setName((name.isEmpty() ? "No Subdiagram Name" : name));
                    // qDebug() << "Subdiagram name" << subdiagram->getName();
                }
                else if(currentTag == "description" && currentToken == QXmlStreamReader::StartElement) {
                    QString description = this->readElementText();
                    subdiagram->setDescription((description.isEmpty() ? "No Subdiagram Description Available" : description));
                    // qDebug() << "Subdiagram description" << subdiagram->getDescription();
                }
                // get root item location data
                else if(currentTag == "root_item_location" && currentToken == QXmlStreamReader::StartElement) {
                    QPointF location = this->getLocationPoint("root_item_location");    // call get location point function
                    root->setRootLocation(location);                    // set the root's location
                    // qDebug() << "Root item Location Set!" << subdiagram->getRoot()->getRootLocation();     // print
                }

                // update token and tag to read next element
                currentToken = this->readNext();
                currentTag = this->name().toString();
            }
        }
        else if(currentTag == "connections" && currentToken == QXmlStreamReader::StartElement) {
            // qDebug() << "-- Start connections";
            while(currentTag != "connections" || currentToken != QXmlStreamReader::EndElement) {

                // process a connection
                if(currentTag == "connect" && currentToken == QXmlStreamReader::StartElement) {
                    // get the ids for the input and output
                    QMap<QString, QString> inputOutput = this->makeConnectMap();

                    // get the diagramitems from the diagram item list
                    DiagramItem *input = findDiagramItemById(inputOutput["input"]);
                    DiagramItem *output = findDiagramItemById(inputOutput["output"]);

                    // add output and input as input items for the subdiagram
                    subdiagram->addInputItem(input);
                    subdiagram->addInputItem(output);

                    // connect the two items
                    subdiagram->connectItems(input, output);
                    // qDebug() << "connected items" << inputOutput["input"] << inputOutput["output"];
                }

                // update token and tag to read next element
                currentToken = this->readNext();
                currentTag = this->name().toString();
            }
            // qDebug() << "-- End connections";
        }
        else if(currentTag == "subdiagram" && currentToken == QXmlStreamReader::EndElement) {

            // add diagram to front if it is the main diagram
            if(isMainDiagram)
                allSubdiagrams.prepend(subdiagram);
            else
                allSubdiagrams.append(subdiagram);

            // qDebug() << "------ finished subdiagram! ------";
        }

        // update token and tag to read next element
        currentToken = this->readNext();
        currentTag = this->name().toString();
    }
    // print amount of items in allSubdiagrams list
    // qDebug() << "Subdiagrams stored:" << allSubdiagrams.count();

    // qDebug() << "===================================END SUBDIAGRAMS===================================";
}



/*
 * INDIVIDUAL TAG FUNCTIONS
 */

// read connect tag in a subdiagram's connections tag
// return a QMap with input and output item id
QMap<QString, QString> DescriptionFileReader::makeConnectMap()
{
    QMap<QString, QString> inputOutput;

    currentToken = this->readNext();
    QString currentTag = this->name().toString();

    while(currentTag != "connect" || currentToken != QXmlStreamReader::EndElement) {

        if(currentTag == "input" && currentToken == QXmlStreamReader::StartElement) {
            inputOutput["input"] = this->readElementText();
        }
        else if(currentTag == "output" && currentToken == QXmlStreamReader::StartElement) {
            inputOutput["output"] = this->readElementText();
        }

        // update token and tag to read next element
        currentToken = this->readNext();
        currentTag = this->name().toString();
    }

    return inputOutput;
}

// read status_info of a block or gate
QMap<QString, DiagramItemData> DescriptionFileReader::getStatusInfo()
{
    // qDebug() << "--\nStart reading status_info tag";

    // go to next element
    currentToken = this->readNext();
    QString currentTag = this->name().toString();

    // to store item info to a list compatible to what's in diagramitem objects
    QMap<QString, DiagramItemData> itemDataMap;

    // read until end of status_info element
    while(!(currentTag == "status_info" && currentToken == QXmlStreamReader::EndElement)) {
        // for each data tag
        if(currentTag == "data" && currentToken == QXmlStreamReader::StartElement) {
            // qDebug() << "Found data tag";

            QString currentForStatusID; // holds the key for the QMap
            DiagramItemData data;       // holds the value for the QMap

            // get the for_status attribute
            if(this->attributes().hasAttribute("for_status")) {
                // qDebug() << "getting for_status" << this->attributes().value("for_status").toString();
                currentForStatusID = this->attributes().value("for_status").toString();
            }

            // get each data element
            while(!(currentTag == "data" && currentToken == QXmlStreamReader::EndElement)) {
                // get the name/title
                if(currentTag == "name" && currentToken == QXmlStreamReader::StartElement) {
                    if(this->attributes().isEmpty()) {
                        data.title = this->readElementText();
                    }
                    else {
                        // contact stimulator
                        data.title = this->readElementText();
                    }
                }
                // get the description
                if(currentTag == "description" && currentToken == QXmlStreamReader::StartElement) {
                    if(this->attributes().isEmpty()) {
                        data.description = this->readElementText();
                    }
                    else {
                        // contact stimulator
                    }
                }
                // get the hovertext
                if(currentTag == "hovertext" && currentToken == QXmlStreamReader::StartElement) {
                    if(this->attributes().isEmpty()) {
                        data.hovertext = this->readElementText();
                    }
                    else {
                        // contact stimulator
                    }
                }


                // update token and tag
                currentToken = this->readNext();
                currentTag = this->name().toString();
            }

            // qDebug() << "Data for" << currentForStatusID << data.title << data.description << data.hovertext;

            // add the data to the item map
            itemDataMap[currentForStatusID] = data;
        }

        // update token and tag
        currentToken = this->readNext();
        currentTag = this->name().toString();
    }

    // qDebug() << "Number of data items:" << itemDataMap.count() << itemDataMap.keys();

    // qDebug() << "End reading status_info tag\n--";

    return itemDataMap;
}


void DescriptionFileReader::getStatusInfo(Block *b)
{
    DiagramItemData blockData;
    QXmlStreamAttributes attributes;
    QString currentTag;

    attributes = this->attributes();
    while(currentTag != "status_info" || currentToken != QXmlStreamReader::EndElement) {
        // for a given source
        attributes = this->attributes();
        if(attributes.hasAttribute("default_status"))
        {
            blockData.setDefaultStatus(attributes.value("default_status").toString());
            // qDebug() << "Block Default Status: "<< blockData.defaultStatus<<endl;
        }

        if(attributes.hasAttribute("for_status"))
        {
           blockData.setForStatus(attributes.value("for_status").toString());
           // qDebug() << "Block For Status: "<< blockData.forStatus<<endl;
        }

        if (currentTag == "name" && attributes.value("column").toString() == "name" && currentToken == QXmlStreamReader::StartElement)
        {
            blockData.setTitle((cleanString(this->readElementText())));
            // qDebug() << "Block Title: "<< blockData.title<<endl;

        }

        if (currentTag == "description" && attributes.value("column").toString() == "desc" && currentToken == QXmlStreamReader::StartElement)
        {
            blockData.setDescription((cleanString(this->readElementText())));
            // qDebug() << "Block Description: "<< blockData.description<<endl;

        }

        if (currentTag == "hovertext" && attributes.value("column").toString() == "hover" && currentToken == QXmlStreamReader::StartElement)
        {
            blockData.setHovertext((cleanString(this->readElementText())));
            // qDebug() << "Block Hovertext: "<< blockData.hovertext<<endl;

        }

        currentToken = this->readNext();
        currentTag = this->name().toString();
    }

    //blockStatuses.insert(b,blockData);
    //blockStatuses[b] = this->readElementText().toInt();

}

// function to read a location tag with a X and Y subtag
QPointF DescriptionFileReader::getLocationPoint(QString tagName) {

    // qDebug() << "--\nStart reading location tag";

    // goes to next xml item
    currentToken = this->readNext();
    QString currentTag = this->name().toString();

    // store the x and y values
    int x = 0, y = 0;

    // loop until end of dimensions tag
    while(currentTag != tagName || currentToken != QXmlStreamReader::EndElement) {
        // qDebug() << "Looping through location";

        // get width text and save as int
        if(currentTag == "X") {
            x = this->readElementText().toInt();
            // qDebug() << "found x value" << x;
        }
        // get height text and save as int
        else if(currentTag == "Y") {
            y = this->readElementText().toInt();
            // qDebug() << "found y value" << y;
        }

        // goes to next xml item with each loop
        currentToken = this->readNext();
        currentTag = this->name().toString();
    }

    // qDebug() << "End reading location tag\n--";

    return QPointF(x,y);
}

// function to read a dimensions tag with a width and height subtag
QMap<QString, CommonSource> DescriptionFileReader::getSources() const
{
    return sources;
}

QMap<QString, StatusTypes> DescriptionFileReader::getStatuses() const
{
    return statuses;
}

QMap<QString, int> DescriptionFileReader::getDimensions() {

    // qDebug() << "--\nStart reading dimensions tag";

    // to store the dimensions
    QMap<QString, int> dimension;

    // goes to next xml item
    currentToken = this->readNext();
    QString currentTag = this->name().toString();

    // loop until end of dimensions tag
    while(currentTag != "dimensions" || currentToken != QXmlStreamReader::EndElement) {
        // qDebug() << "Looping through dimensions";

        // get width text and save as int
        if(currentTag == "width") {
            dimension["width"] = this->readElementText().toInt();
            // qDebug() << "found width" << dimension["width"];
        }
        // get height text and save as int
        else if(currentTag == "height") {
            dimension["height"] = this->readElementText().toInt();
            // qDebug() << "found height" << dimension["height"];
        }

        // goes to next xml item with each loop
        currentToken = this->readNext();
        currentTag = this->name().toString();
    }

    // qDebug() << "End reading dimensions tag\n--";

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
