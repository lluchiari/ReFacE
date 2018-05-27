#ifndef __SETTINGS_H__
#define __SETTINGS_H__

/* Internal Libs */
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>

using namespace std;

namespace mySettings {
    class Settings;
}

class mySettings::Settings
{
public:

    virtual int read(string) = 0;
    virtual int interprate() = 0;
    virtual int print() =0;
    virtual ~Settings();

};

#endif // SETTINGS_H
