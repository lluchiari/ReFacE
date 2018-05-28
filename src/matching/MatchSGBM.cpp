#include <matching/MatchSGBM.h>

MatchSGBM::MatchSGBM(){
    this->_name = consts::MATCHING_SGBM;
}

MatchSGBM::~MatchSGBM() {
}

int MatchSGBM::config(string filename){
    //TODO: Check the returns
    this->_matchSettings.read(filename);
    this->_matchSettings.interprate();
    return 1;
}

int MatchSGBM::match(){
    return 1;
}

int MatchSGBM::run(){
    return 1;
}
