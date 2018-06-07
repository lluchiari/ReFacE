#ifndef __SETTINGS_CALIB_SINGLE_H__
#define __SETTINGS_CALIB_SINGLE_H__

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

/* 3rd Party Libs */
#include <3rdParty/TinyXML2/tinyxml2.h>

// Internal Libs //
#include <Utils/Settings.hh>
#include <Utils/common.h>

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif


using namespace cv;
using namespace std;
using namespace consts;
using namespace mySettings;

class SettingsCalibSingle : public Settings
{
public:

    SettingsCalibSingle() : goodInput(false) {}

    // Kinds of pattern for calibration
    enum Pattern { NOT_EXISTING, CHESSBOARD, CIRCLES_GRID, ASYMMETRIC_CIRCLES_GRID};

    //Read vector for this class
    int read(string);

    void setStackImage(string);

    void setOutputFile(string);

    int interprate();

    Mat nextImage(void);

    bool readStringList( const string& filename, vector<string>& l );

    bool isListOfImages( const string& filename);

    int print();

public:
    string systemName;
    Size boardSize;                 // The size of the board -> Number of items by width and height
    Pattern calibrationPattern;     // One of the Chessboard, circles, or asymmetric circle pattern
    float squareSize;               // The size of a square in your defined unit (point, millimeter,etc).
    int nrFrames;                   // The number of frames to use from the input for calibration
    float aspectRatio;              // The aspect ratio
    int delay;                      // In case of a video input
    bool bwritePoints;              // Write detected feature points
    bool bwriteExtrinsics;          // Write extrinsic parameters
    bool calibZeroTangentDist;      // Assume zero tangential distortion
    bool calibFixPrincipalPoint;    // Fix the principal point at the center
    bool flipVertical;              // Flip the captured images around the horizontal axis
    string outputFileName;          // The name of the file where to write
    bool showUndistorsed;           // Show undistorted images after calibration
    string input;                   // The input ->

    int cameraID;
    vector<string> imageList;       // List with addres of image files
    int atImageList;                // Image List Counter for parsing iteration
    VideoCapture inputCapture;      //
    InputType inputType;            //
    bool goodInput;                 //
    int flag;                       //

private:
    string _patternToUse;


};

#endif // __SETTINGS_CALIB_SINGLE_H__
