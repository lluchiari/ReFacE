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
        this->calibFile = aux->GetText();
        this->has_calib_module = true;

        auxString = doc.FirstChildElement("ReFacE")->FirstChildElement("Config_System")->FirstChildElement("Calib_Config")->Attribute("name");
        if(!auxString.empty()){
            this->calibType = auxString;
        }
        else{
            this->calibType = "";
            return -1;
        }
    }
    else{
        this->calibFile = "";
        this->has_calib_module = false;
    }

    #if DEBUG_MAIN_CONTROLLER_SETTINGS
        cout << "SettingsMainController::read: Successful read Calib_Config: '" << this->calibFile << "'. Type: " << this->calibType << "\n";
    #endif



    // Matching Section //
    aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Config_System")->FirstChildElement("Match_Config");
    if(aux != NULL){
        this->matchFile = aux->GetText();
        this->has_match_module = true;

        auxString = doc.FirstChildElement("ReFacE")->FirstChildElement("Config_System")->FirstChildElement("Match_Config")->Attribute("name");
        if(!auxString.empty()){
            this->matchType = auxString;
        }
        else{
            this->matchType = "";
            return -1;
        }
    }
    else{
        this->matchFile = "";
        this->has_match_module = false;
    }
    #if DEBUG_MAIN_CONTROLLER_SETTINGS
        cout << "SettingsMainController::read: Successful read Match_Config: '" << this->matchFile << "'. Type: " << this->matchType << "\n";
    #endif



    // Viewer Section //
    aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Config_System")->FirstChildElement("View_Config");
    if(aux != NULL){
        this->viewFile = aux->GetText();
        this->has_viewer_module = true;

        auxString = doc.FirstChildElement("ReFacE")->FirstChildElement("Config_System")->FirstChildElement("View_Config")->Attribute("name");
        if(!auxString.empty()){
            this->viewType = auxString;
        }
        else{
            this->viewType = "";
            return -1;
        }
    }
    else{
        this->viewFile = "";
        this->has_viewer_module = false;
    }
    #if DEBUG_MAIN_CONTROLLER_SETTINGS
        cout << "SettingsMainController::read: Successful read View_Config: '" << this->viewFile << "'. Type: " << this->viewType << "\n";
    #endif




    // Running Mode //
    aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Config_System")->FirstChildElement("Run_Mode");
    if(aux != NULL){this->runMode = aux->GetText();}
    else{this->runMode = "";}
    #if DEBUG_MAIN_CONTROLLER_SETTINGS
        cout << "SettingsMainController::read: Successful read Run_Mode: '" << this->runMode << "'\n";
    #endif

    return 0;
}

int SettingsMainController::interprate(){
    if(runMode.empty()){
        cerr << "SettingsMainController::interprate() Error: Not specified Run Mode!\n";
        return -1;
    }

    // Check if has modules //
    if(!calibFile.empty()){
        has_calib_module = true;
    }
    if(!matchFile.empty()){
        has_match_module = true;
    }
    if(!viewFile.empty()){
        has_viewer_module = true;
    }
    return 0;
}

int SettingsMainController::print(){
    cout << "SettingsMainController:\n";
    cout << "Run Mode: " << this->runMode << endl;
    cout << "Calib File: " << this->calibFile << endl;
    cout << "Match File: " << this->matchFile << endl;
    cout << "View File: " << this->viewFile << endl;
    return 1;
}
