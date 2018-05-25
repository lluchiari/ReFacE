#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

// Internal Modules
#include <utils/common.h>
#include <utils/Module.hh>
#include <utils/Settings.hh>

#include <calibration/Calibration.hh>
#include <calibration/SingleCalib.h>
#include <calibration/StereoCalib.h>

#include <matching/Matching.hh>

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

class myMainController::MainController : Module
{
public:
    MainController();
    ~MainController();

    int config(string);
    int run();

    // Operation Mode
    myMainController::runMode _mode;

    // TODO: Vector of mudules // (Future)
 //    vector<Module*> _modules;

    // Modules to be loaded //
    bool has_calib_Module;
    StereoCalib *_calibModule;

    bool has_match_module;
    Matching *_matchModule;

    bool has_view_module;
    Viewer *_viewModule;

    SettingsMainController *_settings;
};


#endif __CONTROLLER_H__
