#include <Modules/faceRec/FaceRec.h>

FaceRec::FaceRec(){
    this->_name = consts::FACE_REC;
    emit this->getMatchImge();
}

FaceRec::~FaceRec(){

}

int FaceRec::config(string filename){
    if(LOG_FACE_REC){cout << "FaceRec::config(): Start...\n";}

    if(this->_faceRecSetting.read(filename) != 0){
        cerr << "FaceRec::config(): Error on read settings!\n";
        return -1;
    }
    if(this->_faceRecSetting.interprate() != 0){
        cerr << "FaceRec::config(): Error on interprate!\n";
        return -1;
    }



    if(LOG_FACE_REC){cout << "FaceRec::config(): Finish_OK!\n";}
    return 0;
}

int FaceRec::run(){
    if(LOG_FACE_REC){cout << "FaceRec::run(): Start...\n";}

    int rectnum;
    Mat output, img;
    vector<Rect> roi;
    img = imread(this->_inputFile, IMREAD_GRAYSCALE);
    rectnum = this->haarCascadeFaceDetection(HAAR_CASCADE_CONFIG_FACE_FILE, img, output, roi);

    cout << "Detected Faces: " << rectnum << "\n";

    if(LOG_FACE_REC){cout << "FaceRec::run(): Finish_OK!\n";}
    return -1;
}

void FaceRec::faceDetect(){

}

void FaceRec::faceRecognize(){

}

int haarCascadeFaceDetection(string fileLocation, Mat image, Mat& outImg, vector<Rect>& Rects)
{
    CascadeClassifier face_cascade = cv::CascadeClassifier(fileLocation);
//    CascadeClassifier eye_cascade = cv::CascadeClassifier(HAAR_CASCADE_CONFIG_EYE_FILE);

    Mat img, gray;
//    vector<Rect> eye_roi;
//    vector<int> rejectLevels;
//    vector<double> levelWeights;
    img = image;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    face_cascade.detectMultiScale(img,CV_OUT Rects);
    for(int i=0; i<Rects.size();i++){
        rectangle(img, Rects.at(i),Scalar(0,0,255),2);
    }
    imshow("Faces", img);

    img.copyTo(outImg);
//    eye_cascade.detectMultiScale(img, eye_roi, rejectLevels,levelWeights);
    return ;
}
