#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

// Internal Modules
#include <Utils/common.h>
#include <Utils/consts.h>
#include <Utils/Module.hh>
#include <Utils/Settings.hh>
#include <Utils/Factory.hh>
#include <Utils/CameraCapture.hh>

#include <Modules/connection/Connector.h>

#include <Modules/calibration/Calibration.hh>
#include <Modules/calibration/CalibSingle.h>
#include <Modules/calibration/CalibStereo.h>

#include <Modules/matching/Matching.hh>
#include <Modules/matching/MatchBM.h>
#include <Modules/matching/MatchSGBM.h>

#include <Modules/viewer/Viewer.hh>
#include <Modules/viewer/Viewer3D.h>

#include <Modules/faceRec/FaceRecognition.hh>
#include <Modules/faceRec/FaceRec.h>

#include <Modules/faceDetection/FaceDetection.hh>
#include <Modules/faceDetection/FaceDetector.h>

#include <3rdParty/TinyXML2/tinyxml2.h>

#include <Modules/mainController/Settings/SettingsMainController.h>

using namespace myModule;
using namespace myMatching;
using namespace myConnection;
using namespace myCameraCapture;

namespace myMainController {
    class MainController;
}

class myMainController::MainController : public Module
{
public:
    MainController();
    ~MainController();

    int config(string);
    int run();

public:
    // Modules to be loaded //
    Connection *_connectionModule = NULL;
    Calibration *_calibModule = NULL;
    Matching *_matchModule = NULL;
    Viewer *_viewModule = NULL;
    FaceDetection *_faceDetectionModule = NULL;
    FaceRecognition *_faceRecModule = NULL;

    SettingsMainController _settings;
};


#endif //__CONTROLLER_H__
