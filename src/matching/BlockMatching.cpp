#include <BlockMatching.h>

BlockMatching::BlockMatching(){
    this->_name = "Block Matching";
}

BlockMatching::~BlockMatching() {
    delete this->_calibSettings;
}

int BlockMatching::config(string filename){

    this->_calibSettings = new SettingsMatchingStereo();
    this->_calibSettings->read(filename);
    this->_calibSettings->interprate();
    return 1;
}


int BlockMatching::match(){
    return 1;
}
