#include <Modules/matching/settings/SettingsMatchingBM.h>

SettingsMatchingBM::SettingsMatchingBM(){
}

SettingsMatchingBM::~SettingsMatchingBM(){
}

int SettingsMatchingBM::read(string fileLocation){
    if(LOG_SETTINGS_MATCHING_BM){cout << "SettingsMatchingBM()::read(): Start...\n";}

     tinyxml2::XMLDocument doc;
     tinyxml2::XMLElement *aux;
     if(doc.LoadFile(fileLocation.c_str()) != tinyxml2::XMLError::XML_SUCCESS){
         cerr << "SettingsMatchingBM()::read(): Error on loaing xml file!";
         return -1;
     }

     aux = doc.FirstChildElement("ReFacE");
     if(aux == NULL){cerr << "SettingsMatchingBM::read(): Error on xml file! 'ReFacE' tag could not be found!\n" ;return -1;}

     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings");
     if(aux == NULL){cerr << "SettingsMatchingBM::read(): Error on xml file! 'Settings' tag could not be found!\n" ;return -1;}

     this->systemName = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->Attribute("sys_name");

     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("Input");
     if(aux != NULL){this->input = aux->GetText();} else {cerr << "SettingsMatchingBM()::read(): Error on Input\n"; return -1;}

     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("Calib_Param_File");
     if(aux != NULL){this->camParamFile = aux->GetText();} else {cerr << "SettingsMatchingBM()::read(): Error on Calib_Param_File\n";return -1;}

     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("Output");
     if(aux != NULL){this->outputFileName = aux->GetText();} else {cerr << "SettingsMatchingBM()::read(): Error on Output\n";return -1;}

     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("Scale");
     if(aux != NULL){this->scale = (float) std::atof(aux->GetText());} else {cerr << "SettingsMatchingBM()::read(): Error on Scale\n";return -1;}

     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("Real_Time_Setter");
     if(aux != NULL){this->hasRealTimeSetter = std::atoi(aux->GetText());} else {this->hasRealTimeSetter = false;}

     // Block Matching Parameters //
     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("Window_Size");
     if(aux != NULL){this->windowSize = std::atoi(aux->GetText());} else {cerr << "SettingsMatchingBM()::read(): Error on Window_Size\n";return -1;}
     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("Max_Disparity");
     if(aux != NULL){this->maxDisparity = std::atoi(aux->GetText());} else {cerr << "SettingsMatchingBM()::read(): Error on Max_Disparity\n";return -1;}
     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("PreFilterCarp");
     if(aux != NULL){this->preFilterCarp = std::atoi(aux->GetText());} else {cerr << "SettingsMatchingBM()::read(): Error on PreFilterCarp\n";return -1;}
     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("UniquenessRatio");
     if(aux != NULL){this->uniquenessRatio = std::atoi(aux->GetText());} else {cerr << "SettingsMatchingBM()::read(): Error on UniquenessRatio\n";return -1;}
     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("SpeckleWindowSize");
     if(aux != NULL){this->speckleWindowSize = std::atoi(aux->GetText());} else {cerr << "SettingsMatchingBM()::read(): Error on SpeckleWindowSize\n";return -1;}
     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("SpeckleRange");
     if(aux != NULL){this->speckleRange = std::atoi(aux->GetText());} else {cerr << "SettingsMatchingBM()::read(): Error on SpeckleRange\n";return -1;}
     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("Disp12MaxDiff");
     if(aux != NULL){this->disp12MaxDiff = std::atoi(aux->GetText());} else {cerr << "SettingsMatchingBM()::read(): Error on Disp12MaxDiff\n";return -1;}

     // Specific Parameters //
     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("TextureThreshold");
     if(aux != NULL){this->textureThreshold = std::atoi(aux->GetText());} else {cerr << "SettingsMatchingBM()::read(): Error on TextureThreshold\n";return -1;}

     if(LOG_SETTINGS_MATCHING_BM){cout << "SettingsMatchingBM()::read(): Finish_OK!\n";}
     return 0;
}

int SettingsMatchingBM::interprate()
{
    if(LOG_SETTINGS_MATCHING_BM){cout << "SettingsMatchingBM()::interprate(): Start...\n";}

    // Input Check //
    if (this->input.empty())
    {
        #if DEBUG_SETTINGS_MATCHING_BM
            cout << "SettingsMatchingBM()::interprate(): Input is Empty!" << endl;
        #endif

        this->inputType = consts::INVALID;
        cerr << "SettingsMatchingBM::interprate(): Error! Invalid input detected!\n";
        return -1;
    }
    else
    {
        // In the CAMERA case. Idicates the ID of the camera.
        if (this->input[0] >= '0' && this->input[0] <= '9')
        {
            #if DEBUG_SETTINGS_MATCHING_BM
                cout << "SettingsMatchingBM()::interprate(): CAMERA Case" << endl;
            #endif

            this->cameraRightID = (int)std::atoi(&this->input[0]);
            this->cameraLeftID = (int)std::atoi(&this->input[2]);

            this->inputType = consts::CAMERA;
        }
        else
        {
            // If the input is the IMAGE LIST case
            if (Settings::isListOfImages(this->input))
            {
                #if DEBUG_SETTINGS_MATCHING_BM
                    cout << "SettingsMatchingBM()::interprate(): IMAGE_LIST mode " << endl;
                #endif
                this->inputType = consts::IMAGE_LIST;
            }
            // If the input is the VIDEO FILE case
            else {
                #if DEBUG_SETTINGS_MATCHING_BM
                    cout << "SettingsMatchingBM()::interprate(): VIDEO_FILE mode " << endl;
                #endif
                this->inputType = consts::VIDEO_FILE;
            }
        }
    }


    // OutputFile Check //
    if(LOG_SETTINGS_MATCHING_BM){cout << "Checking OutputFile\n";}
    if(outputFileName.empty()){
        cerr << "SettingsMatchingBM::interprate(): Error! Output file is empty!\n";
        return -1;
    }

    // Scale Check //
    if(LOG_SETTINGS_MATCHING_BM){cout << "Checking scale\n";}
    if(scale < 0){
        cerr << "SettingsMatchingBM::interprate(): Error! Invalid scale detected!\n";
        return -1;
    }

    // MaxDisparity Check //
    if(LOG_SETTINGS_MATCHING_BM){cout << "Checking maxDisparity\n";}
    if(maxDisparity % 16 != 0){
        cerr << "SettingsMatchingBM::interprate(): Error! Disparity must be divisible by 16!\n";
        return -1;
    }

    // Window Check //
    if(LOG_SETTINGS_MATCHING_BM){cout << "Checking windowSize\n";}
    if(windowSize < 5 || windowSize > 256 || windowSize % 2 != 1){
        cerr << "SettingsMatchingBM::interprate(): Error! Invalid window detected!\n";
        return -1;
    }

    // Parameters File //
    if(LOG_SETTINGS_MATCHING_BM){cout << "Checking camParamFile\n";}
    if(camParamFile.empty()){
        cerr << "SettingsMatchingBM::interprate(): Error! Parameters file is empty!\n";
        return -1;
    }

    if(LOG_SETTINGS_MATCHING_BM){cout << "SettingsMatchingBM()::interprate(): Finish_OK!\n";}
    return 0;
}

int SettingsMatchingBM::print(){
    if(LOG_SETTINGS_MATCHING_BM){cout << "SettingsMatchingBM()::print(): Start...\n";}
    if(LOG_SETTINGS_MATCHING_BM){cout << "SettingsMatchingBM()::print(): Finish_OK!\n";}
    return 0;

}
