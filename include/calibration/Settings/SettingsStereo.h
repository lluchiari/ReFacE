#ifndef __SETTINGS_STEREO_H__
#define __SETTINGS_STEREO_H__

/* Internal Libs */
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>

/* OPENCV Libs */
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <common.h>

// Internal Libs //
#include <Settings/Settings.hh>

// 3rd Party Libs //
#include <tinyxml2.h>


using namespace cv;
using namespace std;
using namespace myCalibSettings;

class SettingsStereo : public Settings
{
public:

    SettingsStereo();
    ~SettingsStereo();

    //Read vector for this class
    void read(string);

    void print();

private:
    vector<string> _imagelist;      // List with addres of image files
    cv::Size _boardSize;            // The size of the board -> Number of items by width and height
    float _squareSize;              // The size of a square in your defined unit (point, millimeter,etc).
    bool _displayCorners = false;
    bool _useCalibrated = true;
    bool _showRectified = true;     // Shows the rectified images after the calibration
    string _outputFileName;         // The name of the file where to write

    Pattern calibrationPattern;     // One of the Chessboard, circles, or asymmetric circle pattern
//    int nrFrames;                   // The number of frames to use from the input for calibration
//    float aspectRatio;              // The aspect ratio
//    int delay;                      // In case of a video input
//    bool bwritePoints;              // Write detected feature points
//    bool bwriteExtrinsics;          // Write extrinsic parameters
//    bool calibZeroTangentDist;      // Assume zero tangential distortion
//    bool calibFixPrincipalPoint;    // Fix the principal point at the center
//    bool flipVertical;              // Flip the captured images around the horizontal axis
    bool showUndistorsed;           // Show undistorted images after calibration
    string input;                   // The input ->

//    int cameraID;
//    int atImageList;                // Image List Counter for parsing iteration
//    VideoCapture inputCapture;      //
//    InputType inputType;            //
//    bool goodInput;                 //
//    int flag;                       //

//private:
//    string _patternToUse;
};

#endif // SETTINGS_STEREO_H
