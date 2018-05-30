#include <matching/settings/SettingsMatchingBM.h>

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
     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("Input");
     if(aux != NULL){this->input = aux->GetText();} else {cerr << "SettingsMatchingBM()::read(): Error on Input\n"; return -1;}

     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("Calib_File_Input");
     if(aux != NULL){this->camParametersFile = aux->GetText();} else {cerr << "SettingsMatchingBM()::read(): Error on Calib_Fileinput\n";return -1;}

     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("Write_outputFileName");
     if(aux != NULL){this->outputFileName = aux->GetText();} else {cerr << "SettingsMatchingBM()::read(): Error on Write_outputFileName\n";return -1;}

     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("Max_Disparity");
     if(aux != NULL){this->maxDisparity = std::atoi(aux->GetText());} else {cerr << "SettingsMatchingBM()::read(): Error on Max_Disparity\n";return -1;}

     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("Scale");
     if(aux != NULL){this->scale = (float) std::atof(aux->GetText());} else {cerr << "SettingsMatchingBM()::read(): Error on Scale\n";return -1;}

     aux = doc.FirstChildElement("ReFacE")->FirstChildElement("Settings")->FirstChildElement("Window_Size");
     if(aux != NULL){this->windowSize = std::atoi(aux->GetText());} else {cerr << "SettingsMatchingBM()::read(): Error on Window_Size\n";return -1;}

    if(LOG_SETTINGS_MATCHING_BM){cout << "SettingsMatchingBM()::read(): Finish_OK!\n";}
    return 0;
}

int SettingsMatchingBM::interprate(){
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
            this->cameraRightID = this->input[0];
            this->cameraLeftID = this->input[2];
            this->inputType = consts::CAMERA;
        }
        else
        {
            // If the input is the IMAGE LIST case
            if (_isListOfImages(this->input) && _readStringList(this->input, this->imageList))
            {
                #if DEBUG_SETTINGS_MATCHING_BM
                    cout << "SettingsMatchingBM()::interprate(): IMAGE_LIST mode " << endl;
                #endif
                this->inputType = consts::IMAGE_LIST;
                //this->nrFrames = (this->nrFrames < (int)imageList.size()) ? this->nrFrames : (int)imageList.size();
                //                if(DEBUG_SETTINGS_STEREO){cout << "SettingsMatchingBM()::interprate(): Number of Frames: " << this->nrFrames<< endl;}
            }
            // If the input is the VIDEO FILE case
            else {
                #if DEBUG_SETTINGS_MATCHING_BM
                    cout << "SettingsMatchingBM()::interprate(): VIDEO_FILE mode " << endl;
                #endif
                this->inputType = consts::VIDEO_FILE;
            }
        }
        if (this->inputType == consts::CAMERA){
            #if DEBUG_SETTINGS_MATCHING_BM
                cout << "SettingsMatchingBM()::interprate(): CAMERA open mode " << endl;
            #endif
            //            this->inputCapture.open(this->cameraID);
        }
        if (this->inputType == consts::VIDEO_FILE){
            #if DEBUG_SETTINGS_MATCHING_BM
                cout << "SettingsMatchingBM()::interprate(): VIDEO_FILE open mode " << endl;
            #endif
            //            this->inputCapture.open(input);
        }
//        if (this->inputType != consts::IMAGE_LIST && !this->inputCapture.isOpened()){
//            #if DEBUG_SETTINGS_MATCHING_BM
//                cout << "SettingsMatchingBM()::interprate(): INVALID mode! Error on opening the Camera System! " << endl;
//            #endif
//            this->inputType = consts::INVALID;
//            cerr << "SettingsMatchingBM::interprate(): Error! Invalid input detected!\n";
//            return -1;
//        }
    }


    // OutputFile Check //
    if(outputFileName.empty()){
        cerr << "SettingsMatchingBM::interprate(): Error! Output file is empty!\n";
        return -1;
    }

    // Scale Check //
    if(scale <0){
        cerr << "SettingsMatchingBM::interprate(): Error! Invalid scale detected!\n";
        return -1;
    }

    // Window Check //
    if(windowSize < 1 || windowSize % 2 != 1){
        cerr << "SettingsMatchingBM::interprate(): Error! Invalid window detected!\n";
    }

    // Parameters File //
    if(camParametersFile.empty()){
        cerr << "SettingsMatchingBM::interprate(): Error! Parameters file is empty!\n";
    }

    if(LOG_SETTINGS_MATCHING_BM){cout << "SettingsMatchingBM()::interprate(): Finish_OK!\n";}
    return 0;
}

int SettingsMatchingBM::print(){
    if(LOG_SETTINGS_MATCHING_BM){cout << "SettingsMatchingBM()::print(): Start...\n";}
    if(LOG_SETTINGS_MATCHING_BM){cout << "SettingsMatchingBM()::print(): Finish_OK!\n";}
    return 0;

}

bool SettingsMatchingBM::_isListOfImages( const string& filename)
{
    string s(filename);
    #if DEBUG_SETTINGS_MATCHING_BM
        cout << "SettingsMatchingBM::isListOfImages(): String Name:"<< s << endl;
    #endif
    // Look for file extension
    if( s.find(".xml") == string::npos && s.find(".yaml") == string::npos && s.find(".yml") == string::npos )
    {
        cerr << "SettingsMatchingBM::isListOfImages(): File extension is incorrect!" << endl;
        return false;
    }
    else{
        #if DEBUG_SETTINGS_MATCHING_BM
            cout << "SettingsMatchingBM::isListOfImages(): Return True" << endl;
        #endif
        return true;
    }
}

/**
 * @brief SettingsStereo::_readStringList Read the xml file containing the list of images
 * @param filename is the path of the xml file
 * @param l is the list where the images will be saved
 * @return true if everything is ok. False otherwise
 * @author OpenCV Library
 */
bool SettingsMatchingBM::_readStringList( const string& filename, vector<string>& l )
{
    l.clear();
    FileStorage fs(filename, FileStorage::READ);
    if( !fs.isOpened() ){
        cerr << "SettingsMatchingBM::readStringList: Error on opening Stacks File" << endl;
        return false;
    }
    FileNode n = fs.getFirstTopLevelNode();
    if( n.type() != FileNode::SEQ ){
        cerr << "SettingsMatchingBM::readStringList: Error! Incorrect Syntax on file or File is not a sequence." << endl;
        return false;
    }
    FileNodeIterator it = n.begin(), it_end = n.end();
    for( ; it != it_end; ++it ){
        l.push_back((string)*it);
    }
    #if DEBUG_SETTINGS_CALIB_STEREO
        cout << "SettingsMatchingBM::readStringList(): Return True" << endl;
    #endif
    return true;
}

