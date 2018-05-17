#include <Settings/SettingsSingle.h>

//void SettingsSingle::write(SETTING_STORAGE& fs) const
//{
//    fs << "{" << "BoardSize_Width"  << this->boardSize.width
//       << "BoardSize_Height" << this->boardSize.height
//       << "Square_Size"         << this->squareSize
//       << "Calibrate_Pattern" << this->_patternToUse
//       << "Calibrate_NrOfFrameToUse" << this->nrFrames
//       << "Calibrate_FixAspectRatio" << this->aspectRatio
//       << "Calibrate_AssumeZeroTangentialDistortion" << this->calibZeroTangentDist
//       << "Calibrate_FixPrincipalPointAtTheCenter" << this->calibFixPrincipalPoint

//       << "Write_DetectedFeaturePoints" << this->bwritePoints
//       << "Write_extrinsicParameters"   << this->bwriteExtrinsics
//       << "Write_outputFileName"  << this->outputFileName

//       << "Show_UndistortedImage" << this->showUndistorsed

//       << "Input_FlipAroundHorizontalAxis" << this->flipVertical
//       << "Input_Delay" << this->delay
//       << "Input" << this->input
//       << "}";
//}

//void SettingsSingle::read(const SETTING_NODE
//                    & node)
//{
//    node["BoardSize_Width" ] >> this->boardSize.width;
//    node["BoardSize_Height"] >> this->boardSize.height;
//    node["Calibrate_Pattern"] >> this->_patternToUse;
//    node["Square_Size"]  >> this->squareSize;
//    node["Calibrate_NrOfFrameToUse"] >> this->nrFrames;
//    node["Calibrate_FixAspectRatio"] >> this->aspectRatio;
//    node["Write_DetectedFeaturePoints"] >> this->bwritePoints;
//    node["Write_extrinsicParameters"] >> this->bwriteExtrinsics;
//    node["Write_outputFileName"] >> this->outputFileName;
//    node["Calibrate_AssumeZeroTangentialDistortion"] >> this->calibZeroTangentDist;
//    node["Calibrate_FixPrincipalPointAtTheCenter"] >> this->calibFixPrincipalPoint;
//    node["Input_FlipAroundHorizontalAxis"] >> this->flipVertical;
//    node["Show_UndistortedImage"] >> this->showUndistorsed;
//    node["Input"] >> this->input;
//    node["Input_Delay"] >> this->delay;
//    interprate();
//}

///**
// * @brief This function reads the xml file and fullfill the class variables
// * @param fileLocation
// */
//void SettingsSingle::read(string fileLocation)
//{
//    this->boardSize.width = 9;
//    this->boardSize.height = 6;
//    this->_patternToUse = "CHESSBOARD";
//    this->squareSize = 50;
//    this->nrFrames = 7;
//    this->aspectRatio = 1;
//    this->bwritePoints = 1;
//    this->bwriteExtrinsics = 1;
//    //this->outputFileName = outFileLocation;
//    this->calibZeroTangentDist = 1;
//    this->calibFixPrincipalPoint = 1;
//    this->flipVertical = 0;
//    this->showUndistorsed = 1;
//    this->input = fileLocation;
//    this->delay = 100;
//}

/**
 * @brief This function reads the xml file and fullfill the class variables
 * @param fileLocation
 */
