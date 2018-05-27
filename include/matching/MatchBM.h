#ifndef __MATCH_BLOCKMATCHING_H__
#define __MATCH_BLOCKMATCHING_H__

// Internal LIBs
#include <matching/Matching.hh>
#include <matching/settings/SettingsMatchingBM.h>
#include <utils/common.h>

// OpenCV Libs
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

using namespace myMatching;

class myMatching::MatchBM : public Matching{
public:
    MatchBM();
    ~MatchBM();

    int config(string) override;
    int match() override;
    int run() override;

    SettingsMatchingBM *_matchSettings;
};

#endif //__MATCH_BLOCKMATCHING_H__