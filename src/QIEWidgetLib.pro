#-------------------------------------------------
#
# Project created by QtCreator 2017-04-04T00:01:09
#
#-------------------------------------------------

QT       += core axcontainer #gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QIEWidget
TEMPLATE = lib
CONFIG += release
CONFIG += warn_on exceptions_off hide_symbols
#CONFIG += staticlib
#CONFIG += dll static release

DEFINES += QIEWIDGETLIB_LIBRARY

SOURCES += qiewidget.cpp

HEADERS += qiewidget.h\
        qiewidgetlib_global.h \
    webaxwidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DEFINES += _XKEYCHECK_H

INCLUDEPATH += .
INCLUDEPATH += $$[QT_INSTALL_HEADERS]

LIBS += -L$$[QT_INSTALL_LIBS]
