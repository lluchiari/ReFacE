#ifndef __SETTINGS_MATCHING_SGBM_H__
#define __SETTINGS_MATCHING_SGBM_H__

/* Internal Libs */
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>

/* OPENCV Libs */
#include <opencv2/core/core.hpp>

// Internal Libs //
#include <utils/common.h>
#include <utils/consts.h>
#include <utils/Settings.hh>

// 3rd Party Libs //
#include <3rdParty/TinyXML2/tinyxml2.h>


using namespace cv;
using namespace std;
using namespace consts;
using namespace mySettings;

class SettingsMatchingSGBM : public Settings
{
public:

    SettingsMatchingSGBM();
    ~SettingsMatchingSGBM();

    int read(string);
    int interprate();
    int print();


    /* Read from input file */
    string systemName;
    string input;
    InputType inputType;
    string outputFileName;
    int channels;

    int cameraRightID;
    int cameraLeftID;

    string camParamFile;                               //Parameters of the camera stored inside a file

    /* Matchign Parameters */
    float scale;
    int windowSize;
    int maxDisparity;
    int preFilterCarp;
    int uniquenessRatio;
    int speckleWindowSize;
    int speckleRange;
    int disp12MaxDiff;
    //Different
    string algorithm;

    bool _configFlag;
    double _rms;                                         // Erro for calibration
    vector<vector<Point2f> > _imagePoints[2];            // The corners of the chessboard found //
    vector<vector<Point3f> > _objectPoints;              // Vector of vectors containing the calibration pattern points. If changes the pattern, than changes the way this is calculated //

};

#endif // __SETTINGS_MATCHING_BM_H__
