#include <mainController/MainController.h>

myMainController::MainController::MainController()
{
    this->_name = "MainController";
    _settings = new SettingsMainController();
}

myMainController::MainController::~MainController(){
    if(_settings->has_calib_module && _calibModule != NULL){delete _calibModule;}
    if(_settings->has_match_module && _matchModule != NULL){delete _matchModule;}
    if(_settings->has_viewer_module && _viewModule != NULL){delete _viewModule;}
    delete _settings;
}

int myMainController::MainController::config(string fileLocation){
    #if DEBUG_MAIN_CONTROLLER
        cout << "MainController::config starting...\n";
    #endif

    if(_settings->read(fileLocation) != 0){
        cerr << "MainController::config(): Error on reading Setting file!\n";
        return -1;
    }

    #if DEBUG_MAIN_CONTROLLER
        cout << "MainController::interprate starting...\n";
    #endif

    if (_settings->interprate() != 0){
        cerr << "MainController::config(): Error on Setting File!\n";
        return -1;
    }

    #if DEBUG_MAIN_CONTROLLER
        cout << "MainController::operation mode checker starting...\n";
    #endif

    // Check the Operation Mode //
    if(!_settings->runMode.compare("CALIBRATION_ONLY")) {
//        _mode = myMainController::runMode::CALIBRATION_ONLY;
        _mode = runMode::CALIBRATION_ONLY;
        #if DEBUG_MAIN_CONTROLLER
        cout << "MainController::config(): operation mode CALIBRATION_ONLY\n";
        #endif
    }
    else if(!_settings->runMode.compare("MATCHING_ONLY")) {
//        _mode = myMainController::runMode::MATCHING_ONLY;
        _mode = runMode::MATCHING_ONLY;
        #if DEBUG_MAIN_CONTROLLER
            cout << "MainController::config(): operation mode MATCHING_ONLY\n";
        #endif
    }
    else if(!_settings->runMode.compare("CALIBRATION_MATCHING")) {
//        _mode = myMainController::runMode::CALIBRATION_MATCHING;
        _mode = runMode::CALIBRATION_MATCHING;
        #if DEBUG_MAIN_CONTROLLER
                cout << "MainController::config(): operation mode CALIBRATION_MATCHING\n";
        #endif
    }
    else {
        cerr << "MainController::config() Error: Invalid Operation Mode!\n";
        return -1;
    }




    // Call modules configuration //
    if(_settings->has_calib_module){
        _calibModule = Factory::getNewClibModule(_settings->calibType);
        if(_calibModule == NULL){
            cerr << "MainController::config(): Error on alocating Calibration class!\n";
            return -1;
        }
        _calibModule->config(_settings->calibFile);
        cout << "Calibration Module Selected\n";
    }
    if(_settings->has_match_module){
        _matchModule = Factory::getNewMatchModule(_settings->matchType);
        if(_matchModule == NULL){
            cerr << "MainController::config(): Error on alocating Matching class!\n";
            return -1;
        }
        _matchModule->config(_settings->matchFile);
        cout << "Match Module Selected\n";
    }
    if(_settings->has_viewer_module){
        _viewModule = Factory::getNewViewModule(_settings->viewType);
        if(_viewModule == NULL){
            cerr << "MainController::config(): Error on alocating Viewer class!\n";
            return -1;
        }
        _viewModule->config(_settings->viewFile);
        cout << "Viewer Module Selected\n";
    }
    return 0;


//    // Normal Calibration
//    if(flags[0] == true){
//        #if DEBUG
//            std::cout << "Calibration";
//        #endif
//        Calibration *calib = new Calibration();
//        calib->config(configFile);
//        calib->calibrate();
//        delete calib;
//    }

//    // Stereo Calibration
//    if(flags[1] == true){
//        #if DEBUG
//            std::cout << "Stereo-Calibration\n";
//        #endif

//        StereoCalib calib;
//        calib.config(configFile);

//        // Run the calibration process based on config file //
//        if(calib.calibrate() != 0)
//        {
//            cerr << "Error on Calibration!\n";
//        }

//        // Run the rectification process based on config file //
//        if(calib.rectificate() != 0){
//            cerr << "Error on Rectification!\n";
//        }
//    }

//    // Stereo Matching
//    if(flags[2] == true){
//        StereoMatching *method;
//        if(param == "--algorithm=bm")
//        {
//            method = new BlockMatching();
//        }
//        else if(param == "--algorithm=sgbm")
//        {
//            method = new SGBM();
//        }
//        else
//        {
//            std::cerr << "Not recognize parameter: " << param;
//            return -1;
//        }
//        #if DEBUG
//            cout << method->nameToString();
//        #endif

//        if(method->config(configFile) != 0){
//            std::cerr << "Error on Matching Configuration!\n";
//            delete method;
//            return -1;
//        }

////        if(method->match() != 0){
////            std::cerr << "Error on Matching Method '" << method->nameToString() << "'\n";
////            delete method;
////            return -1;
////        }
//        delete method;
//    }
//    return 0;
}

int myMainController::MainController::run(){
    return 1;
}


//Module *myMainController::MainController::_getType(string type){
//    if(!type.compare(NameOfModules.CALIBRATION_SINGLE)){
//        Module *ptr = new CalibSingle();
//        return ptr;
//    }
//    else if(!type.compare(NameOfModules.CALIBRATION_STEREO)){
//        Module *ptr = new CalibStereo();
//        return ptr;
//    }
//    else if(!type.compare(NameOfModules.MATCHING_BM)){
//        Module *ptr = new MatchBM();
//        return ptr;
//    }
//    else if(!type.compare(NameOfModules.MATCHING_SGBM)){
//        Module *ptr = new MatchSGBM();
//        return ptr;
//    }
////    else if(!type.compare(NameOfModules.VEWER3D)){

////    }
//    else{
//        return NULL;
//    }
//}
