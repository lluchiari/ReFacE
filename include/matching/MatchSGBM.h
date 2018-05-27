#ifndef __MATCH_SGBM_H__
#define __MATCH_SGBM_H__

// Internal LIBs
#include <utils/common.h>
#include <matching/Matching.hh>
#include <matching/settings/SettingsMatchingSGBM.h>

// OpenCV Libs
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

using namespace myMatching;

class myMatching::MatchSGBM : public Matching
{
public:
    MatchSGBM();
    ~MatchSGBM();
    int config(string) override;
    int match() override;
    int run() override;

    SettingsMatchingSGBM *_matchSettings;
};


#endif //__MATCH_SGBM_H__
