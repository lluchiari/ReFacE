#ifndef __FACTORY_H__
#define __FACTORY_H__

#include <utils/common.h>
#include <calibration/CalibSingle.h>
#include <calibration/CalibStereo.h>
#include <matching/MatchBM.h>
#include <matching/MatchSGBM.h>
#include <viewer/Viewer3D.h>

using namespace std;
using namespace myModule;

class Factory {
public:
    virtual ~Factory();
    static Calibration *getNewClibModule(string type)
    {
        if(!type.compare(consts::CALIBRATION_SINGLE)){
            return new CalibSingle();
        }
        else if(!type.compare(consts::CALIBRATION_STEREO)){
            return new CalibStereo();
        }
        else{
            cerr << "Factory::getNewClibModule(): Error! None Type identified!\n";
            return NULL;
        }
    }
    static Matching *getNewMatchModule(string type)
    {
        if(!type.compare(consts::MATCHING_BM)){
            return new MatchBM();
        }
        else if(!type.compare(consts::MATCHING_SGBM)){
            return new MatchSGBM();
        }
        else{
            cerr << "Factory::getNewMatchModule(): Error! None Type identified!\n";
            return NULL;
        }
    }

    static Viewer *getNewViewModule(string type){
        return NULL;
    }
};

#endif //__FACTORY_H__
