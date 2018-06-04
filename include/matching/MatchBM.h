#ifndef __MATCH_BLOCKMATCHING_H__
#define __MATCH_BLOCKMATCHING_H__

// Internal LIBs
#include <matching/Matching.hh>
#include <matching/settings/SettingsMatchingBM.h>
#include <utils/common.h>
#include <utils/Settings.hh>

// OpenCV Libs
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

// QT Libs
#include <QApplication>

using namespace myMatching;

class myMatching::MatchBM : public Matching, public QObject
{
public:
    MatchBM();
    ~MatchBM();

    int config(string);
    int run();

    void setScale(float aux){this->_matchSettings.scale = aux;}
    float getScale(){return this->_matchSettings.scale;}

    void setWindowSize(int aux){this->_matchSettings.windowSize = aux;}
    int getWindowSize(){return this->_matchSettings.windowSize;}

    void setMaxDisparity(int aux){this->_matchSettings.maxDisparity = aux;}
    int getMaxDisparity(){return this->_matchSettings.maxDisparity;}

    void setPreFilterCarp(int aux){this->_matchSettings.preFilterCarp = aux;}
    int getPreFilterCarp(){return this->_matchSettings.preFilterCarp;}

    void setUniquenessRatio(int aux){this->_matchSettings.uniquenessRatio = aux;}
    int getUniquenessRatio(){return this->_matchSettings.uniquenessRatio;}

    void setSpeckleWindowSize(int aux){this->_matchSettings.speckleWindowSize = aux;}
    int getSpeckleWindowSize(){return this->_matchSettings.speckleWindowSize;}

    void setSpeckleRange(int aux){this->_matchSettings.speckleRange = aux;}
    int getSpeckleRange(){return this->_matchSettings.speckleRange;}

    void setDisp12MaxDiff(int aux){this->_matchSettings.disp12MaxDiff = aux;}
    int getDisp12MaxDiff(){return this->_matchSettings.disp12MaxDiff;}

    //Different
    void setTextureThreshold(int aux){this->_matchSettings.textureThreshold = aux;}
    int getTextureThreshold(){return this->_matchSettings.textureThreshold;}

private:
    VideoCapture inputCaptureLeft;
    VideoCapture inputCaptureRight;

    vector<string> imageList;

    Ptr<StereoBM> bm;

    /* Calibration Parameters */
    const int _colorMode=0;
    Mat _mapCam1[2];
    Mat _mapCam2[2];
    Mat _distCoeffs[2];
    Rect _validRoi[2];

    Mat disp, disp8;

//    Mat _R, _T, _E, _F;                                  // All the main matrix that describes the camera and the image system //

    /* Rectified coeficients for stereo matching */
//    Mat _R1;                                             // Output 3x3 rectification transform (rotation matrix) for the first camera.
//    Mat _R2;                                             // Output 3x3 rectification transform (rotation matrix) for the second camera.
//    Mat _P1;                                             // Output 3x4 projection matrix in the new (rectified) coordinate systems for the first camera.
//    Mat _P2;                                             // Output 3x4 projection matrix in the new (rectified) coordinate systems for the second camera.
//    Mat _Q;

    SetMatchParamWindow *setParam;

    SettingsMatchingBM _matchSettings;

private:
    int _loadCameraParameters();

};

#endif //__MATCH_BLOCKMATCHING_H__
