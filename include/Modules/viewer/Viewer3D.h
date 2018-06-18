#ifndef __VIEWER3D_H__
#define __VIEWER3D_H__

// Internal LIBs
#include <Utils/common.h>
#include <Utils/Module.hh>
#include <Utils/Settings.hh>
#include <Modules/viewer/Viewer.hh>
#include <Modules/viewer/settings/SettingsViwer3D.h>

// STL Libs
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstring>

#include <3rdParty/TinyPly/tinyply.h>

using namespace std;
using namespace cv;
using namespace tinyply;
using namespace myModule;
using namespace mySettings;


class Viewer3D : public Viewer
{
    Q_OBJECT
public:
    Viewer3D();
    ~Viewer3D();

    // Overrided Function
    int config(string);
    int run();

    Mat dispMap;                    // Disparity Map taken from the Match Method
    Mat mesh3D;                     // Mesh of points in space, representing the disparity in xyz coordinates

    void setQMatrix(Mat Q);
    Mat getQMatrix(void);

    int writePlyFile(std::string filename, Mat mesh3D);
    int readPlyFile(std::string filename);

private:
    Mat _Q;
    SettingsViewer3D _viewerSettings;

    int _loadCameraParameters();
};


#endif //__VIEWER3D_H__
