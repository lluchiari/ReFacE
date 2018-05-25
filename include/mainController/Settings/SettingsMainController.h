#ifndef __SETTINGS_MAIN_CONTROLLER_H__
#define __SETTINGS_MAIN_CONTROLLER_H__

#include <utils/common.h>
#include <utils/Settings.hh>
#include <3rdParty/TinyXML2/tinyxml2.h>

using namespace std;
using namespace mySettings;

class SettingsMainController : public Settings
{
public:
    SettingsMainController();
    ~SettingsMainController();

    int read(string);
    int interprate();
    int print();

    // Calibration //
    string _calibFile;
    string _calibType;

    // Matching //
    string _matchFile;
    string _matchType;

    // Vewer //
    string _viewFile;
    string _viewType;

    string _runMode;


    bool has_calib_module;
    bool has_match_module;
    bool has_viewer_module;
};

#endif
