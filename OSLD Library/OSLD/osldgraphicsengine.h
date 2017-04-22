#ifndef OSLDGRAPHICSENGINE_H
#define OSLDGRAPHICSENGINE_H

#include <QtCore>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include "osld_global.h"
#include "subdiagram.h"
#include "rootitempathscene.h"
#include "descriptionfilereader.h"

struct OSLDDataObject {
    QString name = "Default Diagram Name";
    QString description = "Default Diagram Description";
    QList<Subdiagram *> subdiagrams;  // a list of all of the subdiagrams
    QList<Block *> blocks;       // a list of all of the blocks in the diagram
    QList<Gate *> gates;         // a list of all of the gates in the diagram
    QMap<QString, DiagramItem *> blocksAndGates;  // maps item ids to their respective objects
    QMap<QString, CommonSource> sourceMap;    // maps source ids to their name and type
    QMap<QString, StatusTypes> statusMap;    // maps status names to different colors
};

/*!
 * \struct StatusData
 * \brief Provides the necessary members to communicate status data between the
 * OSLD and an external system.
 * \note The OSLD must send the id and ref_id of the item it wishes to retrieve
 * an updated status for.
 * The external system must fill out the entire struct with the updated status
 * data.
 */
struct StatusData {
    QString id;
    QString ref_id;
    QString status;
    QString title;
    QString description;
    QString hovertext;
    QString titleQuery;
    QString descriptionQuery;
    QString hovertextQuery;
};

class OSLDSHARED_EXPORT OSLDGraphicsEngine : public QGraphicsScene
{
    Q_OBJECT

private:
    // environment variables
    int pollingRate = 1000;
    bool hideControls = false;
    QString rootViewOrientation = "v";
    bool hideBlockTitles = false;
    bool fullscreen = false;
    bool showGridBackground = false;

    QMap<QString, CommonSource> sources;    // maps source ids to their name and type
    QMap<QString, StatusTypes> statuses;    // maps status names to different colors

    Subdiagram *currentSubdiagram = 0;

    QString diagramName;
    QString diagramDescription;
    QList<Subdiagram *> allSubdiagrams;         // a list of all of the subdiagrams
    QList<Block *> allBlocks;                   // a list of all of the blocks in the diagram
    QList<Gate *> allGates;                     // a list of all of the gates in the diagram
    QMap<QString, DiagramItem *> allItems;      // maps item ids to their respective objects

    void retrieveStatusData();

    RootItemPathScene *rootScene;
    QList<Block *> rootPathList;    // holds the chain of root items to the current subdiagram

    QVarLengthArray<QLineF> backgroundGrid;
    QVarLengthArray<QPointF> backgroundDots;

    int gridUnitSize = 20;
    QColor backgroundColor = QColor("#fafafa");

    QGraphicsItem *pressedItem;
    QPointF pressPosition;

    // functions for creating gates
    Gate *createRandomGate(QPointF pos);

    // functions for creating blocks
    Block *createRandomBlock(QPointF pos);    // get information from the description file reader
    Block *buildBlock(QString id, QPointF position, QMap<QString, DiagramItemData> data);    // passes data into a block

    // stores any caught errors after reading a description file
    QXmlStreamReader::Error xmlError;
    QString xmlErrorString;

public:
    OSLDGraphicsEngine(QString filePath = "",
                       QWidget *parent = 0,
                       int pollingRate = 1000,
                       bool hideControls = 0,
                       QString rootViewOrientation = "v",
                       bool hideBlockTitles = 0,
                       bool fullscreen = 0,
                       bool showGrid = 0);

    QMap<QString, CommonSource> getSources() const { return sources; }
    void setSources(const QMap<QString, CommonSource> &value) { sources = value; }

    QMap<QString, StatusTypes> getStatuses() const { return statuses; }
    void setStatuses(const QMap<QString, StatusTypes> &value) { statuses = value; }

    QList<Subdiagram *> getAllSubdiagrams() const;

    void showGrid(bool show, QRectF area);

    void randomlyGenerateSubdiagrams(int numSubs);

    void drawSubdiagramItems(Subdiagram *sub);

    bool blockExists(QString id);
    Block *retrieveBlock(QString id);
    Subdiagram *createRandomSubdiagram(Block *root, int index);
    void hideSubdiagramItems(Subdiagram *sub);

    QList<Block *> getRootPathList() const;

    QMap<QString, DiagramItem *> getAllItems() const;

    void hideAllItemTitleText(bool b);

    RootItemPathScene *getRootScene() const;

    Subdiagram *getCurrentSubdiagram() const;

    void goToSubdiagram(Block *rootBlock);
    QString getDiagramName() const;
    void setDiagramName(const QString &value);

    QString getDiagramDescription() const;
    void setDiagramDescription(const QString &value);

    OSLDDataObject readDescriptionFile(QString filePath = "");
    void runGraphics(OSLDDataObject data);

    void readFileAndRunOSLD(QString filePath);

    QXmlStreamReader::Error getXmlError() const;

    QString getXmlErrorString() const;

    QList<Block *> getAllBlocks() const;

    QList<Gate *> getAllGates() const;

    // environment variable getter methods

    bool getHideControls() const;

    QString getRootViewOrientation() const;

    bool getHideBlockTitles() const;

    bool getFullscreen() const;

    bool getShowGridBackground() const;

    int getPollingRate() const;

public slots:
    void updateStatus(StatusData statusData);
    void alignRootScene(PathAlignment alignment, QGraphicsView *view = 0);
    void fitRootSceneToView();
    void resizeRootScenePadding(int padding);

signals:
    void subdiagramChanged();
    void statusDataQuery(StatusData statusData);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // OSLDGRAPHICSENGINE_H
