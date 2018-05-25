#ifndef __MODULE_H__
#define __MODULE_H__

#include <utils/common.h>
#include <utils/Settings.hh>

using namespace std;
using namespace mySettings;

namespace myModule {
    class Module;
}

class myModule::Module
{
public:
    virtual int config(string) = 0;
    virtual int run() = 0;
    virtual string getName(){return _name;}
    virtual ~Module() {}

    /* The Name of the Module */
    string _name;

protected:
    Settings *_innerSetting;
};

struct _MODULE_NAMES_
{
    const string CALIBRATION_SINGLE  = "Single Calib";
    const string CALIBRATION_STEREO  = "Stereo Calib";
    const string MATCHING_BM  = "Block Matching";
    const string MATCHING_SGBM  = "Semi-Global Block Matching";
    const string VEWER3D  = "3D Viewer";
} NameOfModules;

#endif __MODULE_H__
