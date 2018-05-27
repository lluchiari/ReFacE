#ifndef __SETTINGS_SINGLE_H__
#define __SETTINGS_SINGLE_H__

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
#include <utils/Settings.hh>
#include <utils/common.h>

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef SETTING_STORAGE
    #define SETTING_STORAGE FileStorage
#endif

#ifndef SETTING_NODE
    #define SETTING_NODE FileNode
#endif

#ifndef SETTING_NODE_ITERATOR
    #define SETTING_NODE_ITERATOR FileNodeIterator
#endif


using namespace cv;
using namespace std;
using namespace mySettings;

class SettingsSingle : public Settings
{
public:

    SettingsSingle() : goodInput(false) {}

    // Kinds of pattern for calibration
    enum Pattern { NOT_EXISTING, CHESSBOARD, CIRCLES_GRID, ASYMMETRIC_CIRCLES_GRID};

//    //Write serialization for this class
//    void write(SETTING_STORAGE& fs) const;

//    //Read serialization for this class
//    void read(const SETTING_NODE& node);

//    static void read(const SETTING_NODE& node, Settings& x, const Settings& default_value = Settings())
//    {
//        if(node.empty())
//            x = default_value;
//        else
//            x.read(node);
//    }

    // Kind of imput images
    enum InputType {
        INVALID,        //Not valid input image
        CAMERA,         //Images coming from the camera
        VIDEO_FILE,     //Images coming from a video file
        IMAGE_LIST      //Images coming from a image list (remember to ennumerate the immage list)
    };


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

#endif // __SETTINGS_SINGLE_H__