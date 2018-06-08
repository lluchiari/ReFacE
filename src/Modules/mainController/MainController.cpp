#include <Modules/mainController/MainController.h>

myMainController::MainController::MainController()
{
    this->_name = consts::MAIN_CONTROLLER;
}

myMainController::MainController::~MainController(){
    if(_connectionModule != NULL){delete _connectionModule;}
    if(_settings.has_calib_module && _calibModule != NULL){delete _calibModule;}
    if(_settings.has_match_module && _matchModule != NULL){delete _matchModule;}
    if(_settings.has_viewer_module && _viewModule != NULL){delete _viewModule;}    
}

int myMainController::MainController::config(string fileLocation){
    if(LOG_MAIN_CONTROLLER){cout << "MainController::config(): Start...\n";}

    if(_settings.read(fileLocation) != 0){cerr << "MainController::config(): Error on reading Setting file!\n";return -1;}
    if (_settings.interprate() != 0){cerr << "MainController::config(): Error on Setting File!\n";return -1;}


    //---------------------------------------------------------------
    //                      ALWAYS
    //---------------------------------------------------------------
    //###################################
    //#        CONECTION MODULE         #
    //###################################
    // Connection will ALWAYS Instantiate! on future, I can differentiate with the Run Mode used //
    _connectionModule = Factory::getNewConnectionModule(_settings.runMode);
    if(_connectionModule == NULL){
        cerr << "MainController::config(): Error on Connection Module Instatiation!\n";
        return -1;
    }


    //---------------------------------------------------------------
    //                      CAPTURE_IMAGES
    //---------------------------------------------------------------
    // Check the Operation Mode //
    if(!_settings.runMode.compare("CAPTURE_IMAGES")) {
        _runMode = consts::runMode::CAPTURE_IMAGES;
    }
    //---------------------------------------------------------------
    //                      CALIBRATION_ONLY
    //---------------------------------------------------------------
    else if(!_settings.runMode.compare("CALIBRATION_ONLY")) {
        _runMode = consts::runMode::CALIBRATION_ONLY;
        #if DEBUG_MAIN_CONTROLLER
        cout << "MainController::config(): operation mode CALIBRATION_ONLY\n";
        #endif

        //###################################
        //#         CALIB MODULE            #
        //###################################
        if(_settings.has_calib_module)
        {
            _calibModule = Factory::getNewClibModule(_settings.calibType);
            if(_calibModule == NULL){cerr << "MainController::config(): Error on alocating Calibration class of CALIBRATION_ONLY!\n";return -1;}

            if(_calibModule->config(_settings.calibFile) != 0){cerr << "MainController::config(): Error on config of Calibration module on CALIBRATION_ONLY!\n";return -1;}
        }
        else{
            cerr << "MainController::config(): No calib module found!\n";
            return -1;
        }
    }

    //---------------------------------------------------------------
    //                              MATCHING_ONLY
    //---------------------------------------------------------------
    else if(!_settings.runMode.compare("MATCHING_ONLY")) {
        _runMode = consts::runMode::MATCHING_ONLY;
        #if DEBUG_MAIN_CONTROLLER
            cout << "MainController::config(): operation mode MATCHING_ONLY\n";
        #endif

        //###################################
        //#         MATCH MODULE            #
        //###################################
        if(_settings.has_match_module){
            _matchModule = Factory::getNewMatchModule(_settings.matchType);
            if(_matchModule == NULL){cerr << "MainController::config(): Error on alocating Matching class of MATCHING_ONLY!\n";return -1;}

            if(_matchModule->config(_settings.matchFile) != 0){cerr << "MainController::config(): Error on Matching Module of MATCHING_ONLY!\n";return -1;}
        }
        else {
            cerr << "MainController::config(): No match module found!\n";
            return -1;
        }
    }

    //---------------------------------------------------------------
    //                      CALIBRATION_MATCHING
    //---------------------------------------------------------------
    else if(!_settings.runMode.compare("CALIBRATION_MATCHING")) {
        _runMode = consts::runMode::CALIBRATION_MATCHING;
        #if DEBUG_MAIN_CONTROLLER
                cout << "MainController::config(): operation mode CALIBRATION_MATCHING\n";
        #endif

        //###################################
        //#         CALIB MODULE            #
        //###################################
        if(_settings.has_calib_module)
        {
            _calibModule = Factory::getNewClibModule(_settings.calibType);
            if(_calibModule == NULL){cerr << "MainController::config(): Error on alocating Calibration class of CALIBRATION_MATCHING!\n";return -1;}

            if(_calibModule->config(_settings.calibFile) != 0){cerr << "MainController::config(): Error on config of Calibration module on CALIBRATION_MATCHING!\n";return -1;}
        }
        else{
            cerr << "MainController::config(): No calib module found!\n";
            return -1;
        }

        //###################################
        //#         MATCH MODULE            #
        //###################################
        if(_settings.has_match_module){
            _matchModule = Factory::getNewMatchModule(_settings.matchType);
            if(_matchModule == NULL){cerr << "MainController::config(): Error on alocating Matching class of CALIBRATION_MATCHING!\n";return -1;}
            if(_matchModule->config(_settings.matchFile) != 0){cerr << "MainController::config(): Error on Matching Module of CALIBRATION_MATCHING!\n";return -1;}
        }
        else{
            cerr << "MainController::config(): No match module found!\n";
            return -1;
        }

    }

    //---------------------------------------------------------------
    //                      CALIBRATION_MATCHING_VIEW
    //---------------------------------------------------------------
    else if(!_settings.runMode.compare("CALIBRATION_MATCHING_VIEW")){
        _runMode = consts::runMode::CALIBRATION_MATCHING_VIEW;
        #if DEBUG_MAIN_CONTROLLER
                cout << "MainController::config(): operation mode CALIBRATION_MATCHING_VIEW\n";
        #endif

        //###################################
        //#         CALIB MODULE            #
        //###################################
        if(_settings.has_calib_module)
        {
            _calibModule = Factory::getNewClibModule(_settings.calibType);
            if(_calibModule == NULL){cerr << "MainController::config(): Error on alocating Calibration class of CALIBRATION_MATCHING_VIEW!\n";return -1;}
            if(_calibModule->config(_settings.calibFile) != 0){cerr << "MainController::config(): Error on config of Calibration module on CALIBRATION_MATCHING_VIEW!\n";return -1;}
        }
        else{
            cerr << "MainController::config(): No calib module found!\n";
            return -1;
        }

        //###################################
        //#         MATCH MODULE            #
        //###################################
        if(_settings.has_match_module){
            _matchModule = Factory::getNewMatchModule(_settings.matchType);
            if(_matchModule == NULL){cerr << "MainController::config(): Error on alocating Matching class of CALIBRATION_MATCHING_VIEW!\n";return -1;}
            if(_matchModule->config(_settings.matchFile) != 0){cerr << "MainController::config(): Error on Matching Module of CALIBRATION_MATCHING_VIEW!\n";return -1;}
        }
        else{
            cerr << "MainController::config(): No match module found!\n";
            return -1;
        }

        //###################################
        //#         VIEWER MODULE           #
        //###################################
        if(_settings.has_viewer_module){
            _viewModule = Factory::getNewViewModule(_settings.viewType);
            if(_viewModule == NULL){cerr << "MainController::config(): Error on alocating Viewer class of CALIBRATION_MATCHING_VIEW!\n";return -1;}
            if(_viewModule->config(_settings.viewFile) != 0){cerr << "MainController::config(): Error on config Viewer module of CALIBRATION_MATCHING_VIEW!\n";return -1;}
        }
        else{
            cerr << "MainController::config(): No viewer module found!\n";
            return -1;
        }
    }
    else {
        cerr << "MainController::config() Error: Invalid Operation Mode!\n";
        return -1;
    }


//#################################################################
//#################################################################

    if(LOG_MAIN_CONTROLLER){cout << "MainController::config(): Finish_OK!\n";}
    return 0;
}

int myMainController::MainController::run()
{
    if(LOG_MAIN_CONTROLLER){cout << "MainController::run(): Start...\n";}

    if(this->_runMode == consts::runMode::CAPTURE_IMAGES){
        CameraCapture::stereoCapture("../images/StereoDataset/", this->_settings.systemName,1,2);
    }
    else if(_runMode == consts::runMode::CALIBRATION_ONLY){
        if(_calibModule->run() != 0){cerr << "MainController::run(): Error on running calibration module!\n";return -1;}
    }
    else if(_runMode == consts::runMode::MATCHING_ONLY){
        if(_matchModule->run() != 0) {cerr << "MainController::run(): Error on running matching module!\n";return -1;}
    }
    else if(_runMode == consts::runMode::CALIBRATION_MATCHING){
        if(_calibModule->run() != 0){cerr << "MainController::run(): Error on running calibration module!\n";return -1;}
        if(_matchModule->run() != 0){cerr << "MainController::run(): Error on running matching module!\n";return -1;}
    }
    else
    {
        cerr << "MainController::run(): Error on mode selecting! Mode doens't exist!\n";
        return -1;
    }
    if(LOG_MAIN_CONTROLLER){cout << "MainController::run(): Finish_OK!\n";}
    return 0;
}
