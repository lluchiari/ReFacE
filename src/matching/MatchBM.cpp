#include <matching/MatchBM.h>

MatchBM::MatchBM(){
    this->_name = "Block Matching";
    this->_matchSettings = new SettingsMatchingBM();
}

MatchBM::~MatchBM() {
    delete this->_matchSettings;
}

int MatchBM::config(string filename){
    //TODO: Check the returns
    this->_matchSettings->read(filename);
    this->_matchSettings->interprate();
    return 1;
}


int MatchBM::match(){
    return 1;
}
