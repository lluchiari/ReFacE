#include <SGBM.h>

SGBM::SGBM(){
    this->_name = "Semiglobal Block Matching";
}

SGBM::~SGBM() {

}

int SGBM::config(string filename){
    return 1;
}

int SGBM::match(){
    return 1;
}
