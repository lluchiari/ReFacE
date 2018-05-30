#ifndef __COMMON_H__
#define __COMMON_H__

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <utils/consts.h>

#include <opencv2/core/core.hpp>

/////////////////////////////////

/////////////////////////////////
#ifndef DEBUG
    #define DEBUG 0
#endif
/////////////////////////////////

/////////////////////////////////
#ifndef DEBUG_SETTINGS_CALIB_SINGLE
    #define DEBUG_SETTINGS_CALIB_SINGLE 1
#endif

#ifndef DEBUG_SETTINGS_CALIB_STEREO
    #define DEBUG_SETTINGS_CALIB_STEREO 1
#endif

#ifndef DEBUG_CALIB_SINGLE
    #define DEBUG_CALIB_SINGLE 1
#endif

#ifndef DEBUG_CALIB_STEREO
    #define DEBUG_CALIB_STEREO 0
#endif
/////////////////////////////////

/////////////////////////////////
#ifndef DEBUG_MATCHING_BM
#define DEBUG_MATCHING_BM 0
#endif

#ifndef DEBUG_MATCHING_SGBM
#define DEBUG_MATCHING_SGBM 0
#endif

#ifndef DEBUG_SETTINGS_MATCHING_BM
#define DEBUG_SETTINGS_MATCHING_BM 0
#endif

#ifndef DEBUG_SETTINGS_MATCHING_SGBM
#define DEBUG_SETTINGS_MATCHING_SGBM 0
#endif
/////////////////////////////////

/////////////////////////////////
#ifndef DEBUG_VIEWER_3D
#define DEBUG_VIEWER_3D 0
#endif

#ifndef DEBUG_SETTINGS_VIEWER_3D
#define DEBUG_SETTINGS_VIEWER_3D 0
#endif
/////////////////////////////////

/////////////////////////////////
#ifndef DEBUG_MAIN_CONTROLLER
#define DEBUG_MAIN_CONTROLLER 0
#endif

#ifndef DEBUG_SETTINGS_MAIN_CONTROLLER
#define DEBUG_SETTINGS_MAIN_CONTROLLER 0
#endif
//###################################################################
//#                         DEBUG ALL                               #
//###################################################################
#ifdef DEBUG_ALL
    #define DEBUG_SETTINGS_CALIB_SINGLE 1
    #define DEBUG_SETTINGS_CALIB_STEREO 1
    #define DEBUG_CALIB_SINGLE 1
    #define DEBUG_CALIB_STEREO 1
    #define DEBUG_MATCHING_BM 1
    #define DEBUG_MATCHING_SGBM 1
    #define DEBUG_SETTINGS_MATCHING_BM 1
    #define DEBUG_SETTINGS_MATCHING_SGBM 1
    #define DEBUG_VIEWER_3D 1
    #define DEBUG_SETTINGS_VIEWER_3D 1
    #define DEBUG_MAIN_CONTROLLER 1
    #define DEBUG_SETTINGS_MAIN_CONTROLLER 1
    #define DEBUG 1
#endif
//###################################################################
//#                                                                 #
//###################################################################
#ifndef LOG
#define LOG 0
#endif
/////////////////////////////////

/////////////////////////////////
#ifndef LOG_SETTINGS_CALIB_SINGLE
#define LOG_SETTINGS_CALIB_SINGLE 1
#endif

#ifndef LOG_SETTINGS_CALIB_STEREO
#define LOG_SETTINGS_CALIB_STEREO 1
#endif

#ifndef LOG_CALIB_SINGLE
#define LOG_CALIB_SINGLE 1
#endif

#ifndef LOG_CALIB_STEREO
#define LOG_CALIB_STEREO 1
#endif
/////////////////////////////////

/////////////////////////////////
#ifndef LOG_MATCHING_BM
#define LOG_MATCHING_BM 1
#endif

#ifndef LOG_MATCHING_SGBM
#define LOG_MATCHING_SGBM 1
#endif

#ifndef LOG_SETTINGS_MATCHING_BM
#define LOG_SETTINGS_MATCHING_BM 1
#endif

#ifndef LOG_SETTINGS_MATCHING_SGBM
#define LOG_SETTINGS_MATCHING_SGBM 1
#endif
/////////////////////////////////

/////////////////////////////////
#ifndef LOG_VIEWER_3D
#define LOG_VIEWER_3D 1
#endif

#ifndef LOG_SETTINGS_VIEWER_3D
#define LOG_SETTINGS_VIEWER_3D 1
#endif
/////////////////////////////////

/////////////////////////////////
#ifndef LOG_MAIN_CONTROLLER
#define LOG_MAIN_CONTROLLER 1
#endif

#ifndef LOG_SETTINGS_MAIN_CONTROLLER
#define LOG_SETTINGS_MAIN_CONTROLLER 1
#endif
//###################################################################
//#                         LOG ALL                               #
//###################################################################

#ifdef LOG_ALL
    #define LOG_SETTINGS_CALIB_SINGLE 1
    #define LOG_SETTINGS_CALIB_STEREO 1
    #define LOG_CALIB_SINGLE 1
    #define LOG_CALIB_STEREO 1
    #define LOG_MATCHING_BM 1
    #define LOG_MATCHING_SGBM 1
    #define LOG_SETTINGS_MATCHING_BM 1
    #define LOG_SETTINGS_MATCHING_SGBM 1
    #define LOG_VIEWER_3D 1
    #define LOG_SETTINGS_VIEWER_3D 1
    #define LOG_MAIN_CONTROLLER 1
    #define LOG_SETTINGS_MAIN_CONTROLLER 1
    #define LOG 1
#endif
//###################################################################
//#                                                                 #
//###################################################################

using namespace std;
using namespace cv;


#endif // COMMON_H
