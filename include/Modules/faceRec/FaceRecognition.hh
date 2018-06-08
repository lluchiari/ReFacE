#ifndef __FACERECOGNITION_H__
#define __FACERECOGNITION_H__

#include <Utils/common.h>
#include <Utils/consts.h>

#include <Utils/Module.hh>

using namespace std;
using namespace cv;
using namespace myModule;

class FaceRecognition : public Module
{
    Q_OBJECT
public:
    FaceRecognition(){}
    virtual ~FaceRecognition(){}
    virtual void faceDetect()=0;
    virtual void faceRecognize()=0;

signals:
    void getMatchImge();
};


#endif //__FACERECOGNITION_H__
