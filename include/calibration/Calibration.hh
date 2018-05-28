#ifndef __CALIBRATION_H__
#define __CALIBRATION_H__

/* Internal Libs */
#include <calibration/settings/SettingsCalibSingle.h>
#include <utils/Module.hh>
#include <utils/common.h>

using namespace std;
using namespace myModule;

class Calibration : public Module
{
public:
    virtual ~Calibration(){std::cout << "Calibration Destructor\n";}

private:
    Settings *_s;            //Setting file to be read by the funciton
};

#endif //__CALIBRATION_H__
