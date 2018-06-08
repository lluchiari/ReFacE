#include <Modules/connection/Connector.h>

myConnection::Connector::Connector(){

}

myConnection::Connector::~Connector(){

}


void myConnection::Connector::match_Output(Mat matchOut){
    this->_matchOut = matchOut;

    // Dispara signal para próximo módulo;
    emit view_Input(this->_matchOut);
}


int myConnection::Connector::config(string filename){
    return -1;
}

int myConnection::Connector::run(){
    return -1;
}
