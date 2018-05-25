#include <matching/MatchBM.h>

MatchBM::MatchBM(){
    this->_name = "Block Matching";
    this->_calibSettings = new SettingsMatchingBM();
}

MatchBM::~MatchBM() {
    delete this->_calibSettings;
}

int MatchBM::config(string filename){

    this->_calibSettings->read(filename);
    this->_calibSettings->interprate();
    return 1;
}


int MatchBM::match(){
    return 1;
}
