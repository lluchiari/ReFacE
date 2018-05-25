#include <matching/MatchSGBM.h>

MatchSGBM::MatchSGBM(){
    this->_name = "Semiglobal Block Matching";
    this->_settings = new SettingsMatchingSGBM();
}

MatchSGBM::~MatchSGBM() {

}

int MatchSGBM::config(string filename){
    return 1;
}

int MatchSGBM::match(){
    return 1;
}
