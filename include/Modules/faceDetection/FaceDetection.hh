#ifndef __FACE_DETECTION_H__
#define __FACE_DETECTION_H__

#include <Utils/common.h>
#include <Utils/consts.h>

#include <Utils/Module.hh>

using namespace std;
using namespace cv;
using namespace myModule;

class FaceDetection : public Module
{
    Q_OBJECT
public:
    FaceDetection(){}
    virtual ~FaceDetection(){}

signals:
    void getMatchImge();
};


#endif //__FACE_DETECTION_H__
