#ifndef __STEROCALIB_H__
#define __STEROCALIB_H__

// OpenCV Includes
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


// STL Includes
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


class SteroCalib
{
public:
    SteroCalib();
public:
    void calibrate(const vector<string>&, Size, float, bool, bool, bool);
};

#endif // __STEROCALIB_H__
