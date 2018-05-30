#include <matching/MatchBM.h>

MatchBM::MatchBM(){
    this->_name = consts::MATCHING_BM;
}

MatchBM::~MatchBM() {
}

int MatchBM::config(string filename){
    if(LOG_MATCHING_BM){cout << "MatchBM::config(): Start...\n";}
    if(this->_matchSettings.read(filename) != 0){
        cerr << "MatchBM::config(): Error on read settings!\n";
        return -1;
    }    
    if(this->_matchSettings.interprate() != 0){
        cerr << "MatchBM::config(): Error on interprate!\n";
        return -1;
    }

    // Load the configuration matrix //
    FileStorage fs(_matchSettings.camParametersFile, FileStorage::READ);

    if( !fs.isOpened() ){
        cerr << "MatchBM::config(): Error on opening Camera Matrix File" << endl;
        return -1;
    }

    fs["M1"] >> _cameraMatrix[0];
    fs["M2"] >> _cameraMatrix[1];
    fs["D1"] >> _distCoeffs[0];
    fs["D2"] >> _distCoeffs[1];
    fs.release();

    if(_cameraMatrix[0].empty() || _cameraMatrix[1].empty()){
        cerr << "MatchBM::config(): Error on reading camera matrix!\n";
        return -1;
    }
    if(_distCoeffs[0].empty() || _distCoeffs[1].empty()){
        cerr << "MatchBM::config(): Error on reading distance coefficients!\n";
        return -1;
    }

    // Check the input type in order to prepare the required resources //
    if(_matchSettings.inputType == InputType::CAMERA){
        inputCaptureLeft.open(_matchSettings.cameraLeftID);
        if(!inputCaptureLeft.isOpened()){
            cerr << "MatchBM::config(): Error on opening left camera!\n";
            return -1;
        }
        inputCaptureRight.open(_matchSettings.cameraRightID);
        if(!inputCaptureRight.isOpened()){
            cerr << "MatchBM::config(): Error on opening right camera!\n";
            return -1;
        }
        cout << "CAMERA mode! This are the camera parameters:\n";
        cout << "LeftCamID: " << this->_matchSettings.cameraLeftID << "\n";
        cout << "RightCamID: " << this->_matchSettings.cameraRightID << "\n";
    }
    else if(_matchSettings.inputType == InputType::IMAGE_LIST){
        // isImageList was already verified on SettingsMatchingBM::interprate()
        if(!Settings::readStringList(_matchSettings.input, imageList)){
            cerr << "MatchBM::config():Error on reading xml of string list. Is that on right format?\n";
            return -1;
        }

        #if DEBUG_MATCHING_BM
            cout << "TODO: Take this debug out!\n";
            cout << "MatchBM::config(): Is a list of images! Here are the images:\n";
            for(std::vector<string>::iterator it = imageList.begin(); it != imageList.end(); ++it){
                cout << *it;
                cout << "\n";
            }
        #endif
    }
    else if(_matchSettings.inputType == InputType::VIDEO_FILE){
        cerr << "MatchBM::config(): VIDEO FILE input. This is not an error! Comming soon...\n";
        return -1;
    }
    else if(_matchSettings.inputType == InputType::INVALID){
        cerr << "MatchBM::config(): Error! Invalid Input type mode!\n";
        return -1;
    }

    if(LOG_MATCHING_BM){cout << "MatchBM::config(): Finish_OK!\n";}
    return 0;
}



int MatchBM::run(){
    if(LOG_MATCHING_BM){cout << "MatchBM::run(): Start...\n";}


    //Ptr<StereoBM> bm = StereoBM::create;

    if(_matchSettings.inputType == IMAGE_LIST)
    {
        // TODO: Take the first two images
    }
    else if(_matchSettings.inputType == CAMERA)
    {
        if(!inputCaptureLeft.isOpened()){
            cerr << "MatchBM::run(): Error on opening left camera!\n";
            return -1;
        }
        if(!inputCaptureRight.isOpened()){
            cerr << "MatchBM::run(): Error on opening right camera!\n";
            return -1;
        }

        inputCaptureLeft.release();
        inputCaptureRight.release();

//        Mat imgRight, imgLeft;
    }
    else if(_matchSettings.inputType == VIDEO_FILE)
    {
        // TODO: Take a frame (future)
    }
    else if(_matchSettings.inputType == INVALID){
        cerr << "MatchBM::run(): Error! Invalid input mode!\n";
        return -1;
    }
    else{
        cerr << "MatchBM::run(): WTF?!?!? This message was not suppose to happen!\n";
        return -1;
    }

    if(LOG_MATCHING_BM){cout << "MatchBM::run(): Finish_OK!\n";}
    return 0;
}
