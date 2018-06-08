#ifndef __FACTORY_H__
#define __FACTORY_H__

#include <Utils/common.h>
#include <Modules/connection/Connector.h>
#include <Modules/calibration/CalibSingle.h>
#include <Modules/calibration/CalibStereo.h>
#include <Modules/matching/MatchBM.h>
#include <Modules/matching/MatchSGBM.h>
#include <Modules/viewer/Viewer3D.h>
#include <Modules/faceRec/FaceRec.h>

using namespace std;
using namespace myModule;
using namespace myConnection;

class Factory {
public:
    virtual ~Factory();
    static Connection * getNewConnectionModule(string type){
        if(!type.empty()){
            return new Connector();
        }
        else{
            return NULL;
        }
    }
    static Calibration *getNewClibModule(string type)
    {
        if(!type.compare(consts::CALIBRATION_SINGLE)){
            cout << "Factory::getNewMatchModule(): CALIBRATION_SINGLE selected\n";
            return new CalibSingle();
        }
        else if(!type.compare(consts::CALIBRATION_STEREO)){
            cout << "Factory::getNewMatchModule(): CALIBRATION_STEREO selected\n";
            return new CalibStereo();
        }
        else{
            cerr << "Factory::getNewClibModule(): Error! None Type identified!\n";
            return NULL;
        }
    }
    static Matching *getNewMatchModule(string type)
    {
        cout << "Factory::getNewMatchModule(): Input >> " << type << endl;
        if(!type.compare(consts::MATCHING_BM)){
            cout << "Factory::getNewMatchModule(): MATCHING_BM selected\n";
            return new MatchBM();
        }
        else if(!type.compare(consts::MATCHING_SGBM)){
            cout << "Factory::getNewMatchModule(): MATCHING_SGBM selected\n";
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
    static FaceRecognition *getNewFaceModule(string type){
        return NULL;
    }
};

#endif //__FACTORY_H__
