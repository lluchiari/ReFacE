#include <Modules/viewer/settings/SettingsViwer3D.h>

SettingsViewer3D::SettingsViewer3D(){
}

SettingsViewer3D::~SettingsViewer3D(){
}

int SettingsViewer3D::read(string fileLocation){
    if(LOG_SETTINGS_VIEWER_3D){cout << "SettingsViewer3D()::read(): Start...\n";}

     tinyxml2::XMLDocument doc;
     tinyxml2::XMLElement *aux;
     if(doc.LoadFile(fileLocation.c_str()) != tinyxml2::XMLError::XML_SUCCESS){
         cerr << "SettingsViewer3D()::read(): Error on loaing xml file!";
         return -1;
     }

     aux = doc.FirstChildElement("ReFacE");
     if(aux == NULL){cerr << "SettingsViewer3D::read(): Error on xml file! 'ReFacE' tag could not be found!\n" ;return -1;}

     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings");
     if(aux == NULL){cerr << "SettingsViewer3D::read(): Error on xml file! 'Settings' tag could not be found!\n" ;return -1;}

     this->systemName = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->Attribute("sys_name");

     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("Input");
     if(aux != NULL){this->input = aux->GetText();} else {cerr << "SettingsViewer3D()::read(): Error on Input\n"; return -1;}

     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("Calib_Param_File");
     if(aux != NULL){this->camParamFile = aux->GetText();} else {cerr << "SettingsViewer3D()::read(): Error on Calib_Param_File\n";return -1;}

     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("Output");
     if(aux != NULL){this->outputFileName = aux->GetText();} else {cerr << "SettingsViewer3D()::read(): Error on Output\n";return -1;}

     if(LOG_SETTINGS_VIEWER_3D){cout << "SettingsViewer3D()::read(): Finish_OK!\n";}
     return 0;
}

int SettingsViewer3D::interprate()
{
    if(LOG_SETTINGS_VIEWER_3D){cout << "SettingsViewer3D()::interprate(): Start...\n";}

    // Input Check //
    if (this->input.empty())
    {
        #if DEBUG_SETTINGS_VIEWER_3D
            cout << "SettingsViewer3D()::interprate(): Input is Empty!" << endl;
        #endif
        cerr << "SettingsViewer3D::interprate(): Error! Invalid input detected!\n";
        return -1;
    }

    // OutputFile Check //
    if(LOG_SETTINGS_VIEWER_3D){cout << "Checking OutputFile\n";}
    if(outputFileName.empty()){
        cerr << "SettingsViewer3D::interprate(): Error! Output file is empty!\n";
        return -1;
    }

    // Parameters File //
    if(LOG_SETTINGS_VIEWER_3D){cout << "Checking camParamFile\n";}
    if(camParamFile.empty()){
        cerr << "SettingsViewer3D::interprate(): Error! Parameters file is empty!\n";
        return -1;
    }

    if(LOG_SETTINGS_VIEWER_3D){cout << "SettingsViewer3D()::interprate(): Finish_OK!\n";}
    return 0;
}

int SettingsViewer3D::print(){
    if(LOG_SETTINGS_VIEWER_3D){cout << "SettingsViewer3D()::print(): Start...\n";}
    if(LOG_SETTINGS_VIEWER_3D){cout << "SettingsViewer3D()::print(): Finish_OK!\n";}
    return 0;

}
