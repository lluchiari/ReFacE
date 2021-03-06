#include <Modules/calibration/settings/SettingsCalibSingle.h>

/**
 * @brief This function reads the xml file and fullfill the class variables
 * @param fileLocation
 */
int SettingsCalibSingle::read(string fileLocation)
{
    if(LOG_SETTINGS_CALIB_SINGLE){cout << "SettingsCalibSingle::read(): Starting...\n";}

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement *aux;
    if(doc.LoadFile(fileLocation.c_str()) != tinyxml2::XMLError::XML_SUCCESS){
        cerr << "SettingsCalibSingle::read: Error on reading the xml file!\n";
    }

    aux = doc.FirstChildElement("opencv_storage");
    if(aux == NULL){cerr << "SettingsCalibSingle::read(): Error on xml file! 'opencv_storage' tag could not be found!\n" ;return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings");
    if(aux == NULL){cerr << "SettingsCalibSingle::read(): Error on xml file! 'Settings' tag could not be found!\n" ;return -1;}

    this->systemName = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->Attribute("sys_name");

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("BoardSize_Width");
    if(aux != NULL){this->boardSize.width =  std::atoi(aux->GetText());} else {cerr << "SettingsCalibSingle()::read(): Error on BoardSize_Width\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("BoardSize_Height");
    if(aux != NULL){this->boardSize.height =  std::atoi(aux->GetText());} else {cerr << "SettingsCalibSingle()::read(): Error on BoardSize_Width\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Calibrate_Pattern");
    if(aux != NULL){this->_patternToUse =  aux->GetText();} else {cerr << "SettingsCalibSingle()::read(): Error on Calibrate_Pattern\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Square_Size");
    if(aux != NULL){this->squareSize =  (float) std::atof(aux->GetText());} else {cerr << "SettingsCalibSingle()::read(): Error on Square_Size\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Calibrate_NrOfFrameToUse");
    if(aux != NULL){this->nrFrames =  std::atoi(aux->GetText());} else {cerr << "SettingsCalibSingle()::read(): Error on Calibrate_NrOfFrameToUse\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Calibrate_FixAspectRatio");
    if(aux != NULL){this->aspectRatio =  (float) std::atof(aux->GetText());} else {cerr << "SettingsCalibSingle()::read(): Error on Calibrate_FixAspectRatio\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Write_DetectedFeaturePoints");
    if(aux != NULL){this->bwritePoints =  std::atoi(aux->GetText());} else {cerr << "SettingsCalibSingle()::read(): Error on Write_DetectedFeaturePoints\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Write_extrinsicParameters");
    if(aux != NULL){this->bwriteExtrinsics =  std::atoi(aux->GetText());} else {cerr << "SettingsCalibSingle()::read(): Error on Write_extrinsicParameters\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Write_outputFileName");
    if(aux != NULL){this->outputFileName =  aux->GetText();} else {cerr << "SettingsCalibSingle()::read(): Error on Write_outputFileName\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Calibrate_AssumeZeroTangentialDistortion");
    if(aux != NULL){this->calibZeroTangentDist = std::atoi(aux->GetText());} else {cerr << "SettingsCalibSingle()::read(): Error on Calibrate_AssumeZeroTangentialDistortion\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Calibrate_FixPrincipalPointAtTheCenter");
    if(aux != NULL){this->calibFixPrincipalPoint = std::atoi(aux->GetText());} else {cerr << "SettingsCalibSingle()::read(): Error on Calibrate_FixPrincipalPointAtTheCenter\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Input_FlipAroundHorizontalAxis");
    if(aux != NULL){this->flipVertical = std::atoi(aux->GetText());} else {cerr << "SettingsCalibSingle()::read(): Error on Input_FlipAroundHorizontalAxis\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Show_UndistortedImage");
    if(aux != NULL){this->showUndistorsed = std::atoi(aux->GetText());} else {cerr << "SettingsCalibSingle()::read(): Error on Show_UndistortedImage\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Input");
    if(aux != NULL){this->input = aux->GetText();} else {cerr << "SettingsCalibSingle()::read(): Error on Input\n"; return -1;}

    aux = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Input_Delay");
    if(aux != NULL){this->delay = std::atoi(aux->GetText());} else {cerr << "SettingsCalibSingle()::read(): Error on Input_Delay\n"; return -1;}

    if(LOG_SETTINGS_CALIB_SINGLE){cout << "SettingsCalibSingle::read(): Finish_OK!\n";}
    return 0;
}

void SettingsCalibSingle::setStackImage(string stackFileLocation){
    #if DEBUG_SETTINGS_CALIB_SINGLE
        cout << "SettingsCalibSingle::setStackImage(): Starting Stack File: '" << stackFileLocation << "'" << endl;
    #endif
    this->input = stackFileLocation;
}

void SettingsCalibSingle::setOutputFile(string outFileLocation){
     #if DEBUG_SETTINGS_CALIB_SINGLE
        cout << "SettingsCalibSingle::setOutputFile(): File: " << outFileLocation << endl;
    #endif
    this->outputFileName = outFileLocation;
}

/**
 * @brief SettingsCalibSingle::interprate interprate the configure file given and check for errors
 * @author OpenCV
 */
int SettingsCalibSingle::interprate()
{
    if(LOG_SETTINGS_CALIB_SINGLE){cout << "SettingsCalibSingle::interprate(): Starting...\n";}
    this->goodInput = true;
    if (this->boardSize.width <= 0 || this->boardSize.height <= 0)
    {
        cerr << "Invalid Board size: " << this->boardSize.width << " " << this->boardSize.height << endl;
        this->goodInput = false;
        return -1;
    }
    if (this->squareSize <= 10e-6)
    {
        cerr << "Invalid square size " << squareSize << endl;
        this->goodInput = false;
        return -1;
    }
    if (this->nrFrames <= 0)
    {
        cerr << "Invalid number of frames! Fix you configuration file " << this->nrFrames << endl;
        this->goodInput = false;
        return -1;
    }
    if (this->input.empty())
    {
        #if(DEBUG_SETTINGS_SINGLE)
            cout << "SettingsCalibSingle::interprate(): Input is Empty!" << endl;
        #endif
        this->inputType = consts::INVALID;
        return -1;
    }
    else
    {
        // In the CAMERA case. Idicates the ID of the camera.
        if (this->input[0] >= '0' && this->input[0] <= '9')
        {
             #if(DEBUG_SETTINGS_SINGLE)
                cout << "SettingsCalibSingle::interprate(): CAMERA Case" << endl;
            #endif
            stringstream ss(this->input);
            ss >> this->cameraID;
            this->inputType = consts::CAMERA;
        }
        else
        {
            if (isListOfImages(this->input) && readStringList(this->input, this->imageList))
            {
                 #if(DEBUG_SETTINGS_SINGLE)
                    cout << "SettingsCalibSingle::interprate(): IMAGE_LIST mode " << endl;
                 #endif
                inputType = consts::IMAGE_LIST;
                this->nrFrames = (this->nrFrames < (int)imageList.size()) ? this->nrFrames : (int)imageList.size();
                 #if(DEBUG_SETTINGS_SINGLE)
                    cout << "SettingsCalibSingle::interprate(): Number of Frames: " << this->nrFrames<< endl;
                #endif
            }
            else {
                 #if(DEBUG_SETTINGS_SINGLE)
                    cout << "SettingsCalibSingle::interprate(): VIDEO_FILE mode " << endl;
                 #endif
                inputType = consts::VIDEO_FILE;
            }
        }
        if (inputType == consts::CAMERA){
             #if(DEBUG_SETTINGS_SINGLE)
                cout << "SettingsCalibSingle::interprate(): CAMERA open mode " << endl;
            #endif
            this->inputCapture.open(this->cameraID);
        }
        if (inputType == consts::VIDEO_FILE){
             #if(DEBUG_SETTINGS_SINGLE)
                cout << "SettingsCalibSingle::interprate(): VIDEO_FILE open mode " << endl;
            #endif
            this->inputCapture.open(input);
        }
        if (inputType != consts::IMAGE_LIST && !this->inputCapture.isOpened()){
             #if(DEBUG_SETTINGS_SINGLE)
                cout << "SettingsCalibSingle::interprate(): INVALID !IMAGE_LIST mode " << endl;
            #endif
            inputType = consts::INVALID;
            return -1;
        }
    }
    if (inputType == consts::INVALID)
    {
         #if(DEBUG_SETTINGS_SINGLE)
            cout << "SettingsCalibSingle::interprate(): INVALID mode " << endl;
        #endif
        cerr << " Inexistent input: " << "'" << input << "'" << endl;
        goodInput = false;
    }

    this->flag = 0;
    if(this->calibFixPrincipalPoint) this->flag |= CV_CALIB_FIX_PRINCIPAL_POINT;
    if(this->calibZeroTangentDist)   this->flag |= CV_CALIB_ZERO_TANGENT_DIST;
    if(this->aspectRatio)            this->flag |= CV_CALIB_FIX_ASPECT_RATIO;



    // Chosing the kind of calibration pattern to be used
    this->calibrationPattern = NOT_EXISTING;
    if (!this->_patternToUse.compare("CHESSBOARD")) this->calibrationPattern = CHESSBOARD;
    if (!this->_patternToUse.compare("CIRCLES_GRID")) this->calibrationPattern = CIRCLES_GRID;
    if (!this->_patternToUse.compare("ASYMMETRIC_CIRCLES_GRID")) this->calibrationPattern = ASYMMETRIC_CIRCLES_GRID;
    if (this->calibrationPattern == NOT_EXISTING)
    {
        cerr << " Inexistent camera calibration pattern: " << "'" << this->_patternToUse << "'"<< endl;
        this->goodInput = false;
    }
    this->atImageList = 0;

    if(LOG_SETTINGS_CALIB_SINGLE){cout << "SettingsCalibSingle::interprate(): Finish_OK!\n";}
    return 0;
}

Mat SettingsCalibSingle::nextImage(){
    Mat result;
    if( this->inputCapture.isOpened() )
    {
         #if(DEBUG_SETTINGS_SINGLE)
            cout << "SettingsCalibSingle::nextImage(): 1 " << endl;
        #endif
        Mat view0;
        this->inputCapture >> view0;

        //TODO: is this really necessary? Cab I copy strait to the result
        view0.copyTo(result);
    }
    else if( this->atImageList < (int)this->imageList.size() )
    {
         #if(DEBUG_SETTINGS_SINGLE)
            cout << "SettingsCalibSingle::nextImage(): Reading Image " << this->imageList[this->atImageList] << endl;
        #endif
        result = imread(this->imageList[this->atImageList++], CV_LOAD_IMAGE_COLOR);
    }
    return result;
}

/**
 * @brief SettingsCalibSingle::_readStringList Read the xml file containing the list of images
 * @param filename is the path of the xml file
 * @param l is the list where the images will be saved
 * @return true if everything is ok. False otherwise
 * @author OpenCV Library
 */
bool SettingsCalibSingle::readStringList( const string& filename, vector<string>& l )
{
    l.clear();
    FileStorage fs(filename, FileStorage::READ);
    if( !fs.isOpened() ){
        cerr << "SettingsCalibSingle::readStringList: Error on opening Stacks File" << endl;
        return false;
    }
    FileNode n = fs.getFirstTopLevelNode();
    if( n.type() != FileNode::SEQ ){
        cerr << "SettingsCalibSingle::readStringList: Error! Incorrect Syntax on file or File is not a sequence." << endl;
        return false;
    }
    FileNodeIterator it = n.begin(), it_end = n.end();
    for( ; it != it_end; ++it ){
        l.push_back((string)*it);
    }
    #if DEBUG_SETTINGS_SINGLE
        cout << "SettingsCalibSingle::readStringList(): Return True" << endl;
    #endif
    return true;
}

/**
 * @brief SettingsCalibSingle::isListOfImages look for the xml file
 * @param filename is the name (complete path) of the xml file
 * @return true if there is a file like filename, otherwise false
 * @author OpenCV Library
 */
bool SettingsCalibSingle::isListOfImages( const string& filename)
{
    string s(filename);
    #if(DEBUG_SETTINGS_SINGLE)
        cout << "SettingsCalibSingle::isListOfImages(): String Name:"<< s << endl;
    #endif
    // Look for file extension
    if( s.find(".xml") == string::npos && s.find(".yaml") == string::npos && s.find(".yml") == string::npos )
    {
        cerr << "SettingsCalibSingle::isListOfImages(): File extension is incorrect!" << endl;
        return false;
    }
    else{
        #if(DEBUG_SETTINGS_SINGLE)
            cout << "SettingsCalibSingle::isListOfImages(): Return True" << endl;
        #endif
        return true;
    }
}

int SettingsCalibSingle::print(){
    cout << "Print:\n"
    << "boardSize.width: " << this->boardSize.width << std::endl
    << "boardSize.height: " << this->boardSize.height << std::endl
    << "_patternToUse: " << this->_patternToUse << std::endl
    << "squareSize: " << this->squareSize << std::endl
    << "nrFrames: " << this->nrFrames  << std::endl
    << "aspectRatio: " << this->aspectRatio << std::endl
    << "bwritePoints: " << this->bwritePoints << std::endl
    << "bwriteExtrinsics: " << this->bwriteExtrinsics << std::endl
    << "outputFileName: " << this->outputFileName << std::endl
    << "calibZeroTangentDist: " << this->calibZeroTangentDist << std::endl
    << "calibFixPrincipalPoint: " << this->calibFixPrincipalPoint << std::endl
    << "flipVertical: " << this->flipVertical << std::endl
    << "showUndistorsed: " << this->showUndistorsed << std::endl
    << "input: " << this->input << std::endl
    << "delay: " << this->delay << std::endl;
    return 0;
}
