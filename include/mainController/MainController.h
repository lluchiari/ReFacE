#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

// Internal Modules
#include <utils/common.h>
#include <utils/Module.hh>
#include <utils/Settings.hh>

#include <calibration/Calibration.hh>
#include <calibration/CalibSingle.h>
#include <calibration/CalibStereo.h>

#include <matching/Matching.hh>

#include <viewer/Viewer3D.hh>

#include <3rdParty/TinyXML2/tinyxml2.h>
#include <3rdParty/wallaroo/collaborator.h>
#include <3rdParty/wallaroo/registered.h>
#include <3rdParty/wallaroo/attribute.h>
#include <3rdParty/wallaroo/part.h>

#include <mainController/Settings/SettingsMainController.h>

using namespace myModule;
using namespace myMatching;
using namespace wallaroo;

namespace myMainController {
    class MainController;
    enum runMode {
      CALIBRATION_ONLY,
      MATCHING_ONLY,
      CALIBRATION_MATCHING
    };
}

class myMainController::MainController : public Module, public Part
{
public:
    MainController();
    ~MainController();

    int config(string);
    int run();
private:
    Module *_getType(string);
public:

    // Operation Mode
    myMainController::runMode _mode;

    // TODO: Vector of mudules // (Future)
 //    vector<Module*> _modules;

    // Modules to be loaded //
    bool has_calib_Module;
    Collaborator<Calibration> *_calibModule;

    bool has_match_module;
    Collaborator<Matching> *_matchModule;

    bool has_view_module;
    Collaborator<Viewer> *_viewModule;

    SettingsMainController *_settings;
};


#endif __CONTROLLER_H__
