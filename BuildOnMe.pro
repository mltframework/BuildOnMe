#-------------------------------------------------
#
# Project created by QtCreator 2011-01-14T22:13:15
#
#-------------------------------------------------

QT       += core gui

TARGET = BuildOnMe
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

mac {
    QT += opengl
    SOURCES += glwidget.cpp
    HEADERS += glwidget.h
}
win32 {
    INCLUDEPATH += include/mlt++ include/mlt
    LIBS += -Llib -lmlt++ -lmlt
} else {
    CONFIG += link_pkgconfig
    PKGCONFIG += mlt++
}

RESOURCES += \
    resources.qrc
