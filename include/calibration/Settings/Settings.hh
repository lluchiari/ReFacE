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
    virtual void interprate() = 0;
    virtual void print() =0;

    // Kind of imput images
    enum InputType {
        INVALID,        //Not valid input image
        CAMERA,         //Images coming from the camera
        VIDEO_FILE,     //Images coming from a video file
        IMAGE_LIST      //Images coming from a image list (remember to ennumerate the immage list)
    };

};

#endif // SETTINGS_H
