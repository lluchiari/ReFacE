#ifndef __MATCH_BLOCKMATCHING_H__
#define __MATCH_BLOCKMATCHING_H__

// Internal LIBs
#include <Utils/common.h>
#include <Utils/Settings.hh>

#include <GUI/SetMatchParamWindow.h>

#include <Modules/matching/Matching.hh>
#include <Modules/matching/settings/SettingsMatchingBM.h>

// OpenCV Libs
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

// QT Libs
#include <QApplication>

using namespace myMatching;

class myMatching::MatchBM : public Matching
{
public:
    MatchBM();
    ~MatchBM();

    int config(string);
    int run();

    void setScale(float aux){this->_matchSettings.scale = aux;}
    float getScale(){return this->_matchSettings.scale;}

    void setWindowSize(int aux){
        _matchSettings.windowSize = aux;
        bm->setBlockSize(aux);
    }
    int getWindowSize(){return this->_matchSettings.windowSize;}

    void setMaxDisparity(int aux){
        _matchSettings.maxDisparity = aux;
        bm->setNumDisparities(aux);
    }
    int getMaxDisparity(){return this->_matchSettings.maxDisparity;}

    void setPreFilterCarp(int aux){
        _matchSettings.preFilterCarp = aux;
        bm->setPreFilterCap(aux);
    }
    int getPreFilterCarp(){return this->_matchSettings.preFilterCarp;}

    void setUniquenessRatio(int aux){
        this->_matchSettings.uniquenessRatio = aux;
        bm->setUniquenessRatio(aux);
    }
    int getUniquenessRatio(){return this->_matchSettings.uniquenessRatio;}

    void setSpeckleWindowSize(int aux){
        this->_matchSettings.speckleWindowSize = aux;
        bm->setSpeckleWindowSize(aux);
    }
    int getSpeckleWindowSize(){return this->_matchSettings.speckleWindowSize;}

    void setSpeckleRange(int aux){
        this->_matchSettings.speckleRange = aux;
        bm->setSpeckleRange(aux);
    }
    int getSpeckleRange(){return this->_matchSettings.speckleRange;}

    void setDisp12MaxDiff(int aux){
        this->_matchSettings.disp12MaxDiff = aux;
        bm->setDisp12MaxDiff(aux);
    }
    int getDisp12MaxDiff(){return this->_matchSettings.disp12MaxDiff;}

    //Different
    void setTextureThreshold(int aux){
        this->_matchSettings.textureThreshold = aux;
        bm->setTextureThreshold(aux);
    }
    int getTextureThreshold(){return this->_matchSettings.textureThreshold;}


private:
    VideoCapture inputCaptureLeft;
    VideoCapture inputCaptureRight;

    vector<string> imageList;

    Ptr<StereoBM> bm;

    /* Calibration Parameters */
    const int _colorMode=CV_LOAD_IMAGE_GRAYSCALE;
    Mat _mapCam1[2];                                        //Right Cam
    Mat _mapCam2[2];                                        //Left Cam
    Mat _distCoeffs[2];
    Rect _validRoi[2];

    Mat disp, disp8;
    Mat _Q;

    SetMatchParamWindow *setParam;
    SettingsMatchingBM _matchSettings;

private:
    int _loadCameraParameters();

};

#endif //__MATCH_BLOCKMATCHING_H__
