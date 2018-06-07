#include <Modules/calibration/settings/SettingsCalibStereo.h>

SettingsCalibStereo::SettingsCalibStereo(){
    displayCorners = false;
    useCalibrated = true;
    showRectified = true;
    cameraLeftID = 0;
    cameraRightID = 1;
}

SettingsCalibStereo::~SettingsCalibStereo(){

}

/**
 * @brief This function reads the xml file and fullfill the class variables
 * @param fileLocation
 * @return void
 * @author Lluchiari
 */
int SettingsCalibStereo::read(string fileLocation)
{
   if(LOG_SETTINGS_CALIB_STEREO){cout << "SettingsCalibStereo::read(): Starting...\n";}
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement *aux;
    if(doc.LoadFile(fileLocation.c_str()) != tinyxml2::XMLError::XML_SUCCESS){
        cerr << "SettingsCalibStereo::read: Error on loaing xml file!";
        return -1;
    }

    aux = doc.FirstChildElement("opencv_storage");
    if(aux == NULL){cerr << "SettingsCalibStereo::read(): Error on xml file! 'opencv_storage' tag could not be found!\n" ;return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings");
    if(aux == NULL){cerr << "SettingsCalibStereo::read(): Error on xml file! 'Settings' tag could not be found!\n" ;return -1;}

    this->systemName = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->Attribute("sys_name");

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("BoardSize_Width");
    if(aux != NULL){this->boardSize.width =  std::atoi(aux->GetText());} else {cerr << "SettingsCalibStereo()::read(): Error on BoardSize_Width\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("BoardSize_Height");
    if(aux != NULL){this->boardSize.height = std::atoi(aux->GetText());} else {cerr << "SettingsCalibStereo()::read(): Error on BoardSize_Height\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Calibrate_Pattern");
    if(aux != NULL){this->patternToUse = aux->GetText();} else {cerr << "SettingsCalibStereo()::read(): Error on Calibrate_Pattern\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Square_Size");
    if(aux != NULL){this->squareSize = (float) std::atof(aux->GetText());} else {cerr << "SettingsCalibStereo()::read(): Error on Square_Size\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Display_Corner");
    if(aux != NULL){this->displayCorners = std::atoi(aux->GetText());} else {cerr << "SettingsCalibStereo()::read(): Error on Display_Corner\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Use_Calibrated");
    if(aux != NULL){this->useCalibrated = std::atoi(aux->GetText());} else {cerr << "SettingsCalibStereo()::read(): Error on Use_Calibrated\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Show_Rectified");
    if(aux != NULL){this->showRectified = std::atoi(aux->GetText());} else {cerr << "SettingsCalibStereo()::read(): Error on Show_Rectified\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Input");
    if(aux != NULL){this->input = aux->GetText();} else {cerr << "SettingsCalibStereo()::read(): Error on Input\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Output_Camera_FileName");
    if(aux != NULL){this->outputCameraFilename = aux->GetText();} else {cerr << "SettingsCalibStereo()::read(): Error on Output_Camera_FileName\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Output_Intrinsic_FileName");
    if(aux != NULL){this->outputIntrinsicFilename = aux->GetText();} else {cerr << "SettingsCalibStereo()::read(): Error on Output_Intrinsic_FileName\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Output_Extrinsic_FileName");
    if(aux != NULL){this->outputExtrinsicFilename = aux->GetText();} else {cerr << "SettingsCalibStereo()::read(): Error on Output_Extrinsic_FileName\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Show_UndistortedImage");
    if(aux != NULL){this->showUndistorsed = std::atoi(aux->GetText());} else {cerr << "SettingsCalibStereo()::read(): Error on Show_UndistortedImage\n"; return -1;}

    if(LOG_SETTINGS_CALIB_STEREO){cout << "SettingsCalibStereo::read(): Finish_OK!\n";}
    return 0;
}

/**
 * @brief SettingsCalibStereo::interprate Interprate the input files and fill all the class required information for calibration
 * @author OpenCV
 */
int SettingsCalibStereo::interprate(){
    if(LOG_SETTINGS_CALIB_STEREO){cout << "SettingsCalibStereo::interprate(): Starting...\n";}

    // Check the input variable //
    if (this->input.empty())
    {
        #if DEBUG_SETTINGS_CALIB_STEREO
            cout << "SettingsCalibStereo::interprate(): Input is Empty!" << endl;
        #endif

        this->inputType = consts::INVALID;
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

            if(DEBUG_CALIB_STEREO){
                cout << "CameraRightID: " << cameraRightID << "\n";
                cout << "CameraLeftID: " << cameraLeftID << "\n";
            }
        }
        else
        {
            // If the input is the IMAGE LIST case
            if (_isListOfImages(this->input) && _readStringList(this->input, this->imageList))
            {
                #if DEBUG_SETTINGS_CALIB_STEREO
                    cout << "SettingsCalibStereo::interprate(): IMAGE_LIST mode " << endl;
                #endif
                this->inputType = consts::IMAGE_LIST;
                //this->nrFrames = (this->nrFrames < (int)imageList.size()) ? this->nrFrames : (int)imageList.size();
                //                if(DEBUG_SETTINGS_STEREO){cout << "SettingsCalibStereo::interprate(): Number of Frames: " << this->nrFrames<< endl;}
            }
            // If the input is the VIDEO FILE case
            else {
                #if DEBUG_SETTINGS_CALIB_STEREO
                    cout << "SettingsCalibStereo::interprate(): VIDEO_FILE mode " << endl;
                #endif
                this->inputType = consts::VIDEO_FILE;
            }
        }

//        if (this->inputType == consts::CAMERA){
//            #if DEBUG_SETTINGS_CALIB_STEREO
//                cout << "SettingsCalibStereo::interprate(): CAMERA open mode " << endl;
//            #endif
//        }
//        if (this->inputType == consts::VIDEO_FILE){
//            #if DEBUG_SETTINGS_CALIB_STEREO
//                cout << "SettingsCalibStereo::interprate(): VIDEO_FILE open mode " << endl;
//            #endif
//            //            this->inputCapture.open(input);
//        }
    }

    // Board Size Check //
    if(boardSize.empty()){
        cerr << "SettingsCalibStereo::interprate(): Error! Board Size not informed on config file, or some other error related! Please check this again!\n";
        return -1;
    }

    if(LOG_SETTINGS_CALIB_STEREO){cout << "SettingsCalibStereo::interprate(): Finish_OK!\n";}
    return 0;
}

/**
 * @brief SettingsStereo::isListOfImages look for the xml file
 * @param filename is the name (complete path) of the xml file
 * @return true if there is a file like filename, otherwise false
 * @author OpenCV Library
 */
bool SettingsCalibStereo::_isListOfImages( const string& filename)
{
    string s(filename);
    #if DEBUG_SETTINGS_CALIB_STEREO
        cout << "SettingsCalibStereo::isListOfImages(): String Name:"<< s << endl;
    #endif
    // Look for file extension
    if( s.find(".xml") == string::npos && s.find(".yaml") == string::npos && s.find(".yml") == string::npos )
    {
        cerr << "SettingsCalibStereo::isListOfImages(): File extension is incorrect!" << endl;
        return false;
    }
    else{
        #if DEBUG_SETTINGS_CALIB_STEREO
            cout << "SettingsCalibStereo::isListOfImages(): Return True" << endl;
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
bool SettingsCalibStereo::_readStringList( const string& filename, vector<string>& l )
{
    l.clear();
    FileStorage fs(filename, FileStorage::READ);
    if( !fs.isOpened() ){
        cerr << "SettingsStereo::readStringList: Error on opening Stacks File" << endl;
        return false;
    }
    FileNode n = fs.getFirstTopLevelNode();
    if( n.type() != FileNode::SEQ ){
        cerr << "SettingsStereo::readStringList: Error! Incorrect Syntax on file or File is not a sequence." << endl;
        return false;
    }
    FileNodeIterator it = n.begin(), it_end = n.end();
    for( ; it != it_end; ++it ){
        l.push_back((string)*it);
    }
    #if DEBUG_SETTINGS_CALIB_STEREO
        cout << "SettingsStereo::readStringList(): Return True" << endl;
    #endif
    return true;
}



int SettingsCalibStereo::print(){
    if(LOG_SETTINGS_CALIB_STEREO){cout << "SettingsStereo::print(): Start printing...\n";}
    cout << "Image List:\t";
    for(int i=0; i < this->imageList.size(); i++)
    {
        if(i==0) cout << this->imageList.at(i) << "\n";
        else cout << "\t\t" << this->imageList.at(i) << "\n";
    }
    cout << "boardSize.width: " << this->boardSize.width << std::endl
    << "boardSize.height: " << this->boardSize.height << std::endl
    << "patternToUse: " << this->patternToUse << std::endl
    << "squareSize: " << this->squareSize << std::endl
    << "displayCorners_flag: " << this->displayCorners << std::endl
    << "useCalibrated_flag: " << this->useCalibrated << std::endl
    << "showRectified_flag: " << this->showRectified << std::endl
    << "showUndistorsed: " << this->showUndistorsed << std::endl
    << "input: " << this->input << std::endl
    << "outputExtrinsicFilename: " << this->outputExtrinsicFilename << std::endl
    << "outputIntrinsicFilename: " << this->outputIntrinsicFilename << std::endl
    << "InputType: ";

    switch(this->inputType){
        case INVALID:
            cout << "INVALID\n";
            break;
        case CAMERA:
            cout << "CAMERA\n";
            break;
        case VIDEO_FILE:
            cout << "VIDEO_FILE\n";
            break;
        case IMAGE_LIST:
            cout << "IMAGE_LIST\n";
            break;
    };
    cout << "CameraLeftID: " << this->cameraLeftID  << std::endl;
    cout << "CameraRightID: " << this->cameraRightID  << std::endl;


    if(LOG_SETTINGS_CALIB_STEREO){cout << "SettingsStereo::print(): Finish_OK!\n";}
    return 0;
}
