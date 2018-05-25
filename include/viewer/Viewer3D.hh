#ifndef __VIEW_H__
#define __VIEW_H__

// Internal LIBs
#include <utils/common.h>
#include <utils/Module.hh>
#include <utils/Settings.hh>

// STL Libs
#include <iostream>
#include <string>

using namespace std;
using namespace myModule;
using namespace mySettings;


class Viewer : public Module
{
    virtual int config(string);
    virtual int run();
};


#endif //__VIEW_H__
