#ifndef __SGBM_H__
#define __SGBM_H__

// Internal LIBs
#include <Matching.hh>
#include <matching/settings/SettingsMatchingSGBM.h>
#include <common.h>

// OpenCV Libs
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

// STL Libs
#include <string>

using namespace myMatching;

class myMatching::MatchSGBM : public Matching{
public:
    MatchSGBM();
    ~MatchSGBM();
    int config(string);
    int match();

    SettingsMatchingSGBM *_settings;
};


#endif __MATCH_SGBM_H__
