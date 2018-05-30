#ifndef __VIEWER_H__
#define __VIEWER_H__

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
public:
    virtual ~Viewer(){}
};


#endif //__VIEWER_H__
