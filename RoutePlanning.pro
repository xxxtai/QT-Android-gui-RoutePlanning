#-------------------------------------------------
#
# Project created by QtCreator 2016-04-25T21:20:05
#
#-------------------------------------------------

QT       += core gui
QT += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RoutePlanning
TEMPLATE = app


SOURCES += main.cpp\
    imageButton.cpp \
    qDebug2Logcat.cpp \
    dialog.cpp \
    content.cpp \
    countlnglat.cpp \
    ipQuery.cpp \
    logingui.cpp \
    usergui.cpp \
    setgui.cpp \
    ui/clickhandler.cpp \
    ui/cscrollscreenview.cpp \
    ui/dialog.cpp \
    ui/imageButton.cpp \
    ui/logingui.cpp \
    ui/setgui.cpp \
    ui/ShowLabel.cpp \
    ui/usergui.cpp \
    count/content.cpp \
    count/countlnglat.cpp \
    count/ipQuery.cpp

HEADERS  += \
    imageButton.h \
    qDebug2Logcat.h \
    dialog.h \
    content.h \
    countlnglat.h \
    ipQuery.h \
    logingui.h \
    usergui.h \
    setgui.h \
    ui/clickhandler.h \
    ui/cscrollscreenview.h \
    ui/dialog.h \
    ui/imageButton.h \
    ui/logingui.h \
    ui/setgui.h \
    ui/ShowLabel.h \
    ui/usergui.h \
    count/content.h \
    count/countlnglat.h \
    count/ipQuery.h

CONFIG += mobility
MOBILITY = 

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml

RESOURCES += \
ListWidgetDemo.qrc

