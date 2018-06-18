#include <Modules/faceRec/FaceRec.h>

FaceRec::FaceRec(){
    this->_name = consts::FACE_REC;
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


    if(LOG_FACE_REC){cout << "FaceRec::run(): Finish_OK!\n";}
    return -1;
}
