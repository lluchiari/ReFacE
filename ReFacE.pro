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
        src/mainController/MainController.cpp \
        src/mainController/Settings/SettingsMainController.cpp \
#
        src/calibration/CalibSingle.cpp \
        src/calibration/settings/SettingsCalibSingle.cpp \
        src/calibration/CalibStereo.cpp \
        src/calibration/settings/SettingsCalibStereo.cpp \
#
        src/matching/MatchBM.cpp \
        src/matching/settings/SettingsMatchingBM.cpp \
        src/matching/MatchSGBM.cpp \
        src/matching/settings/SettingsMatchingSGBM.cpp \
#
        src/viewer/Viewer3D.cpp \
#
        src/3rdParty/TinyXML2/tinyxml2.cpp

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
        include/3rdParty/TinyXML2/*.h \
        include/3rdParty/wallaroo/*.h \
        include/3rdParty/wallaroo/cxx0x.h \
        include/3rdParty/wallaroo/part.h \
        include/3rdParty/wallaroo/detail/*


FORMS += \
        mainwindow.ui

DESTDIR = bin


LIBS += -L$(OPENCV_STATIC_DIR)/build/x64/vc15/lib/ -lopencv_world341
LIBS += -L$(OPENCV_STATIC_DIR)/build/x64/vc15/lib/ -lopencv_world341d


INCLUDEPATH += $(OPENCV_STATIC_DIR)/build/x64/vc15 $(OPENCV_STATIC_DIR)/build/include
INCLUDEPATH += $$PWD/include $$PWD/include/calibration $$PWD/include/utils
INCLUDEPATH += $$PWD/include/3rdParty/TinyXML2 $$PWD/include/3rdParty/wallaroo/
INCLUDEPATH += $$PWD/include/matching


DISTFILES += \
    $$PWD/config/* \
    $$PWD/images/CameraCalibration/*
