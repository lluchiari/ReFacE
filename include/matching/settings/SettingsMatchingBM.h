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
#include <GUI/SetMatchParamWindow.h>

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
    string systemName;
    string input;
    InputType inputType;
    string outputFileName;
    string camParamFile;                               //Parameters of the camera stored inside a file

    int cameraRightID;
    int cameraLeftID;

    // Matchign Parameters //
    float scale;
    int windowSize;
    int maxDisparity;
    int preFilterCarp;
    int uniquenessRatio;
    int speckleWindowSize;
    int speckleRange;
    int disp12MaxDiff;
    //Different
    int textureThreshold;

    bool _configFlag;
    double _rms;                                         // Erro for calibration
    vector<vector<Point2f> > _imagePoints[2];            // The corners of the chessboard found //
    vector<vector<Point3f> > _objectPoints;              // Vector of vectors containing the calibration pattern points. If changes the pattern, than changes the way this is calculated //
};

#endif // __SETTINGS_MATCHING_BM_H__
