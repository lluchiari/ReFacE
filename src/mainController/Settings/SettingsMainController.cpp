#include <mainController/Settings/SettingsMainController.h>

SettingsMainController::SettingsMainController(){
    has_calib_module = false;
    has_match_module = false;
    has_viewer_module = false;
}

SettingsMainController::~SettingsMainController(){

}

int SettingsMainController::read(string fileLocation){

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement *aux;
    string auxString;

    tinyxml2::XMLError err = doc.LoadFile(fileLocation.c_str());
    if(err != tinyxml2::XMLError::XML_SUCCESS){
        cerr << "SettingsMainController::read: Error on loaing xml file!\n";
        return -1;
    }
    #if DEBUG_MAIN_CONTROLLER_SETTINGS
        cout << "SettingsMainController::read: Successful open the file.\n";
    #endif




    // Calibration Mode //
    aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Config_System")->FirstChildElement("Calib_Config");
    if(aux != NULL){
        this->_calibFile = aux->GetText();
        this->has_calib_module = true;

        auxString = doc.FirstChildElement("ReFacE")->FirstChildElement("Config_System")->FirstChildElement("Calib_Config")->Attribute("name");
        if(!auxString.empty()){
            this->_calibType = auxString;
        }
        else{
            this->_calibType = "";
            return -1;
        }
    }
    else{
        this->_calibFile = "";
        this->has_calib_module = false;
    }

    #if DEBUG_MAIN_CONTROLLER_SETTINGS
        cout << "SettingsMainController::read: Successful read Calib_Config: '" << this->_calibFile << "'. Type: " << this->_calibType << "\n";
    #endif



    // Matching Section //
    aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Config_System")->FirstChildElement("Match_Config");
    if(aux != NULL){
        this->_matchFile = aux->GetText();
        this->has_match_module = true;

        auxString = doc.FirstChildElement("ReFacE")->FirstChildElement("Config_System")->FirstChildElement("Match_Config")->Attribute("name");
        if(!auxString.empty()){
            this->_matchType = auxString;
        }
        else{
            this->_matchType = "";
            return -1;
        }
    }
    else{
        this->_matchFile = "";
        this->has_match_module = false;
    }
    #if DEBUG_MAIN_CONTROLLER_SETTINGS
        cout << "SettingsMainController::read: Successful read Match_Config: '" << this->_matchFile << "'. Type: " << this->_matchType << "\n";
    #endif



    // Viewer Section //
    aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Config_System")->FirstChildElement("View_Config");
    if(aux != NULL){
        this->_viewFile = aux->GetText();
        this->has_viewer_module = true;

        auxString = doc.FirstChildElement("ReFacE")->FirstChildElement("Config_System")->FirstChildElement("View_Config")->Attribute("name");
        if(!auxString.empty()){
            this->_viewType = auxString;
        }
        else{
            this->_viewType = "";
            return -1;
        }
    }
    else{
        this->_viewFile = "";
        this->has_viewer_module = false;
    }
    #if DEBUG_MAIN_CONTROLLER_SETTINGS
        cout << "SettingsMainController::read: Successful read View_Config: '" << this->_viewFile << "'. Type: " << this->_viewType << "\n";
    #endif




    // Running Mode //
    aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Config_System")->FirstChildElement("Run_Mode");
    if(aux != NULL){this->_runMode = aux->GetText();}
    else{this->_runMode = "";}
    #if DEBUG_MAIN_CONTROLLER_SETTINGS
        cout << "SettingsMainController::read: Successful read Run_Mode: '" << this->_runMode << "'\n";
    #endif

    return 0;
}

int SettingsMainController::interprate(){
    if(_runMode.empty()){
        cerr << "SettingsMainController::interprate() Error: Not specified Run Mode!\n";
        return -1;
    }

    // Check if has modules //
    if(!_calibFile.empty()){
        has_calib_module = true;
    }
    if(!_matchFile.empty()){
        has_match_module = true;
    }
    if(!_viewFile.empty()){
        has_viewer_module = true;
    }
    return 0;
}

int SettingsMainController::print(){
    cout << "SettingsMainController:\n";
    cout << "Run Mode: " << this->_runMode << endl;
    cout << "Calib File: " << this->_calibFile << endl;
    cout << "Match File: " << this->_matchFile << endl;
    cout << "View File: " << this->_viewFile << endl;
    return 1;
}
