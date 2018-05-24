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
        src/MainWindow.cpp \
        src/calibration/Calibration.cpp \
        src/calibration/settings/SettingsStereo.cpp \
        src/calibration/settings/SettingsSingle.cpp \
        src/calibration/StereoCalib.cpp \
        src/matching/settings/SettingsMatchingStereo.cpp \
        src/matching/BlockMatching.cpp \
        src/matching/SGBM.cpp \
        src/viewer/Viewer3D.cpp \
        src/utils/InputParser.cpp \
        src/3rdParty/TinyXML2/tinyxml2.cpp

HEADERS += \
        include/MainWindow.h \
        include/ReFacE.h \
        include/calibration/settings/SettingsStereo.h \
        include/calibration/settings/SettingsSingle.h \
        include/calibration/StereoCalib.h \
        include/matching/settings/SettingsMatchingStereo.h \
        include/calibration/Calibration.h \
        include/matching/StereoMatching.hh \
        include/matching/BlockMatching.h \
        include/matching/SGBM.h \
        include/viewer/Viewer3D.hh \
        include/utils/common.h \
        include/utils/Settings.hh \
        include/utils/InputParser.hh \
        include/3rdParty/TinyXML2/tinyxml2.h


FORMS += \
        mainwindow.ui

DESTDIR = bin


LIBS += -L$(OPENCV_STATIC_DIR)/build/x64/vc15/lib/ -lopencv_world341
LIBS += -L$(OPENCV_STATIC_DIR)/build/x64/vc15/lib/ -lopencv_world341d


INCLUDEPATH += $(OPENCV_STATIC_DIR)/build/x64/vc15 $(OPENCV_STATIC_DIR)/build/include
INCLUDEPATH += $$PWD/include $$PWD/include/calibration $$PWD/include/utils $$PWD/include/3rdParty/TinyXML2
INCLUDEPATH += $$PWD/include/matching


DISTFILES += \
    $$PWD/config/* \
    $$PWD/images/CameraCalibration/*
