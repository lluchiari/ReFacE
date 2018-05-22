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

// Internal Libs //
#include <utils/Settings.hh>
#include <utils/common.h>

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
    void interprate();
    void print();

    // Kind of imput images
    enum InputType {
        INVALID,        //Not valid input image
        CAMERA,         //Images coming from the camera
        VIDEO_FILE,     //Images coming from a video file
        IMAGE_LIST      //Images coming from a image list (remember to ennumerate the immage list)
    };

private:
    bool _isListOfImages(const string&);
    bool _readStringList(const string&, vector<string>&);

public:
    vector<string> _imageList;        // List with addres of image files
    cv::Size _boardSize;              // The size of the board -> Number of items by width and height
    string _patternToUse;
    float _squareSize;                // The size of a square in your defined unit (point, millimeter,etc).
    bool _displayCorners;
    bool _useCalibrated;
    bool _showRectified;              // Shows the rectified images after the calibration
    bool _showUndistorsed;            // Show undistorted images after calibration
    string _input;                    // The input ->
    string outputFileName;           // The name of the file where to write
    InputType _inputType;             // It's the type of input used on calibration. Could be camera, video, set of image
    int _cameraID;
    VideoCapture _inputCapture;       //

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

#endif // SETTINGS_STEREO_H
