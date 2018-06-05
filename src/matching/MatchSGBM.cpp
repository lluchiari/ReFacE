#include <matching/MatchSGBM.h>

MatchSGBM::MatchSGBM(){
    this->_name = consts::MATCHING_SGBM;
}

MatchSGBM::~MatchSGBM() {
}

int MatchSGBM::config(string filename){
    if(LOG_SETTINGS_MATCHING_SGBM){cout << "MatchSGBM::config(): Start...\n";}

    if(this->_matchSettings.read(filename) != 0){
        cerr << "MatchSGBM::config(): Error on read settings!\n";
        return -1;
    }
    if(this->_matchSettings.interprate() != 0){
        cerr << "MatchSGBM::config(): Error on interprate!\n";
        return -1;
    }
    // Check the input type in order to prepare the required resources //
    if(_matchSettings.inputType == InputType::CAMERA){
        inputCaptureLeft.open(_matchSettings.cameraLeftID);
        if(!inputCaptureLeft.isOpened()){
            cerr << "MatchSGBM::config(): Error on opening left camera!\n";
            return -1;
        }
        inputCaptureRight.open(_matchSettings.cameraRightID);
        if(!inputCaptureRight.isOpened()){
            cerr << "MatchSGBM::config(): Error on opening right camera!\n";
            return -1;
        }
        cout << "CAMERA mode! This are the camera parameters:\n";
        cout << "LeftCamID: " << this->_matchSettings.cameraLeftID << "\n";
        cout << "RightCamID: " << this->_matchSettings.cameraRightID << "\n";
    }
    else if(_matchSettings.inputType == InputType::IMAGE_LIST){
        // isImageList was already verified on SettingsMatchingBM::interprate()
        if(!Settings::readStringList(_matchSettings.input, imageList)){
            cerr << "MatchSGBM::config():Error on reading xml of string list. Is that on right format?\n";
            return -1;
        }

        #if DEBUG_MATCHING_BM
            cout << "MatchBM::config(): Is a list of images! Here are the images:\n";
            for(std::vector<string>::iterator it = imageList.begin(); it != imageList.end(); ++it){
                cout << *it;
                cout << "\n";
            }
        #endif
    }
    else if(_matchSettings.inputType == InputType::VIDEO_FILE){
        cerr << "MatchSGBM::config(): VIDEO FILE input. This is not an error! Comming soon...\n";
        return -1;
    }
    else if(_matchSettings.inputType == InputType::INVALID){
        cerr << "MatchSGBM::config(): Error! INVALID Input type mode!\n";
        return -1;
    }
    else{
        cerr << "MatchSGBM::config(): Error! Not Recognized Input Type! Please check it in your config file.\n";
    }


    if(LOG_SETTINGS_MATCHING_SGBM){cout << "MatchSGBM::config(): Finish_OK!\n";}
    return 0;
}