void SettingsSingle::read(string fileLocation)
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile(fileLocation.c_str());

    this->boardSize.width = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("BoardSize_Width")->GetText());
    this->boardSize.height = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("BoardSize_Height")->GetText());
    this->_patternToUse = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Calibrate_Pattern")->GetText();
    this->squareSize = (float) std::atof(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Square_Size")->GetText());
    this->nrFrames = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Calibrate_NrOfFrameToUse")->GetText());
    this->aspectRatio = (float) std::atof(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Calibrate_FixAspectRatio")->GetText());
    this->bwritePoints = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Write_DetectedFeaturePoints")->GetText());
    this->bwriteExtrinsics = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Write_extrinsicParameters")->GetText());
    this->outputFileName = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Write_outputFileName")->GetText();
    this->calibZeroTangentDist = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Calibrate_AssumeZeroTangentialDistortion")->GetText());
    this->calibFixPrincipalPoint = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Calibrate_FixPrincipalPointAtTheCenter")->GetText());
    this->flipVertical = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Input_FlipAroundHorizontalAxis")->GetText());
    this->showUndistorsed = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Show_UndistortedImage")->GetText());
    this->input = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Input")->GetText();
    this->delay = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Input_Delay")->GetText());
}

void SettingsSingle::setStackImage(string stackFileLocation){
    if(DEBUG_SETTINGS){cout << "SettingsSingle::setStackImage(): File: " << stackFileLocation << endl;}
    this->input = stackFileLocation;
}

void SettingsSingle::setOutputFile(string outFileLocation){
    if(DEBUG_SETTINGS){cout << "SettingsSingle::setOutputFile(): File: " << outFileLocation << endl;}
    this->outputFileName = outFileLocation;
}

/**
 * @brief This function interprate the configure file given and check for errors
 *
 */
void SettingsSingle::interprate()
{
    this->goodInput = true;
    if (this->boardSize.width <= 0 || this->boardSize.height <= 0)
    {
        cerr << "Invalid Board size: " << this->boardSize.width << " " << this->boardSize.height << endl;
        this->goodInput = false;
    }
    if (this->squareSize <= 10e-6)
    {
        cerr << "Invalid square size " << squareSize << endl;
        this->goodInput = false;
    }
    if (this->nrFrames <= 0)
    {
        cerr << "Invalid number of frames! Fix you configuration file " << this->nrFrames << endl;
        this->goodInput = false;
    }
    if (this->input.empty())
    {
        if(DEBUG_SETTINGS){cout << "SettingsSingle::interprate(): Input is Empty!" << endl;}
        this->inputType = INVALID;
    }
    else
    {
        // In the CAMERA case. Idicates the ID of the camera.
        if (this->input[0] >= '0' && this->input[0] <= '9')
        {
            if(DEBUG_SETTINGS){cout << "SettingsSingle::interprate(): CAMERA Case" << endl;}
            stringstream ss(this->input);
            ss >> this->cameraID;
            this->inputType = CAMERA;
        }
        else
        {
            if (isListOfImages(this->input) && readStringList(this->input, this->imageList))
            {
                if(DEBUG_SETTINGS){cout << "SettingsSingle::interprate(): IMAGE_LIST mode " << endl;}
                inputType = IMAGE_LIST;
                this->nrFrames = (this->nrFrames < (int)imageList.size()) ? this->nrFrames : (int)imageList.size();
                if(DEBUG_SETTINGS){cout << "SettingsSingle::interprate(): Number of Frames: " << this->nrFrames<< endl;}
            }
            else {
                if(DEBUG_SETTINGS){cout << "SettingsSingle::interprate(): VIDEO_FILE mode " << endl;}
                inputType = VIDEO_FILE;
            }
        }
        if (inputType == CAMERA){
            if(DEBUG_SETTINGS){cout << "SettingsSingle::interprate(): CAMERA open mode " << endl;}
            this->inputCapture.open(this->cameraID);
        }
        if (inputType == VIDEO_FILE){
            if(DEBUG_SETTINGS){cout << "SettingsSingle::interprate(): VIDEO_FILE open mode " << endl;}
            this->inputCapture.open(input);
        }
        if (inputType != IMAGE_LIST && !this->inputCapture.isOpened()){
            if(DEBUG_SETTINGS){cout << "SettingsSingle::interprate(): INVALID !IMAGE_LIST mode " << endl;}
            inputType = INVALID;
        }
    }
    if (inputType == INVALID)
    {
        if(DEBUG_SETTINGS){cout << "SettingsSingle::interprate(): INVALID mode " << endl;}
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
}

Mat SettingsSingle::nextImage(){
    Mat result;
    if( this->inputCapture.isOpened() )
    {
        if(DEBUG_SETTINGS){cout << "SettingsSingle::nextImage(): 1 " << endl;}
        Mat view0;
        this->inputCapture >> view0;

        //TODO: is this really necessary? Cab I copy strait to the result
        view0.copyTo(result);
    }
    else if( this->atImageList < (int)this->imageList.size() )
    {
        if(DEBUG_SETTINGS){
            cout << "SettingsSingle::nextImage(): Reading Image " << this->imageList[this->atImageList] << endl;
        }
        result = imread(this->imageList[this->atImageList++], CV_LOAD_IMAGE_COLOR);
    }
    return result;
}

bool SettingsSingle::readStringList( const string& filename, vector<string>& l )
{
    l.clear();
    SETTING_STORAGE fs(filename, SETTING_STORAGE::READ);
    if( !fs.isOpened() ){
        cerr << "SettingsSingle::readStringList: Error on opening Stacks File" << endl;
        return false;
    }
    SETTING_NODE n = fs.getFirstTopLevelNode();
    if( n.type() != SETTING_NODE::SEQ ){
        cerr << "SettingsSingle::readStringList: Error! Incorrect Syntax on file or File is not a sequence." << endl;
        return false;
    }
    SETTING_NODE_ITERATOR it = n.begin(), it_end = n.end();
    for( ; it != it_end; ++it ){
        l.push_back((string)*it);
    }
    if(DEBUG_SETTINGS){cout << "SettingsSingle::readStringList(): Return True" << endl;}
    return true;
}

bool SettingsSingle::isListOfImages( const string& filename)
{
    string s(filename);
    if(DEBUG_SETTINGS){cout << "SettingsSingle::isListOfImages(): String Name:"<< s << endl;}
    // Look for file extension
    if( s.find(".xml") == string::npos && s.find(".yaml") == string::npos && s.find(".yml") == string::npos )
    {
        cerr << "SettingsSingle::isListOfImages(): File extension is incorrect!" << endl;
        return false;
    }
    else{
        if(DEBUG_SETTINGS){cout << "SettingsSingle::isListOfImages(): Return True" << endl;}
        return true;
    }
}

void SettingsSingle::print(){
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
}
