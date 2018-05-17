#include <Settings/SettingsStereo.h>

SettingsStereo::SettingsStereo(){

}

SettingsStereo::~SettingsStereo(){

}

/**
 * @brief This function reads the xml file and fullfill the class variables
 * @param fileLocation
 */
void SettingsStereo::read(string fileLocation)
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile(fileLocation.c_str());

    this->boardSize.width = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("BoardSize_Width")->GetText());
    this->boardSize.height = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("BoardSize_Height")->GetText());
    this->_patternToUse = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Calibrate_Pattern")->GetText();
    this->squareSize = (float) std::atof(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Square_Size")->GetText());
//    this->nrFrames = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Calibrate_NrOfFrameToUse")->GetText());
//    this->aspectRatio = (float) std::atof(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Calibrate_FixAspectRatio")->GetText());
//    this->bwritePoints = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Write_DetectedFeaturePoints")->GetText());
//    this->bwriteExtrinsics = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Write_extrinsicParameters")->GetText());
    this->outputFileName = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Write_outputFileName")->GetText();
//    this->calibZeroTangentDist = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Calibrate_AssumeZeroTangentialDistortion")->GetText());
//    this->calibFixPrincipalPoint = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Calibrate_FixPrincipalPointAtTheCenter")->GetText());
//    this->flipVertical = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Input_FlipAroundHorizontalAxis")->GetText());
    this->showUndistorsed = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Show_UndistortedImage")->GetText());
    this->input = doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Input")->GetText();
//    this->delay = std::atoi(doc.FirstChildElement("opencv_storage")->FirstChildElement("Settings")->FirstChildElement("Input_Delay")->GetText());
}

void SettingsStereo::print(){
    cout << "Print:\n";
//    << "boardSize.width: " << this->boardSize.width << std::endl
//    << "boardSize.height: " << this->boardSize.height << std::endl
//    << "_patternToUse: " << this->_patternToUse << std::endl
//    << "squareSize: " << this->squareSize << std::endl
//    << "nrFrames: " << this->nrFrames  << std::endl
//    << "aspectRatio: " << this->aspectRatio << std::endl
//    << "bwritePoints: " << this->bwritePoints << std::endl
//    << "bwriteExtrinsics: " << this->bwriteExtrinsics << std::endl
//    << "outputFileName: " << this->outputFileName << std::endl
//    << "calibZeroTangentDist: " << this->calibZeroTangentDist << std::endl
//    << "calibFixPrincipalPoint: " << this->calibFixPrincipalPoint << std::endl
//    << "flipVertical: " << this->flipVertical << std::endl
//    << "showUndistorsed: " << this->showUndistorsed << std::endl
//    << "input: " << this->input << std::endl
//    << "delay: " << this->delay << std::endl;
}
