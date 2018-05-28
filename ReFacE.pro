#-------------------------------------------------
#
# Project created by QtCreator 2018-04-12T00:21:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReFacE
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        src/main.cpp \
#
        src/mainController/*.cpp \
        src/mainController/Settings/*.cpp \
#
        src/calibration/*.cpp \
        src/calibration/settings/*.cpp \
#
        src/matching/*.cpp \
        src/matching/settings/*.cpp \
#
        src/viewer/*.cpp \
#
        src/3rdParty/TinyXML2/*.cpp

HEADERS += \
        include/ReFacE.h \
#
        include/mainController/*.h \
        include/mainController/Settings/*.h \
#
        include/calibration/*.hh \
        include/calibration/*.h \
        include/calibration/settings/*.h \
#
        include/matching/*.hh \
        include/matching/*.h \
        include/matching/settings/*.h \
#
        include/viewer/*.hh \
#
        include/utils/*.h \
        include/utils/*.hh \
#
#       // 3rdParty libraries
        include/3rdParty/TinyXML2/*.h

FORMS += \
        mainwindow.ui

DESTDIR = bin


LIBS += -L$(OPENCV_STATIC_DIR)/build/x64/vc15/lib/ -lopencv_world341
LIBS += -L$(OPENCV_STATIC_DIR)/build/x64/vc15/lib/ -lopencv_world341d


INCLUDEPATH += $(OPENCV_STATIC_DIR)/build/x64/vc15
INCLUDEPATH += $(OPENCV_STATIC_DIR)/build/include
INCLUDEPATH += $$PWD/include


DISTFILES += \
    $$PWD/config/* \
    $$PWD/images/CameraCalibration/*
