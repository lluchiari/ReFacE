#ifndef __MATCH_SGBM_H__
#define __MATCH_SGBM_H__

// Internal LIBs
#include <utils/common.h>
#include <utils/consts.h>
#include <matching/Matching.hh>
#include <matching/settings/SettingsMatchingSGBM.h>

// OpenCV Libs
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

using namespace myMatching;

class myMatching::MatchSGBM : public Matching
{
public:
    MatchSGBM();
    ~MatchSGBM() override;

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
    void setAlgorithm(string aux){this->_matchSettings.algorithm = aux;}
    string getAlgorithm(){return this->_matchSettings.algorithm;}


private:
    VideoCapture inputCaptureLeft;
    VideoCapture inputCaptureRight;

    vector<string> imageList;

    Ptr<StereoSGBM> sgbm;

    /* Calibration Parameters */
    const int _colorMode=0;
    Mat _mapCam1[2];
    Mat _mapCam2[2];
    Mat _distCoeffs[2];
    Rect _validRoi[2];

    Mat disp, disp8;

    SettingsMatchingSGBM _matchSettings;
private:
    int _loadCameraParameters();
};


#endif //__MATCH_SGBM_H__
