#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

// Internal Modules
#include <utils/common.h>
#include <utils/consts.h>
#include <utils/Module.hh>
#include <utils/Settings.hh>
#include <utils/Factory.hh>
#include <utils/CameraCapture.hh>

#include <calibration/Calibration.hh>
#include <calibration/CalibSingle.h>
#include <calibration/CalibStereo.h>

#include <matching/Matching.hh>
#include <matching/MatchBM.h>
#include <matching/MatchSGBM.h>

#include <viewer/Viewer.hh>
#include <viewer/Viewer3D.h>

#include <3rdParty/TinyXML2/tinyxml2.h>

#include <mainController/Settings/SettingsMainController.h>

using namespace myModule;
using namespace myMatching;
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
    // Operation Mode
    consts::runMode _mode;

    // Modules to be loaded //
    Calibration *_calibModule = NULL;
    Matching *_matchModule = NULL;
    Viewer *_viewModule = NULL;


    SettingsMainController _settings;
};


#endif //__CONTROLLER_H__
