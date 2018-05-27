#ifndef __COMMON_H__
#define __COMMON_H__

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <opencv2/core/core.hpp>

#ifndef DEBUG
    #define DEBUG 0
#endif

#ifndef DEBUG_MAIN_CONTROLLER
    #define DEBUG_MAIN_CONTROLLER 1
#endif

#ifndef DEBUG_MAIN_CONTROLLER_SETTINGS
    #define DEBUG_MAIN_CONTROLLER_SETTINGS 1
#endif



#ifndef DEBUG_CALIBRATION
    #define DEBUG_CALIBRATION 0
#endif

#ifndef DEBUG_STEREO_CALIBRATION
    #define DEBUG_CALIBRATION_STEREO 0
#endif

#ifndef DEBUG_SETTINGS
    #define DEBUG_SETTINGS 0
#endif

#ifndef DEBUG_SETTINGS_SINGLE
    #define DEBUG_SETTINGS_SINGLE 0
#endif

#ifndef DEBUG_SETTINGS_STEREO
    #define DEBUG_SETTINGS_STEREO 0
#endif

#ifndef DEBUG_MATCHING_STEREO
    #define DEBUG_MATCHING_STEREO 0
#endif



//###################################################################
//#                         DEBUG ALL                               #
//###################################################################

#ifdef DEBUG_ALL
    #define DEBUG_CALIBRATION_STEREO 1
    #define DEBUG_MAIN_CONTROLLER 1
    #define DEBUG_SETTINGS_SINGLE 1
    #define DEBUG_SETTINGS_STEREO 1
    #define DEBUG_MATCHING_STEREO 1
    #define DEBUG_CALIBRATION 1
    #define DEBUG_SETTINGS 1
    #define DEBUG 1
#endif

//###################################################################
//#                                                                 #
//###################################################################


using namespace std;
using namespace cv;


#endif // COMMON_H
