#ifndef __BLOCKMATCHING_H__
#define __BLOCKMATCHING_H__

// Internal LIBs
#include <StereoMatching.hh>
#include <common.h>

// OpenCV Libs
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

// STL Libs
#include <string>

using namespace myStereoMatching;

class myStereoMatching::BlockMatching : public StereoMatching{
public:
    BlockMatching();
    ~BlockMatching();

    int config(string);
    int match();
};

#endif __BLOCKMATCHING_H__
