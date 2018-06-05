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

    void setWindowSize(int aux){
        this->_matchSettings.windowSize = aux;
        sgbm->setBlockSize(aux);
    }
    int getWindowSize(){return this->_matchSettings.windowSize;}

    void setMaxDisparity(int aux){
        this->_matchSettings.maxDisparity = aux;
        sgbm->setNumDisparities(aux);
    }
    int getMaxDisparity(){return this->_matchSettings.maxDisparity;}

    void setPreFilterCarp(int aux){
        this->_matchSettings.preFilterCarp = aux;
        sgbm->setPreFilterCap(aux);
    }
    int getPreFilterCarp(){return this->_matchSettings.preFilterCarp;}

    void setUniquenessRatio(int aux){
        this->_matchSettings.uniquenessRatio = aux;
        sgbm->setUniquenessRatio(aux);
    }
    int getUniquenessRatio(){return this->_matchSettings.uniquenessRatio;}

    void setSpeckleWindowSize(int aux){
        this->_matchSettings.speckleWindowSize = aux;
        sgbm->setSpeckleWindowSize(aux);
    }
    int getSpeckleWindowSize(){return this->_matchSettings.speckleWindowSize;}

    void setSpeckleRange(int aux){
        this->_matchSettings.speckleRange = aux;
        sgbm->setSpeckleRange(aux);
    }
    int getSpeckleRange(){return this->_matchSettings.speckleRange;}

    void setDisp12MaxDiff(int aux){
        this->_matchSettings.disp12MaxDiff = aux;
        sgbm->setDisp12MaxDiff(aux);
    }
    int getDisp12MaxDiff(){return this->_matchSettings.disp12MaxDiff;}

    //Different
    void setAlgorithm(string aux){
        this->_matchSettings.algorithm = aux;
        if(!aux.compare("STEREO_HH"))
            sgbm->setMode(StereoSGBM::MODE_HH);
        else if(!aux.compare("STEREO_SGBM"))
            sgbm->setMode(StereoSGBM::MODE_SGBM);
        else if(!aux.compare("STEREO_3WAY"))
            sgbm->setMode(StereoSGBM::MODE_SGBM_3WAY);
    }
    string getAlgorithm(){return this->_matchSettings.algorithm;}


private:
    VideoCapture inputCaptureLeft;
    VideoCapture inputCaptureRight;

    vector<string> imageList;

    Ptr<StereoSGBM> sgbm;

    /* Calibration Parameters */
    const int _colorMode=CV_LOAD_IMAGE_GRAYSCALE;
    Mat _mapCam1[2];
    Mat _mapCam2[2];
    Mat _distCoeffs[2];
    Rect _validRoi[2];

    Mat disp, disp8;

//    SetMatchParamWindow *setParam;
    SettingsMatchingSGBM _matchSettings;
private:
    int _loadCameraParameters();
};


#endif //__MATCH_SGBM_H__
