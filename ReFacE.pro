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
        src/GUI/*.cpp \
#
        src/Modules/mainController/*.cpp \
        src/Modules/mainController/Settings/*.cpp \
#
        src/Modules/connection/*.cpp \
#
        src/Modules/calibration/*.cpp \
        src/Modules/calibration/settings/*.cpp \
#
        src/Modules/matching/*.cpp \
        src/Modules/matching/settings/*.cpp \
#
        src/Modules/viewer/*.cpp \
        src/Modules/viewer/settings/*.cpp \
#
        src/Modules/faceRec/*.cpp \
        src/Modules/faceRec/settings/*.cpp \
#
        src/Modules/faceDetection/*.cpp \
        src/Modules/faceDetection/settings/*.cpp \
#
        3rdParty/TinyXML2/*.cpp \
        3rdParty/TinyPly/*.cpp
#        3rdParty/OpenFace/*.cpp

HEADERS += \
        include/ReFacE.h \
#
        include/GUI/*.h \
#
        include/Modules/mainController/*.h \
        include/Modules/mainController/settings/*.h \
#
        include/Modules/connection/*.hh \
        include/Modules/connection/*.h \
#
        include/Modules/calibration/*.hh \
        include/Modules/calibration/*.h \
        include/Modules/calibration/settings/*.h \
#
        include/Modules/matching/*.hh \
        include/Modules/matching/*.h \
        include/Modules/matching/settings/*.h \
#
        include/Modules/viewer/*.hh \
        include/Modules/viewer/*.h \
        include/Modules/viewer/settings/*.h \
#
        include/Modules/faceRec/*.hh \
        include/Modules/faceRec/*.h \
        include/Modules/faceRec/settings/*.h \
#
        include/Modules/faceDetection/*.hh \
        include/Modules/faceDetection/*.h \
        include/Modules/faceDetection/settings/*.h \
#
        include/Utils/*.h \
        include/Utils/*.hh \
#
#       // 3rdParty libraries
        3rdParty/TinyXML2/*.h \
        3rdParty/TinyPly/*.h
#        3rdParty/OpenFace/*.h


FORMS += \
        forms/mainwindow.ui \
        forms/setmatchparamwindow.ui

DESTDIR = bin


LIBS += -L$(OPENCV_STATIC_DIR)/build/x64/vc15/lib/ -lopencv_world341
LIBS += -L$(OPENCV_STATIC_DIR)/build/x64/vc15/lib/ -lopencv_world341d
#LIBS += -L$(OPENCV_DIR)/build/install/x64/vc15/bin/ -lopencv_aruco341  -lopencv_ffmpeg341_64 -lopencv_bgsegm341 -lopencv_bioinspired341 -lopencv_calib3d341 -lopencv_ccalib341 -lopencv_core341 -lopencv_datasets341 -lopencv_dnn_objdetect341 -lopencv_dnn341 -lopencv_dpm341 -lopencv_face341 -lopencv_features2d341 -lopencv_ffmpeg341_64 -lopencv_flann341 -lopencv_fuzzy341 -lopencv_hdf341 -lopencv_hfs341 -lopencv_highgui341 -lopencv_img_hash341 -lopencv_imgcodecs341 -lopencv_imgproc341 -lopencv_line_descriptor341 -lopencv_ml341 -lopencv_objdetect341 -lopencv_optflow341 -lopencv_phase_unwrapping341 -lopencv_photo341 -lopencv_plot341 -lopencv_reg341 -lopencv_rgbd341 -lopencv_shape341 -lopencv_stereo341 -lopencv_stitching341 -lopencv_structured_light341 -lopencv_superres341 -lopencv_surface_matching341 -lopencv_text341 -lopencv_tracking341 -lopencv_video341 -lopencv_videoio341 -lopencv_videostab341 -lopencv_xfeatures2d341 -lopencv_ximgproc341 -lopencv_xobjdetect341 -lopencv_xphoto341
#LIBS += -L$(OPEN_FACE)/build/dlib_build/Debug/ -ldlib19.13.99_debug_32bit_msvc1913
#LIBS += -L$(BOOST)/lib64-msvc-14.1/


# OpenCV Libriries
INCLUDEPATH += $(OPENCV_STATIC_DIR)/build/x64/vc15
INCLUDEPATH += $(OPENCV_STATIC_DIR)/build/include

# OpenFace Libraries
#INCLUDEPATH += $(OPEN_FACE)/Lib/dlib-18_18

# Boost Libraties
#INCLUDEPATH += $$PWD/3rdParty/BoostProcess
#INCLUDEPATH += $(BOOST)

# Internal Project Libraries
INCLUDEPATH += $$PWD/include


DISTFILES += \
    $$PWD/config/* \
    $$PWD/images/CameraCalibration/*
