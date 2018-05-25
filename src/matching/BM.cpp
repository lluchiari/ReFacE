#include <BM.h>

BM::BM(){
    this->_name = "Block Matching";
    this->_calibSettings = new SettingsMatchingBM();
}

BM::~BM() {
    delete this->_calibSettings;
}

int BM::config(string filename){

    this->_calibSettings->read(filename);
    this->_calibSettings->interprate();
    return 1;
}


int BM::match(){
    return 1;
}
