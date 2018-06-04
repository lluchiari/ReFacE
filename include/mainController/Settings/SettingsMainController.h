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
    string calibFile;
    string calibType;

    // Matching //
    string matchFile;
    string matchType;

    // Vewer //
    string viewFile;
    string viewType;

    string runMode;
    string systemName;


    bool has_calib_module;
    bool has_match_module;
    bool has_viewer_module;
};

#endif //__SETTINGS_MAIN_CONTROLLER_H__
