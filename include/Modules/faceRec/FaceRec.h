#ifndef __FACEREC_H__
#define __FACEREC_H__

#include <Utils/common.h>
#include <Utils/consts.h>

#include <Modules/faceRec/settings/SettingsFaceRec.h>

#include <Modules/faceRec/FaceRecognition.hh>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define HAAR_CASCADE_CONFIG_FACE_FILE "../config/face/HaarCascade/haarcascade_frontalface_default.xml"
#define HAAR_CASCADE_CONFIG_EYE_FILE "../config/face/HaarCascade/haarcascade_eye.xml"

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

    void faceDetect();
    void faceRecognize();

    /**
     * @brief haarCascadeFaceDetection runs the Har-Cascade method
     * @return the number of faces detected
     * @arg fileLocation is the input image file location
     * @arg image is the input image to find the faces
     * @arg output is the matriz with the rectangles dawed
     * @arg
     */
    int haarCascadeFaceDetection(string fileLocation, Mat image, Mat& outImg, vector<Rect>& Rects);

private:
    SettingsFaceRec _faceRecSetting;
    string _inputFile;
};


#endif //__FACEREC_H__
