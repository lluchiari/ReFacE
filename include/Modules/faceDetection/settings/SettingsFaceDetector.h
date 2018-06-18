#ifndef __SETTINGS_FACE_DETECTOR_H__
#define __SETTINGS_FACE_DETECTOR_H__

#include <Utils/common.h>
#include <Utils/consts.h>

#include <Utils/Settings.hh>

// 3rd Party Libs //
#include <3rdParty/TinyXML2/tinyxml2.h>

using namespace std;
using namespace cv;
using namespace mySettings;

class SettingsFaceDetector : public Settings
{
public:
    SettingsFaceDetector();
    ~SettingsFaceDetector();

    int read(string);
    int interprate();
    int print();
};

#endif //__SETTINGS_FACE_DETECTOR_H__
