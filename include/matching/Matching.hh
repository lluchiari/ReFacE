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
    virtual ~Matching(){}
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

    virtual void setScale(float){}
    virtual float getScale(){return 0;}

    virtual void setWindowSize(int){}
    virtual int getWindowSize(){return 0;}

    virtual void setMaxDisparity(int){}
    virtual int getMaxDisparity(){return 0;}

    virtual void setPreFilterCarp(int){}
    virtual int getPreFilterCarp(){return 0;}

    virtual void setUniquenessRatio(int){}
    virtual int getUniquenessRatio(){return 0;}

    virtual void setSpeckleWindowSize(int){}
    virtual int getSpeckleWindowSize(){return 0;}

    virtual void setSpeckleRange(int){}
    virtual int getSpeckleRange(){return 0;}

    virtual void setDisp12MaxDiff(int){}
    virtual int getDisp12MaxDiff(){return 0;}

    //Different
    virtual void setTextureThreshold(int){}
    virtual int getTextureThreshold(){return 0;}

    virtual void setAlgorithm(string){}
    virtual string getAlgorithm(){return NULL;}

};

#endif //__MATCHING_H__
