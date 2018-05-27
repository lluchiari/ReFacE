#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

// Internal Modules
#include <utils/common.h>
#include <utils/Module.hh>
#include <utils/Settings.hh>
#include <utils/Factory.hh>

#include <calibration/Calibration.hh>
#include <calibration/CalibSingle.h>
#include <calibration/CalibStereo.h>

#include <matching/Matching.hh>
#include <matching/MatchBM.h>
#include <matching/MatchSGBM.h>

#include <viewer/Viewer3D.hh>

#include <3rdParty/TinyXML2/tinyxml2.h>

#include <mainController/Settings/SettingsMainController.h>

using namespace myModule;
using namespace myMatching;

namespace myMainController {
    class MainController;
    enum runMode {
      CALIBRATION_ONLY,
      MATCHING_ONLY,
      CALIBRATION_MATCHING
    };
}

class myMainController::MainController : public Module
{
public:
    MainController();
    ~MainController();

    int config(string) override;
    int run() override;

public:

    // Operation Mode
    myMainController::runMode _mode;

    // Modules to be loaded //
    Calibration *_calibModule;
    Matching *_matchModule;
    Viewer *_viewModule;

    SettingsMainController *_settings;
};


#endif //__CONTROLLER_H__
