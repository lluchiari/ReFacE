#ifndef __STEREOMATCHING_H__
#define __STEREOMATCHING_H__

// Internal LIBs
#include <common.h>
#include <calibration/Calibration.h>

// STL Libs
#include <iostream>
#include <string>

using namespace std;

namespace myStereoMatching {
    class StereoMatching;
    class BlockMatching;
    class SGBM;
}

class myStereoMatching::StereoMatching {

public:

    virtual int match() = 0;
    virtual int config(string) = 0;
    virtual string nameToString(){return _name;}

    // Variables //
    Calibration _calib;
    string _name;

};

static void saveXYZ(const char* filename, const Mat& mat)
{
    const double max_z = 1.0e4;
    FILE* fp = fopen(filename, "wt");
    for(int y = 0; y < mat.rows; y++)
    {
        for(int x = 0; x < mat.cols; x++)
        {
            Vec3f point = mat.at<Vec3f>(y, x);
            if(fabs(point[2] - max_z) < FLT_EPSILON || fabs(point[2]) > max_z) continue;
            fprintf(fp, "%f %f %f\n", point[0], point[1], point[2]);
        }
    }
    fclose(fp);
}


#endif __STEREOMATCHING_H__
