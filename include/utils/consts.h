#ifndef __CONSTS_H__
#define __CONSTS_H__

#include <string>
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>

using namespace cv;
using namespace std;

namespace consts{

// Modules Names
const string MAIN_CONTROLLER = "Main Controller";
const string CALIBRATION_SINGLE = "Single Calib";
const string CALIBRATION_STEREO = "Stereo Calib";
const string MATCHING_BM = "Block Matching";
const string MATCHING_SGBM = "Semi-Global Block Matching";
const string VEWER3D = "3D Viewer";
const string FACE_REC = "Face Recognition";
const string FACE_DETECTION = "Face Detection";


// Key Constants
const char ESC_KEY = 27;
const char d_KEY = 100;
const char s_KEY = 115;
const char t_KEY = 116;

enum runMode {
    CAPTURE_IMAGES,
    CALIBRATION_ONLY,
    MATCHING_ONLY,
    CALIBRATION_MATCHING,
    CALIBRATION_MATCHING_VIEW
};


// Kind of imput images
enum InputType {
    INVALID,        //Not valid input image
    CAMERA,         //Images coming from the camera
    VIDEO_FILE,     //Images coming from a video file
    IMAGE_LIST      //Images coming from a image list (remember to ennumerate the immage list)
};


const int MIN_DISPARITY = 0;

}
#endif //__CONSTS_H__
