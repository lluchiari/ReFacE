#ifndef __MATCHING_STEREO_SETTINGS_H__
#define __MATCHING_STEREO_SETTINGS_H__

/* Internal Libs */
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>

/* OPENCV Libs */
#include <opencv2/core/core.hpp>

// Internal Libs //
#include <utils/Settings.hh>
#include <utils/common.h>

// 3rd Party Libs //
#include <tinyxml2.h>


using namespace cv;
using namespace std;
using namespace myCalibSettings;

class MatchingStereoSettings : public Settings
{
public:

    MatchingStereoSettings();
    ~MatchingStereoSettings();

    // Read vector for this class
    // Overrided Functions
    void read(string);
    void interprate();
    void print();

};

#endif // __MATCHING_STEREO_SETTINGS_H__
