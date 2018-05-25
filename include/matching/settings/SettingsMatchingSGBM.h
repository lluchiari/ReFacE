#ifndef __SETTINGS_MATCHING_BM_H__
#define __SETTINGS_MATCHING_BM_H__

/* Internal Libs */
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>

/* OPENCV Libs */
#include <opencv2/core/core.hpp>

// Internal Libs //
#include <utils/common.h>
#include <utils/Settings.hh>

// 3rd Party Libs //
#include <tinyxml2.h>


using namespace cv;
using namespace std;
using namespace mySettings;

class SettingsMatchingSGBM : public Settings
{
public:

    SettingsMatchingSGBM();
    ~SettingsMatchingSGBM();

    // Read vector for this class
    // Overrided Functions
    int read(string);
    int interprate();
    int print();

    /* Stereo Camera Parameters */
    Mat _cameraMatrix[2];                                // Stores the cameras matrix containing all the information for stereo process. //
    Mat _distCoeffs[2];                                  // Distortion coeficient matrix //
    Mat _R, _T, _E, _F;                                  // All the main matrix that describes the camera and the image system //

    /* Rectified coeficients for stereo matching */
    Mat _R1;                                             // Output 3x3 rectification transform (rotation matrix) for the first camera.
    Mat _R2;                                             // Output 3x3 rectification transform (rotation matrix) for the second camera.
    Mat _P1;                                             // Output 3x4 projection matrix in the new (rectified) coordinate systems for the first camera.
    Mat _P2;                                             // Output 3x4 projection matrix in the new (rectified) coordinate systems for the second camera.
    Mat _Q;

    Rect _validRoi[2];
    bool _configFlag;
    double _rms;                                         // Erro for calibration
    vector<vector<Point2f> > _imagePoints[2];            // The corners of the chessboard found //
    vector<vector<Point3f> > _objectPoints;              // Vector of vectors containing the calibration pattern points. If changes the pattern, than changes the way this is calculated //

};

#endif // __SETTINGS_MATCHING_BM_H__
