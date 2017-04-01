#-------------------------------------------------
#
# Project created by QtCreator 2017-03-31T20:08:14
#
#-------------------------------------------------

QT       += widgets

TARGET = OSLDGraphicsEngine
TEMPLATE = lib
CONFIG += plugin

DEFINES += OSLDGRAPHICSENGINE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += osldgraphicsengine.cpp \
    block.cpp \
    connector.cpp \
    descriptionfilereader.cpp \
    diagramitem.cpp \
    gate.cpp \
    rootitempathscene.cpp \
    subdiagram.cpp

HEADERS += osldgraphicsengine.h\
        osldgraphicsengine_global.h \
    block.h \
    connector.h \
    descriptionfilereader.h \
    diagramitem.h \
    gate.h \
    rootitempathscene.h \
    subdiagram.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    OSLDGraphicsEngine.pro.user
