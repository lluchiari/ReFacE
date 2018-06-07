#ifndef __VIEWER_H__
#define __VIEWER_H__

// Internal LIBs
#include <Utils/common.h>
#include <Utils/Module.hh>
#include <Utils/Settings.hh>

// STL Libs
#include <iostream>
#include <string>

using namespace std;
using namespace myModule;
using namespace mySettings;


class Viewer : public Module
{
    Q_OBJECT
public:
    virtual ~Viewer(){}
};


#endif //__VIEWER_H__
