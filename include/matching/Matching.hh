#ifndef __MATCHING_H__
#define __MATCHING_H__

// Internal LIBs
#include <utils/common.h>
#include <utils/Module.hh>
#include <utils/Settings.hh>

// STL Libs
#include <iostream>
#include <string>

using namespace std;
using namespace myModule;
using namespace mySettings;

namespace myMatching {
    class Matching;
    class MatchBM;
    class MatchSGBM;
}

class myMatching::Matching : public Module
{
public:

    virtual int match() = 0;
    virtual ~Matching();
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
};

#endif //__MATCHING_H__
