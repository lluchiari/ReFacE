#include <calibration/settings/SettingsCalibStereo.h>

SettingsCalibStereo::SettingsCalibStereo(){
    _displayCorners = false;
    _useCalibrated = true;
    _showRectified = true;
    _cameraID = 0;
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
    if(doc.LoadFile(fileLocation.c_str()) != tinyxml2::XMLError::XML_SUCCESS){
        cerr << "SettingsCalibStereo::read: Error on loaing xml file!";
        return -1;
    }

    this->_boardSize.width = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("BoardSize_Width")->GetText());
    this->_boardSize.height = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("BoardSize_Height")->GetText());
    this->_patternToUse = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Calibrate_Pattern")->GetText();
    this->_squareSize = (float) std::atof(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Square_Size")->GetText());
    this->_displayCorners = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Display_Corner")->GetText());
    this->_useCalibrated = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Use_Calibrated")->GetText());
    this->_showRectified = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Show_Rectified")->GetText());
    this->_input = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Input")->GetText();
    this->outputFileName = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Write_outputFileName")->GetText();
    this->_showUndistorsed = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Show_UndistortedImage")->GetText());

    if(LOG_SETTINGS_CALIB_STEREO){cout << "SettingsCalibStereo::read(): Finish_OK!\n";}
    return 0;
}

/**
 * @brief SettingsCalibStereo::interprate Interprate the input files and fill all the class required information for calibration
 * @author OpenCV
 */
int SettingsCalibStereo::interprate(){
    if(LOG_SETTINGS_CALIB_STEREO){cout << "SettingsCalibStereo::interprate(): Starting...\n";}

    if (this->_input.empty())
    {
        #if DEBUG_SETTINGS_CALIB_STEREO
            cout << "SettingsCalibStereo::interprate(): Input is Empty!" << endl;
        #endif

        this->_inputType = consts::INVALID;
        return -1;
    }
    else
    {
        // In the CAMERA case. Idicates the ID of the camera.
        if (this->_input[0] >= '0' && this->_input[0] <= '9')
        {
            #if DEBUG_SETTINGS_CALIB_STEREO
                cout << "SettingsCalibStereo::interprate(): CAMERA Case" << endl;
            #endif
            stringstream ss(this->_input);
            ss >> this->_cameraID;
            this->_inputType = consts::CAMERA;
        }
        else
        {
            // If the input is the IMAGE LIST case
            if (_isListOfImages(this->_input) && _readStringList(this->_input, this->_imageList))
            {
                #if DEBUG_SETTINGS_CALIB_STEREO
                    cout << "SettingsCalibStereo::interprate(): IMAGE_LIST mode " << endl;
                #endif
                this->_inputType = consts::IMAGE_LIST;
                //this->nrFrames = (this->nrFrames < (int)imageList.size()) ? this->nrFrames : (int)imageList.size();
                //                if(DEBUG_SETTINGS_STEREO){cout << "SettingsCalibStereo::interprate(): Number of Frames: " << this->nrFrames<< endl;}
            }
            // If the input is the VIDEO FILE case
            else {
                #if DEBUG_SETTINGS_CALIB_STEREO
                    cout << "SettingsCalibStereo::interprate(): VIDEO_FILE mode " << endl;
                #endif
                this->_inputType = consts::VIDEO_FILE;
            }
        }
        if (this->_inputType == consts::CAMERA){
            #if DEBUG_SETTINGS_CALIB_STEREO
                cout << "SettingsCalibStereo::interprate(): CAMERA open mode " << endl;
            #endif
            //            this->inputCapture.open(this->cameraID);
        }
        if (this->_inputType == consts::VIDEO_FILE){
            #if DEBUG_SETTINGS_CALIB_STEREO
                cout << "SettingsCalibStereo::interprate(): VIDEO_FILE open mode " << endl;
            #endif
            //            this->inputCapture.open(input);
        }
        if (this->_inputType != consts::IMAGE_LIST && !this->_inputCapture.isOpened()){
            #if DEBUG_SETTINGS_CALIB_STEREO
                cout << "SettingsCalibStereo::interprate(): INVALID mode! Error on opening the Camera System! " << endl;
            #endif
            this->_inputType = consts::INVALID;
            return -1;
        }
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
    for(int i=0; i < this->_imageList.size(); i++)
    {
        if(i==0) cout << this->_imageList.at(i) << "\n";
        else cout << "\t\t" << this->_imageList.at(i) << "\n";
    }
    cout << "boardSize.width: " << this->_boardSize.width << std::endl
    << "boardSize.height: " << this->_boardSize.height << std::endl
    << "patternToUse: " << this->_patternToUse << std::endl
    << "squareSize: " << this->_squareSize << std::endl
    << "displayCorners_flag: " << this->_displayCorners << std::endl
    << "useCalibrated_flag: " << this->_useCalibrated << std::endl
    << "showRectified_flag: " << this->_showRectified << std::endl
    << "showUndistorsed: " << this->_showUndistorsed << std::endl
    << "input: " << this->_input << std::endl
    << "outputFileName: " << this->outputFileName << std::endl
    << "InputType: ";

    switch(this->_inputType){
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
    cout << "CameraID: " << this->_cameraID  << std::endl;


    if(LOG_SETTINGS_CALIB_STEREO){cout << "SettingsStereo::print(): Finish_OK!\n";}
    return 0;
}
