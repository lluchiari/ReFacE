#include <matching/MatchSGBM.h>

MatchSGBM::MatchSGBM(){
    this->_name = consts::MATCHING_SGBM;
}

MatchSGBM::~MatchSGBM() {
}

int MatchSGBM::config(string filename){
    if(LOG_MAIN_CONTROLLER){cout << "MatchSGBM::config(): Start...\n";}

    if(this->_matchSettings.read(filename) != 0 || this->_matchSettings.interprate() != 0){return -1;}

    if(LOG_MAIN_CONTROLLER){cout << "MatchSGBM::config(): Finish_OK!\n";}
    return 1;
}

int MatchSGBM::run(){
    if(LOG_MAIN_CONTROLLER){cout << "MatchSGBM::run(): Start...\n";}
    if(LOG_MAIN_CONTROLLER){cout << "MatchSGBM::run(): Finish_OK!\n";}
    return 1;
}
