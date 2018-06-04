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

using namespace myMatching;

class myMatching::MatchBM : public Matching{
public:
    MatchBM();
    ~MatchBM();

    int config(string);
    int run();

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

    Mat disp, disp8;

    Mat _R, _T, _E, _F;                                  // All the main matrix that describes the camera and the image system //

    /* Rectified coeficients for stereo matching */
    Mat _R1;                                             // Output 3x3 rectification transform (rotation matrix) for the first camera.
    Mat _R2;                                             // Output 3x3 rectification transform (rotation matrix) for the second camera.
    Mat _P1;                                             // Output 3x4 projection matrix in the new (rectified) coordinate systems for the first camera.
    Mat _P2;                                             // Output 3x4 projection matrix in the new (rectified) coordinate systems for the second camera.
    Mat _Q;

    Rect _validRoi[2];

    SettingsMatchingBM _matchSettings;

private:
    int _loadCameraParameters();

};

#endif //__MATCH_BLOCKMATCHING_H__
