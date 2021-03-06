#ifndef __SETTINGS_CALIB_STEREO_H__
#define __SETTINGS_CALIB_STEREO_H__

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

// Internal Libs //
#include <Utils/Settings.hh>
#include <Utils/common.h>

// 3rd Party Libs //
#include <3rdParty/TinyXML2/tinyxml2.h>


using namespace cv;
using namespace std;
using namespace consts;
using namespace mySettings;

class SettingsCalibStereo : public Settings
{
public:

    SettingsCalibStereo();
    ~SettingsCalibStereo();

    //Read vector for this class
    int read(string);
    int interprate();
    int print();

private:
    bool _isListOfImages(const string&);
    bool _readStringList(const string&, vector<string>&);

public:
    string systemName;
    vector<string> imageList;        // List with addres of image files
    cv::Size boardSize;              // The size of the board -> Number of items by width and height
    string patternToUse;
    float squareSize;                // The size of a square in your defined unit (point, millimeter,etc).
    bool displayCorners;
    bool useCalibrated;
    bool showRectified;              // Shows the rectified images after the calibration
    bool showUndistorsed;            // Show undistorted images after calibration
    string input;                    // The input ->
    string outputCameraFilename;
    string outputExtrinsicFilename;
    string outputIntrinsicFilename;
    InputType inputType;             // It's the type of input used on calibration. Could be camera, video, set of image
    int cameraLeftID;
    int cameraRightID;

//    Pattern calibrationPattern;     // One of the Chessboard, circles, or asymmetric circle pattern
//    int nrFrames;                   // The number of frames to use from the input for calibration
//    float aspectRatio;              // The aspect ratio
//    int delay;                      // In case of a video input
//    bool bwritePoints;              // Write detected feature points
//    bool bwriteExtrinsics;          // Write extrinsic parameters
//    bool calibZeroTangentDist;      // Assume zero tangential distortion
//    bool calibFixPrincipalPoint;    // Fix the principal point at the center
//    bool flipVertical;              // Flip the captured images around the horizontal axis

//    int cameraID;
//    int atImageList;                // Image List Counter for parsing iteration
//    VideoCapture inputCapture;      //
//    InputType inputType;            //
//    bool goodInput;                 //
//    int flag;                       //

};

#endif // SETTINGS_CALIB_STEREO_H
