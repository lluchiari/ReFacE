#ifndef __CALIBRATION_H__
#define __CALIBRATION_H__

/* Internal Libs */
#include <calibration/settings/SettingsCalibSingle.h>
#include <utils/Module.hh>
#include <utils/common.h>

using namespace myModule;

class Calibration : public Module
{
public:    

private:
    Settings *_s;            //Setting file to be read by the funciton
};

#endif
