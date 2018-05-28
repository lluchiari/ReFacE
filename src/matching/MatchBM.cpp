#include <matching/MatchBM.h>

MatchBM::MatchBM(){
    this->_name = consts::MATCHING_BM;
}

MatchBM::~MatchBM() {
}

int MatchBM::config(string filename){
    //TODO: Check the returns
    this->_matchSettings.read(filename);
    this->_matchSettings.interprate();
    return 1;
}


int MatchBM::match(){
    return 1;
}

int MatchBM::run(){
    return 1;
}
