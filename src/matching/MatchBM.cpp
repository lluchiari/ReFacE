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

    if(LOG_MATCHING_BM){cout << "MatchBM::config(): Finish_OK!\n";}
    return 0;
}


int MatchBM::match(){
    if(LOG_MATCHING_BM){cout << "MatchBM::match(): Start...\n";}
    if(LOG_MATCHING_BM){cout << "MatchBM::match(): Finish_OK!\n";}
    return 0;
}

int MatchBM::run(){
    if(LOG_MATCHING_BM){cout << "MatchBM::run(): Start...\n";}
    if(LOG_MATCHING_BM){cout << "MatchBM::run(): Finish_OK!\n";}
    return 0;
}
