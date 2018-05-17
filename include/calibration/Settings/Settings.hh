#ifndef __SETTINGS_H__
#define __SETTINGS_H__

/* Internal Libs */
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>

using namespace std;

namespace myCalibSettings {
    class Settings;
}

class myCalibSettings::Settings
{
public:

    virtual void read(string) = 0;
    virtual void print() =0;

};

#endif // SETTINGS_H
