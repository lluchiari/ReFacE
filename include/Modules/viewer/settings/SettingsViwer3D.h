#ifndef __SETTINGS_VIWER_3D_H__
#define __SETTINGS_VIWER_3D_H__

/* Internal Libs */
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>

/* OPENCV Libs */
#include <opencv2/core/core.hpp>

// Internal Libs //
#include <Utils/common.h>
#include <Utils/Settings.hh>

// 3rd Party Libs //
#include <3rdParty/TinyXML2/tinyxml2.h>


using namespace cv;
using namespace std;
using namespace consts;
using namespace mySettings;

class SettingsViewer3D : public Settings
{
public:

    SettingsViewer3D();
    ~SettingsViewer3D();

    // Read vector for this class
    // Overrided Functions
    int read(string);
    int interprate();
    int print();

    // General Parameters//
    string systemName;
    string input;
    string outputFileName;
    string camParamFile;                               //Parameters of the camera stored inside a file

    // Viewer Param
};

#endif // __SETTINGS_VIWER_3D_H__
