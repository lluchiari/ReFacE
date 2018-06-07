#include <Modules/faceRec/FaceRec.h>

FaceRec::FaceRec(){
    this->_name = consts::FACE_REC;
    emit this->getMatchImge();
}

FaceRec::~FaceRec(){

}

int FaceRec::config(string){
    return -1;
}

int FaceRec::run(){
    return -1;
}
