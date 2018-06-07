#ifndef __VIEWER3D_H__
#define __VIEWER3D_H__

// Internal LIBs
#include <Utils/common.h>
#include <Utils/Module.hh>
#include <Utils/Settings.hh>
#include <Modules/viewer/Viewer.hh>

// STL Libs
#include <iostream>
#include <string>

using namespace std;
using namespace myModule;
using namespace mySettings;


class Viewer3D : public Viewer
{
    Q_OBJECT
public:
    Viewer3D();
    ~Viewer3D();

    int config(string);
    int run();
};


#endif //__VIEWER3D_H__
