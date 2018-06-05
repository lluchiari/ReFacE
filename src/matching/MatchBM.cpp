#include <matching/MatchBM.h>

#include <QThread>

MatchBM::MatchBM(){
    this->_name = consts::MATCHING_BM;
}

MatchBM::~MatchBM() {
    if(setParam!= NULL){delete setParam;}
}

int MatchBM::config(string filename)
{
    if(LOG_MATCHING_BM){cout << "MatchBM::config(): Start...\n";}
    if(this->_matchSettings.read(filename) != 0){
        cerr << "MatchBM::config(): Error on read settings!\n";
        return -1;
    }    
    if(this->_matchSettings.interprate() != 0){
        cerr << "MatchBM::config(): Error on interprate!\n";
        return -1;
    }

    // Check the input type in order to prepare the required resources //
    if(_matchSettings.inputType == InputType::CAMERA){
        inputCaptureLeft.open(_matchSettings.cameraLeftID);
        if(!inputCaptureLeft.isOpened()){
            cerr << "MatchBM::config(): Error on opening left camera!\n";
            return -1;
        }
        inputCaptureRight.open(_matchSettings.cameraRightID);
        if(!inputCaptureRight.isOpened()){
            cerr << "MatchBM::config(): Error on opening right camera!\n";
            return -1;
        }
        cout << "CAMERA mode! This are the camera parameters:\n";
        cout << "LeftCamID: " << this->_matchSettings.cameraLeftID << "\n";
        cout << "RightCamID: " << this->_matchSettings.cameraRightID << "\n";
    }
    else if(_matchSettings.inputType == InputType::IMAGE_LIST){
        // isImageList was already verified on SettingsMatchingBM::interprate()
        if(!Settings::readStringList(_matchSettings.input, imageList)){
            cerr << "MatchBM::config():Error on reading xml of string list. Is that on right format?\n";
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
        cerr << "MatchBM::config(): VIDEO FILE input. This is not an error! Comming soon...\n";
        return -1;
    }
    else if(_matchSettings.inputType == InputType::INVALID){
        cerr << "MatchBM::config(): Error! INVALID Input type mode!\n";
        return -1;
    }
    else{
        cerr << "MatchBM::config(): Error! Not Recognized Input Type! Please check it in your config file.\n";
    }

    if(LOG_MATCHING_BM){cout << "MatchBM::config(): Finish_OK!\n";}
    return 0;
}

int MatchBM::run(){
    if(LOG_MATCHING_BM){cout << "MatchBM::run(): Start...\n";}


    if(_loadCameraParameters() != 0){
        cerr << "MatchBM::config(): Error on loading camera Matrix\n";
        return -1;
    }

    /* Configure Block Matching Prameters */
    bm = StereoBM::create(_matchSettings.maxDisparity, _matchSettings.windowSize);

    bm->setROI1(_validRoi[0]);
    bm->setROI2(_validRoi[1]);
    bm->setPreFilterCap(_matchSettings.preFilterCarp);
    bm->setBlockSize(_matchSettings.windowSize);
    bm->setMinDisparity(0);
    bm->setNumDisparities(_matchSettings.maxDisparity);
    bm->setTextureThreshold(_matchSettings.textureThreshold);
    bm->setUniquenessRatio(_matchSettings.uniquenessRatio);
    bm->setSpeckleWindowSize(_matchSettings.speckleWindowSize);
    bm->setSpeckleRange(_matchSettings.speckleRange);
    bm->setDisp12MaxDiff(_matchSettings.disp12MaxDiff);


    if(_matchSettings.inputType == CAMERA)
    {
        if(!inputCaptureRight.isOpened()){
            cerr << "MatchBM::run(): Error on opening right camera!\n";
            return -1;
        }
        if(!inputCaptureLeft.isOpened()){
            cerr << "MatchBM::run(): Error on opening left camera!\n";
            return -1;
        }

        // Check if there is Parameters Real-Time Setter
        if(this->_matchSettings.hasRealTimeSetter){
            setParam = new SetMatchParamWindow(consts::MATCHING_BM, this, NULL);
            setParam->show();
        }

        char key;
        Mat imgRight, imgLeft;
        Mat imgBlackRight, imgBlackLeft;
        Mat auxRight, auxLeft;

        for(int i=0;;i++){
            inputCaptureRight >> imgRight;
            inputCaptureLeft >> imgLeft;

            if(imgRight.empty() || imgLeft.empty()){
                cerr << "MatchBM::run():: CAMERA_MODE: Error on capturing camera images. One of those are empty!\n";
                return -1;
            }

            cvtColor(imgRight, imgBlackRight, COLOR_BGR2GRAY);
            cvtColor(imgLeft, imgBlackLeft, COLOR_BGR2GRAY);

            remap(imgBlackRight, auxRight, _mapCam1[0], _mapCam1[1], INTER_LINEAR);
            remap(imgBlackLeft, auxLeft, _mapCam2[0], _mapCam2[1], INTER_LINEAR);

//            do{key = waitKey(10);}
//            while(key != consts::ESC_KEY);

            imgRight = auxRight;
            imgLeft = auxLeft;

            // Compute the stereo itself! //
            bm->compute(imgRight, imgLeft, disp);

            disp.convertTo(disp8, CV_8U);

            namedWindow("left", 1);
            imshow("left", imgRight);
            namedWindow("right", 1);
            imshow("right", imgLeft);
            namedWindow("disparity", 0);
            imshow("disparity", disp8);

            key = waitKey(10);
            if(key == consts::ESC_KEY){break;}
        }

        inputCaptureLeft.release();
        inputCaptureRight.release();
    }
    else if(_matchSettings.inputType == IMAGE_LIST)
    {
        Mat aux[2];
        Mat img1, img2;
        string imgName1, imgName2;
        int imgCount=0;
        for(std::vector<string>::iterator it = imageList.begin(); it != imageList.end(); ++it, imgCount++)
        {
            imgName1 = it->data();
            img1 = imread(it->data(), _colorMode);
            ++it;
            imgName2 = it->data();
            img2 = imread(it->data(), _colorMode);

            // Check the images existence //
            if (img1.empty())
            {
                cerr << "MatchBM::run(): Error on loading '" << imgName1 << "' image from imageList! Not existing image! Check your files!\n";
                return -1;
            }
            if (img2.empty())
            {
                cerr << "MatchBM::run(): Error on loading '" << imgName2 << "' image from imageList! Not existing image! Check your files!\n";
                return -1;
            }

// TODO: Check if this is necessary, once we've made on calibration process!
//            // Scale if necessary //
//            if (_matchSettings.scale != 1.f)
//            {
//                Mat temp1, temp2;
//                int method = _matchSettings.scale < 1 ? INTER_AREA : INTER_CUBIC;
//                resize(img1, temp1, Size(), _matchSettings.scale, _matchSettings.scale, method);
//                img1 = temp1;
//                resize(img2, temp2, Size(), _matchSettings.scale, _matchSettings.scale, method);
//                img2 = temp2;
//            }

            remap(img1, aux[0], _mapCam1[0], _mapCam1[1], INTER_LINEAR);
            remap(img2, aux[1], _mapCam2[0], _mapCam2[1], INTER_LINEAR);

            img1 = aux[0];
            img2 = aux[1];

            // Compute the stereo itself! //
            bm->compute(img1, img2, disp);

            disp.convertTo(disp8, CV_8U);

            //Write on output file:
            string outpuFileName;
            outpuFileName = _matchSettings.outputFileName + "output_match_bm_" + _matchSettings.systemName + "_" +to_string(imgCount) + ".jpg";
            cout << outpuFileName << endl;

//            double sf1 = (600./MAX(img1.cols, img1.rows));
//            Rect vroi1(cvRound(_validRoi[0].x*sf1), cvRound(_validRoi[0].y*sf1),
//                      cvRound(_validRoi[0].width*sf1), cvRound(_validRoi[0].height*sf1));
//            rectangle(img1, vroi1, Scalar(0,0,255), 3, 8);

//            double sf2 = (600./MAX(img2.cols, img2.rows));
//            Rect vroi2(cvRound(_validRoi[1].x*sf2), cvRound(_validRoi[1].y*sf2),
//                      cvRound(_validRoi[1].width*sf2), cvRound(_validRoi[1].height*sf2));
//            rectangle(img2, vroi2, Scalar(0,0,255), 3, 8);

            namedWindow("left", 1);
            imshow("left", img1);
            namedWindow("right", 1);
            imshow("right", img2);
            namedWindow("disparity", 0);
            imshow("disparity", disp8);
            printf("press any key to continue...");
            fflush(stdout);
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
        cerr << "MatchBM::run(): Error! Invalid input mode!\n";
        return -1;
    }
    else{
        cerr << "MatchBM::run(): WTF?!?!? This message was not suppose to happen!\n";
        return -1;
    }

    if(LOG_MATCHING_BM){cout << "MatchBM::run(): Finish_OK!\n";}
    return 0;
}

int MatchBM::_loadCameraParameters()
{
    if(LOG_MATCHING_BM){cout << "MatchBM::_loadCameraParameters(): Start...\n";}

    // Load the configuration matrix //
    FileStorage fs(_matchSettings.camParamFile, FileStorage::READ);

    if( !fs.isOpened() ){
        cerr << "MatchBM::_loadCameraParameters(): Error on opening Camera Matrix File" << endl;
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
        cerr << "MatchBM::_loadCameraParameters(): Error on reading camera1 matrix!\n";
        return -1;
    }
    if(_mapCam2[0].empty() || _mapCam2[1].empty()){
        cerr << "MatchBM::_loadCameraParameters(): Error on reading camera2 matrix!\n";
        return -1;
    }
    if(_validRoi[0].empty() || _validRoi[1].empty()){
        cerr << "MatchBM::_loadCameraParameters(): Error on reading ROI matrix!\n";
        return -1;
    }

    if(LOG_MATCHING_BM){cout << "MatchBM::_loadCameraParameters(): Finish_OK!\n";}
    return 0;
}


