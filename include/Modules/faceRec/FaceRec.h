#ifndef __FACEREC_H__
#define __FACEREC_H__

#include <Utils/common.h>
#include <Utils/consts.h>

#include <Modules/faceRec/FaceRecognition.hh>

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

};


#endif //__FACEREC_H__
