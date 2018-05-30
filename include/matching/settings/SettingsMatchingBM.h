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
#include <3rdParty/TinyXML2/tinyxml2.h>


using namespace cv;
using namespace std;
using namespace consts;
using namespace mySettings;

class SettingsMatchingBM : public Settings
{
public:

    SettingsMatchingBM();
    ~SettingsMatchingBM();

    // Read vector for this class
    // Overrided Functions
    int read(string);
    int interprate();
    int print();



    // Read from input file//
    string input;
    InputType inputType;
    string outputFileName;
    float scale;
    int windowSize;
    string camParametersFile;                               //Parameters of the camera stored inside a file
    int maxDisparity;

    int cameraLeftID;
    int cameraRightID;




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
