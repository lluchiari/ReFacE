#ifndef __REFACE__
#define __REFACE__

// STL Libs
#include <iostream>
#include <fstream>
#include <string>

// QT Libs
#include <QApplication>

// Internal Libs
#include <MainWindow.h>
#include <calibration/Calibration.h>
#include <calibration/StereoCalib.h>
#include <matching/StereoMatching.hh>
#include <matching/BlockMatching.h>
#include <matching/SGBM.h>

// OpenCV Libs
#include <opencv2/core/utility.hpp>


using namespace cv;
using namespace std;
using namespace myStereoMatching;
//using namespace myStereoCalibration;


#define PROGRAM_OPTIONS 3


/* Default config files */

// Match default //
#define DEFAULT_MATCH "../config/match/match_bm.xml"
#define DEFAULT_MATCH_PARAM "--algorithm=bm";

// Calib default //
#define DEFAULT_CALIB "../config/calib/calib_stereo.xml"

#endif
