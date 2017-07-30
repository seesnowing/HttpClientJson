#-------------------------------------------------
#
# Project created by QtCreator 2017-06-23T16:25:02
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = testWidget3
TEMPLATE = app


RC_FILE += json_icon.rc

SOURCES += main.cpp\
        widget.cpp \
    App/NetUtils/httputils.cpp \
    App/Base/appbasewidget.cpp

HEADERS  += widget.h \
    App/NetUtils/httputils.h \
    App/Base/appbasewidget.h \
    App/NetUtils/HttpCallBack.h

FORMS    += widget.ui

RESOURCES += \
    res.qrc
