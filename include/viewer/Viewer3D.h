#ifndef __VIEWER3D_H__
#define __VIEWER3D_H__

// Internal LIBs
#include <utils/common.h>
#include <utils/Module.hh>
#include <utils/Settings.hh>
#include <viewer/Viewer.hh>

// STL Libs
#include <iostream>
#include <string>

using namespace std;
using namespace myModule;
using namespace mySettings;


class Viewer3D : public Viewer
{
public:
    Viewer3D();
    ~Viewer3D();

    int config(string);
    int run();
};


#endif //__VIEWER3D_H__
