#ifndef __CONSTS_H__
#define __CONSTS_H__

#include <string>

using namespace std;

namespace consts{

// Modules Names
const string MAIN_CONTROLLER = "Main Controller";
const string CALIBRATION_SINGLE = "Single Calib";
const string CALIBRATION_STEREO = "Stereo Calib";
const string MATCHING_BM = "Block Matching";
const string MATCHING_SGBM = "Semi-Global Block Matching";
const string VEWER3D = "3D Viewer";


enum runMode {
  CALIBRATION_ONLY,
  MATCHING_ONLY,
  CALIBRATION_MATCHING
};


// Kind of imput images
enum InputType {
    INVALID,        //Not valid input image
    CAMERA,         //Images coming from the camera
    VIDEO_FILE,     //Images coming from a video file
    IMAGE_LIST      //Images coming from a image list (remember to ennumerate the immage list)
};


}
#endif //__CONSTS_H__
