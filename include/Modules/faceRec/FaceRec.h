#ifndef __FACEREC_H__
#define __FACEREC_H__

#include <Utils/common.h>
#include <Utils/consts.h>

#include <Modules/faceRec/FaceRecognition.hh>
#include <Modules/faceRec/settings/SettingsFaceRec.h>

using namespace cv;
using namespace std;

class FaceRec : public FaceRecognition
{
    Q_OBJECT
public:
    FaceRec();
    ~FaceRec();

    int config(string);
    int run();    

private:
    SettingsFaceRec _faceRecSetting;
    string _inputFile;
};


#endif //__FACEREC_H__
