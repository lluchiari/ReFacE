#ifndef __BLOCKMATCHING_H__
#define __BLOCKMATCHING_H__

// Internal LIBs
#include <Matching.hh>
#include <matching/settings/SettingsMatchingBM.h>
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

class myMatching::BM : public Matching{
public:
    BM();
    ~BM();

    int config(string);
    int match();
};

#endif __BLOCKMATCHING_H__
