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
        cerr << "MatchBM::_load(): Error on opening Stacks File" << endl;
        return -1;
    }

    fs["M1"] >> _cameraMatrix[0];
    fs["M2"] >> _cameraMatrix[1];
    fs["D1"] >> _distCoeffs[0];
    fs["D2"] >> _distCoeffs[1];
    fs.release();

    cout << _cameraMatrix[0] << "\n" << _cameraMatrix[1] << "\n";
    cout << _distCoeffs[0] << "\n" << _distCoeffs[1] << "\n";


    //TODO:
    // -Prepare inputs (cam1, cam2 or images)


    if(LOG_MATCHING_BM){cout << "MatchBM::config(): Finish_OK!\n";}
    return 0;
}



int MatchBM::run(){
    if(LOG_MATCHING_BM){cout << "MatchBM::run(): Start...\n";}


    //Ptr<StereoBM> bm = StereoBM::create;

    if(_matchSettings.inputType == INVALID){
        cerr << "MatchBM::run(): Error! Invalid input mode!\n";
        return -1;
    }
    else if(_matchSettings.inputType == CAMERA)
    {
        // TODO: Take a shoot!
    }
    else if(_matchSettings.inputType == IMAGE_LIST)
    {
        // TODO: Take the first two images
    }
    else if(_matchSettings.inputType == VIDEO_FILE)
    {
        // TODO: Take a frame (future)

    }




    if(LOG_MATCHING_BM){cout << "MatchBM::run(): Finish_OK!\n";}
    return 0;
}