int MatchSGBM::run(){
    if(LOG_SETTINGS_MATCHING_SGBM){cout << "MatchSGBM::run(): Start...\n";}

    if(_loadCameraParameters() != 0){
        cerr << "MatchBM::config(): Error on loading camera Matrix\n";
        return -1;
    }

    /* Configure Block Matching Prameters */
    sgbm = StereoSGBM::create(_matchSettings.maxDisparity, _matchSettings.windowSize);

    sgbm->setPreFilterCap(_matchSettings.preFilterCarp);
    sgbm->setBlockSize(_matchSettings.windowSize);
    sgbm->setP1(8*_matchSettings.channels*_matchSettings.windowSize*_matchSettings.windowSize);
    sgbm->setP2(32*_matchSettings.channels*_matchSettings.windowSize*_matchSettings.windowSize);
    sgbm->setMinDisparity(0);
    sgbm->setNumDisparities(_matchSettings.maxDisparity);
    sgbm->setUniquenessRatio(_matchSettings.uniquenessRatio);
    sgbm->setSpeckleWindowSize(_matchSettings.speckleWindowSize);
    sgbm->setSpeckleRange(_matchSettings.speckleRange);
    sgbm->setDisp12MaxDiff(_matchSettings.disp12MaxDiff);
    if(!_matchSettings.algorithm.compare("STEREO_HH"))
        sgbm->setMode(StereoSGBM::MODE_HH);
    else if(!_matchSettings.algorithm.compare("STEREO_SGBM"))
        sgbm->setMode(StereoSGBM::MODE_SGBM);
    else if(!_matchSettings.algorithm.compare("STEREO_3WAY"))
        sgbm->setMode(StereoSGBM::MODE_SGBM_3WAY);


    if(_matchSettings.inputType == CAMERA)
    {
        if(!inputCaptureLeft.isOpened()){
            cerr << "MatchBM::run(): Error on opening left camera!\n";
            return -1;
        }
        if(!inputCaptureRight.isOpened()){
            cerr << "MatchBM::run(): Error on opening right camera!\n";
            return -1;
        }

        inputCaptureLeft.release();
        inputCaptureRight.release();
    }
    else if(_matchSettings.inputType == IMAGE_LIST)
    {
        Mat aux[2];
        Mat imgRight, imgLeft;
        string imgName1, imgName2;
        int imgCount=0;
        for(std::vector<string>::iterator it = imageList.begin(); it != imageList.end(); ++it, imgCount++)
        {
            imgName1 = it->data();
            imgRight = imread(it->data(), _colorMode);
            ++it;
            imgName2 = it->data();
            imgLeft = imread(it->data(), _colorMode);

            // Check the images existence //
            if (imgRight.empty())
            {
                cerr << "MatchSGBM::run(): Error on loading '" << imgName1 << "' image from imageList! Not existing image! Check your files!\n";
                return -1;
            }
            if (imgLeft.empty())
            {
                cerr << "MatchSGBM::run(): Error on loading '" << imgName2 << "' image from imageList! Not existing image! Check your files!\n";
                return -1;
            }

            imshow("ImgRight", imgRight);
            imshow("ImgLeft", imgLeft);

            remap(imgRight, aux[0], _mapCam1[0], _mapCam1[1], INTER_LINEAR);
            remap(imgLeft, aux[1], _mapCam2[0], _mapCam2[1], INTER_LINEAR);

            imgRight = aux[0];
            imgLeft = aux[1];

            // Compute the stereo itself! //
            sgbm->compute(imgRight, imgLeft, disp);

            disp.convertTo(disp8, CV_8U);

            //Write on output file:
            string outpuFileName;
            outpuFileName = _matchSettings.outputFileName + "output_match_sgbm_" + _matchSettings.systemName + "_" +to_string(imgCount) + ".jpg";
            cout << outpuFileName << endl;

//            double sf1 = (600./MAX(imgRight.cols, imgRight.rows));
//            Rect vroi1(cvRound(_validRoi[0].x*sf1), cvRound(_validRoi[0].y*sf1),
//                      cvRound(_validRoi[0].width*sf1), cvRound(_validRoi[0].height*sf1));
//            rectangle(imgRight, vroi1, Scalar(0,0,255), 3, 8);

//            double sf2 = (600./MAX(imgLeft.cols, imgLeft.rows));
//            Rect vroi2(cvRound(_validRoi[1].x*sf2), cvRound(_validRoi[1].y*sf2),
//                      cvRound(_validRoi[1].width*sf2), cvRound(_validRoi[1].height*sf2));
//            rectangle(imgLeft, vroi2, Scalar(0,0,255), 3, 8);

            namedWindow("left", 1);
            imshow("right", imgRight);
            namedWindow("right", 1);
            imshow("left", imgLeft);
            namedWindow("disparity", 0);
            imshow("disparity", disp8);
            printf("press any key to continue...");
            waitKey();
            printf("\n");
            imwrite(outpuFileName, disp8);
        }
    }
    else if(_matchSettings.inputType == VIDEO_FILE)
    {
        // TODO: Take a frame (future)
    }
    else if(_matchSettings.inputType == INVALID){
        cerr << "MatchSGBM::run(): Error! Invalid input mode!\n";
        return -1;
    }
    else{
        cerr << "MatchSGBM::run(): WTF?!?!? This message was not suppose to happen!\n";
        return -1;
    }


    if(LOG_SETTINGS_MATCHING_SGBM){cout << "MatchSGBM::run(): Finish_OK!\n";}
    return 0;
}

int MatchSGBM::_loadCameraParameters()
{
    // Load the configuration matrix //
    FileStorage fs(_matchSettings.camParamFile, FileStorage::READ);

    if( !fs.isOpened() ){
        cerr << "MatchSGBM::_loadCameraParameters(): Error on opening Camera Matrix File" << endl;
        return -1;
    }

    fs["MAP1_CAM1"] >> _mapCam1[0];
    fs["MAP2_CAM1"] >> _mapCam1[1];
    fs["MAP1_CAM2"] >> _mapCam2[0];
    fs["MAP2_CAM2"] >> _mapCam2[1];
    fs["ROI1"] >> _validRoi[0];
    fs["ROI2"] >> _validRoi[1];
    fs.release();

    if(_mapCam1[0].empty() || _mapCam1[1].empty()){
        cerr << "MatchSGBM::_loadCameraParameters(): Error on reading camera1 matrix!\n";
        return -1;
    }
    if(_mapCam2[0].empty() || _mapCam2[1].empty()){
        cerr << "MatchSGBM::_loadCameraParameters(): Error on reading camera2 matrix!\n";
        return -1;
    }
    if(_validRoi[0].empty() || _validRoi[1].empty()){
        cerr << "MatchSGBM::_loadCameraParameters(): Error on reading ROI matrix!\n";
        return -1;
    }
    return 0;
}
