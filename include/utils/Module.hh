#ifndef __MODULE_H__
#define __MODULE_H__

#include <utils/common.h>
#include <utils/Settings.hh>

using namespace std;
using namespace mySettings;

namespace myModule {
    class Module;
    class _MODULE_NAMES_;
}

class myModule::Module
{
public:
    virtual int config(string) = 0;
    virtual int run() = 0;
    virtual string getName(){return _name;}
    virtual ~Module();

    /* The Name of the Module */
    string _name;

protected:
    Settings *_innerSetting;
};

class myModule::_MODULE_NAMES_
{
public:
    static string CALIBRATION_SINGLE;
    static string CALIBRATION_STEREO;
    static string MATCHING_BM;
    static string MATCHING_SGBM;
    static string VEWER3D;
};

string myModule::_MODULE_NAMES_::CALIBRATION_SINGLE  = "Single Calib";
string myModule::_MODULE_NAMES_::CALIBRATION_STEREO  = "Stereo Calib";
string myModule::_MODULE_NAMES_::MATCHING_BM  = "Block Matching";
string myModule::_MODULE_NAMES_::MATCHING_SGBM  = "Semi-Global Block Matching";
string myModule::_MODULE_NAMES_::VEWER3D  = "3D Viewer";

#endif //__MODULE_H__
