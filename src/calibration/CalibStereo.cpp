#include <calibration/CalibStereo.h>

CalibStereo::CalibStereo()
{
    _name = consts::CALIBRATION_STEREO;
    _configFlag = false;
}

CalibStereo::~CalibStereo(){
}

int CalibStereo::config(string configFile)
{
    if(LOG_CALIB_STEREO){cout << "CalibStereo::config(): Start...\n";}

    #if DEBUG_CALIB_STEREO
        cout << "################################################\n";
        cout << "SteroCalib::config(): Configurating....\n";
    #endif

    if(this->_s.read(configFile) != 0){
        cerr << "CalibStereo::config(): Error on reading configuration file!\n";
        return -1;
    }

    if(this->_s.interprate() != 0)
    {
        cerr << "CalibStereo::config(): Error on interprating configuration file!\n";
        return -1;
    }

    #if DEBUG_CALIB_STEREO
        this->_s.print();
        cout << "SteroCalib::config(): Leaving Configurate.\n";
    #endif

    _configFlag = true;

    if(LOG_CALIB_STEREO){cout << "CalibStereo::config(): Finish_OK!\n";}
    return 0;
}

int CalibStereo::run()
{
    if(LOG_CALIB_STEREO){cout << "CalibStereo::run(): Start...\n";}

    #if DEBUG_CALIB_STEREO
        cout << "################################################\n";
        cout << "SteroCalib::run(): Calibrating...\n";
    #endif

    // Check if the configuration was previously done //
    if(!_configFlag){
        cerr << "StereoCalib::run(): Please run config() method first!\n";
        return -1;
    }


    if(this->_s.inputType == consts::CAMERA)
    {
        inputCaptureLeft.open(_s.cameraLeftID);
        inputCaptureRight.open(_s.cameraRightID);
        if(_pairDetectCamera() != 0){
            cerr << "CalibStereo::run(): Error on captureAndSave function!\n";
            return -1;
        }
    }
    else if(this->_s.inputType == consts::IMAGE_LIST)
    {
        // Check if the image list contain correct files //
        // Find the pattern points in the image //
        if(this->_pairDetectImageList() != 0){
            cerr << "SteroCalib::run(): Error on the list image pair detection,"
                 << "please verify your image and configuration files.\n";
            return -1;
        }
    }

    #if DEBUG_CALIB_STEREO
        cout << "SteroCalib::run(): Running stereo calibration ...\n";
    #endif

    _cameraMatrix[0] = initCameraMatrix2D(_objectPoints,_imagePoints[0],imageSize,0);
    _cameraMatrix[1] = initCameraMatrix2D(_objectPoints,_imagePoints[1],imageSize,0);

    _rms = stereoCalibrate(_objectPoints, _imagePoints[0], _imagePoints[1],
            _cameraMatrix[0], _distCoeffs[0],
            _cameraMatrix[1], _distCoeffs[1],
            imageSize, _R, _T, _E, _F,
            CALIB_FIX_ASPECT_RATIO +
            CALIB_ZERO_TANGENT_DIST +
            CALIB_USE_INTRINSIC_GUESS +
            CALIB_SAME_FOCAL_LENGTH +
            CALIB_RATIONAL_MODEL +
            CALIB_FIX_K3 + CALIB_FIX_K4 + CALIB_FIX_K5,
            TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 100, 1e-5) );

    #if DEBUG_CALIB_STEREO
        cout << "Done with RMS error=" << _rms << endl;
    #endif

    // CALIBRATION QUALITY CHECK
    // because the output fundamental matrix implicitly
    // includes all the output information,
    // we can check the quality of calibration using the
    // epipolar geometry constraint: m2^t*F*m1=0
    _calibCheck();

    // Save the output parameters in the file //
    if(_calibStereoSaveIntrinsicParam() != 0)
    {
        cerr << "CalibStereo::run(): Error on Saving Intrinsic parameters of Calibration\n";
        return -1;
    }

    #if DEBUG_CALIB_STEREO
        cout << "End of Calibration! Everything is fine!\n";
    #endif

    #if DEBUG_CALIB_STEREO
        cout << "Start Rectification!\n";
    #endif

    if(rectificate() != 0){
        cerr << "CalibStereo::run(): Error on computing rectification!\n";
        return -1;
    }

    //######################################################################
    //#                      SAVE ALL THE PARAMETERS                       #
    //######################################################################

    if(_calibStereoSaveRectificateOuputParam() != 0){
        cerr << "CalibStereo::run(): Error on Saving Extrinsic parameters of Calibration\n";
        return -1;
    }

    if(_calibStereoSaveCameraParam() != 0){
        cerr << "CalibStereo::run(): Error on Saving Camera parameters of Calibration\n";
        return -1;
    }

    if(LOG_CALIB_STEREO){cout << "CalibStereo::run(): Finish_OK!\n";}
    return 0;
}

int CalibStereo::rectificate()
{
    if(LOG_CALIB_STEREO){cout << "CalibStereo::rectificate(): Start...\n";}
    #if DEBUG_CALIB_STEREO
        cout << "################################################\n";
        cout << "SteroCalib::rectificate(): Rectificating...\n";
    #endif

    int i, j, k;
    Rect roi1, roi2;

    stereoRectify(_cameraMatrix[0], _distCoeffs[0],
            _cameraMatrix[1], _distCoeffs[1],
            imageSize, _R, _T, _R1, _R2, _P1, _P2, _Q,
            CALIB_ZERO_DISPARITY, 0, imageSize, &roi1, &roi2);

    _validRoi[0] = roi1;
    _validRoi[1] = roi2;


    // COMPUTE AND DISPLAY RECTIFICATION
    if(this->_s.showRectified)
    {
       _showRectification();
    }
    else{

        // Creates the mapping for all the matching stereo methods use for image correciton //
        initUndistortRectifyMap(_cameraMatrix[0], _distCoeffs[0], _R1, _P1, imageSize, CV_16SC2, _mapCam1[0], _mapCam1[1]);
        initUndistortRectifyMap(_cameraMatrix[1], _distCoeffs[1], _R2, _P2, imageSize, CV_16SC2, _mapCam2[0], _mapCam2[1]);

        Mat canvas, auxCanvas;
        double sf;
        int w, h;
        sf = 600./MAX(imageSize.width, imageSize.height);
        w = cvRound(imageSize.width*sf);
        h = cvRound(imageSize.height*sf);

        canvas.create(h, w*2, CV_8UC3);
        auxCanvas.create(h, w,CV_8UC3);

        Mat img, rimg, cimg;

        for( i = 0; i < nimages; i++ )
        {
            for( k = 0; k < 2; k++ )
            {

                if(this->_s.inputType == consts::CAMERA){
                    img = _goodImageCamera.at(i*2+k);
                }
                else if (this->_s.inputType == consts::IMAGE_LIST){
                    // Loads the imagea and converts to the GrayScale //
                    img = imread(_goodImageList[i*2+k], IMREAD_GRAYSCALE);
                }
                if(k == 0) {
                    remap(img, rimg, _mapCam1[0], _mapCam1[1], INTER_LINEAR);
                }
                else{
                    remap(img, rimg, _mapCam2[0], _mapCam2[1], INTER_LINEAR);
                }

                cvtColor(rimg, cimg, COLOR_GRAY2BGR);


                Mat canvasPart = canvas(Rect(w*k, 0, w, h));
                resize(cimg, canvasPart, canvasPart.size(), 0, 0, INTER_AREA);
                Rect vroi(cvRound(_validRoi[k].x*sf), cvRound(_validRoi[k].y*sf),
                          cvRound(_validRoi[k].width*sf), cvRound(_validRoi[k].height*sf));
                rectangle(canvasPart, vroi, Scalar(0,0,255), 3, 8);
            }

            for( j = 0; j < canvas.rows; j += 16 ){
                line(canvas, Point(0, j), Point(canvas.cols, j), Scalar(0, 255, 0), 1, 8);
            }

            imshow("rectified", canvas);
            char c = (char)waitKey();
            if( c == 27 || c == 'q' || c == 'Q' )
                break;
        }
    }

    if(LOG_CALIB_STEREO){cout << "CalibStereo::rectificate(): Finish_OK!\n";}
    return 0;
}

int CalibStereo::_pairDetectImageList()
{
    if(LOG_CALIB_STEREO){cout << "CalibStereo::_pairDetectImageList(): Start...\n";}
    #if DEBUG_CALIB_STEREO
        cout << "################################################\n";
        cout << "SteroCalib::_pairDetect(): Starting Pair Detection.....\n";
    #endif

    // Check if the image list is odd //
    if( this->_s.imageList.size() % 2 != 0 )
    {
        cout << "SteroCalib::_pairDetect(): Error! The image list contains odd (non-even) number of elements\n";
        return -1;
    }

    #if DEBUG_CALIB_STEREO
        cout << "SteroCalib::_pairDetect(): Image list is not odd!\n" << this->_s.imageList.size() << endl;
    #endif

    // i is the image list iterator
    // j is the seccess image identified
    // k represents the right and left images iterator
    int i, j, k;
    nimages = (int)this->_s.imageList.size()/2;

    // ARRAY AND VECTOR STORAGE:
    _imagePoints[0].resize(nimages);
    _imagePoints[1].resize(nimages);

    #if DEBUG_CALIB_STEREO
        cout << "SteroCalib::_pairDetect(): Starting corner detection\n";
    #endif

    // This for iterates the images list and check if there is a correspondent
    // pair of image and detects the corner in these images
    for( i = j = 0; i < nimages; i++ )
    {
        for( k = 0; k < 2; k++ )
        {
            #if DEBUG_CALIB_STEREO
                cout << "SteroCalib::_pairDetect(): K = " << k << endl;
            #endif
            const string& filename = this->_s.imageList[i*2+k];

            #if DEBUG_CALIB_STEREO
                cout << "SteroCalib::_pairDetect() for loop: " << filename << endl;
            #endif

            Mat img = imread(filename, 0);
            if(img.empty()){
                cerr << "SteroCalib::_pairDetect() Warning: Image Pair Loop: Image " << filename << " is empty!" << endl;
                break;
            }
            if(!this->_s.boardSize.empty())
            {
                imageSize = img.size();

                #if DEBUG_CALIB_STEREO
                    cout << "SteroCalib::_pairDetect(): Size:" << imageSize << endl;
                #endif
            }
            else if( img.size() != imageSize )
            {
                cout << "SteroCalib::_pairDetect(): Warning!!! The image " << filename << " has the size different from the first image size. Skipping the pair\n";
                break;
            }
            bool found = false;

            // Points the corners object to the memory position of imagePoints
            vector<Point2f>& corners = _imagePoints[k][j];

            // Scales the imagens and tries to find the corners of the chessboard //
            for( int scale = 1; scale <= maxScale; scale++ )
            {
                // Auxiliar Matrix for the scaling //
                Mat timg;
                if( scale == 1 ){
                    timg = img;
                }
                else{
                    resize(img, timg, Size(), scale, scale, INTER_LINEAR_EXACT);
                }

                found = findChessboardCorners(timg, this->_s.boardSize, corners,
                                              CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);
                if(found)
                {
                    if( scale > 1 )
                    {
                        Mat cornersMat(corners);
                        cornersMat *= 1./scale;
                    }
                    #if DEBUG_CALIB_STEREO
                        cout << "SteroCalib::_pairDetect(): Corners FOUND!\n";
                    #endif
                    break;
                }
            }

            // Debug of points//
            if(this->_s.displayCorners)
            {
                cout << filename << endl;
                Mat cimg, cimg1;
                cvtColor(img, cimg, COLOR_GRAY2BGR);
                drawChessboardCorners(cimg, this->_s.boardSize, corners, found);
                double sf = 640./MAX(img.rows, img.cols);
                resize(cimg, cimg1, Size(), sf, sf, INTER_LINEAR_EXACT);
                imshow("corners", cimg1);
                char c = (char)waitKey(500);

                // Allow ESC to quit //
                if( c == 27 || c == 'q' || c == 'Q' )
                    exit(-1);
            }
            else
                putchar('.');
            if(!found){
                cerr << "SteroCalib::_pairDetect() Warning: Corners not found\n";
                break;
            }

            cornerSubPix(img, corners, Size(11,11), Size(-1,-1),
                         TermCriteria(TermCriteria::COUNT+TermCriteria::EPS,
                                      30, 0.01));
        }

        // Stores the good pair of images  //
        if( k == 2 )
        {
            #if DEBUG_CALIB_STEREO
                cout << "SteroCalib::_pairDetect(): Good Image Saved!" << endl;
            #endif
            _goodImageList.push_back(this->_s.imageList[i*2]);
            _goodImageList.push_back(this->_s.imageList[i*2+1]);
            j++;
        }
    }    

    #if DEBUG_CALIB_STEREO
        cout << "SteroCalib::_pairDetect(): " << j << " pairs have been successfully detected.\n";
    #endif

    // Number of pair of images correctlly detected //
    nimages = j;
    if( nimages < 2 )
    {
        std::cout << "SteroCalib::_pairDetectImageList(): Error! Too little pairs to run the calibration\n";
        return -1;
    }

    _imagePoints[0].resize(nimages);
    _imagePoints[1].resize(nimages);
    _objectPoints.resize(nimages);

    // Calculates the points of the Pattern (in this case the chessboard) //
    // It acts like a mask //
    for( i = 0; i < nimages; i++ )
    {
        for( j = 0; j < this->_s.boardSize.height; j++ )
            for( k = 0; k < this->_s.boardSize.width; k++ )
                _objectPoints[i].push_back(Point3f(k*this->_s.squareSize, j*this->_s.squareSize, 0));
    }

    if(LOG_CALIB_STEREO){cout << "CalibStereo::_pairDetectCamera(): Finish_OK!\n";}
    return 0;
}

int CalibStereo::_pairDetectCamera()
{
    if(LOG_CALIB_STEREO){cout << "CalibStereo::_pairDetectCamera(): Start...\n";}
    vector<vector<Point2f> > imageRightPoints, imageLeftPoints;

    if(!inputCaptureLeft.isOpened())
    {
        cerr << "CalibStereo::run(): Error on opening left camera!\n";
        return -1;
    }

    if(!inputCaptureRight.isOpened())
    {
        cerr << "CalibStereo::run(): Error on opening right camera!\n";
        return -1;
    }

    cout << "CAMERA mode! This are the camera parameters:\n";
    cout << "LeftCamID: " << this->_s.cameraLeftID << "\n";
    cout << "RightCamID: " << this->_s.cameraRightID << "\n";

    Mat auxRight, auxLeft, blackRight, blackLeft;
    bool foundRight, foundLeft;
    char key;

    for(int i=0;;i++)
    {
        cout << "CalibStereo::_pairDetectCamera(): Size: " << _imagePoints[0].size() << endl;

        do {
            inputCaptureRight >> auxRight;
            inputCaptureLeft >> auxLeft;

            imshow("Right", auxRight);
            imshow("Left", auxLeft);

            key = (char)waitKey(10);
        }while(key != consts::t_KEY && key != consts::ESC_KEY);

        if(key == consts::ESC_KEY){break;}

        // ARRAY AND VECTOR STORAGE:
        _imagePoints[0].resize(i+1);
        _imagePoints[1].resize(i+1);

        // Check if the cameras has trouble in the capturing process //
        if(auxRight.empty()) {
            cerr << "CalibStereo::_captureAndSave(): Error on capture the right camera image\n";
            return -1;
        }
        if(auxLeft.empty()) {
            cerr << "CalibStereo::_captureAndSave(): Error on capture the left camera image\n";
            return -1;
        }

        // Just check in the first time the image size //
        if(imageSize.empty())
        {
            // Check if the size of the images captured are the same //
            if( auxLeft.size() !=  auxRight.size()){
                cerr << "CalibStereo::_captureAndSave(): Error! Right Image Size is Different from Left Image Size. This program doesn't support different cameras yet! Please use the same configuration!\n";
                return -1;
            }
            else{
                //Whatever if the right or left image! I'm supposing that cameras are equal //
                imageSize = auxRight.size();
            }
        }

        #if DEBUG_CALIB_STEREO
                cout << "SteroCalib::_pairDetect(): Size:" << imageSize << endl;
        #endif

        // Variables for indicating the calibration occurance //
        foundRight = foundLeft = false;

        // Points the corners object to the memory position of imagePoints //
        vector<Point2f>& cornersRight = _imagePoints[0][i];
        vector<Point2f>& cornersLeft = _imagePoints[1][i];

        // Scales the imagens and tries to find the corners of the chessboard //
        for( int scale = 1; scale <= maxScale; scale++ )
        {

            // Auxiliar Matrix for the scaling //
            Mat timgRight, timgLeft;
            if( scale == 1 ){
                timgRight = auxRight;
                timgLeft = auxLeft;
            }
            else{
                resize(auxRight, timgRight, Size(), scale, scale, INTER_LINEAR_EXACT);
                resize(auxLeft, timgLeft, Size(), scale, scale, INTER_LINEAR_EXACT);
            }

            foundRight = findChessboardCorners(timgRight, this->_s.boardSize, cornersRight,
                                               CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);
            foundLeft = findChessboardCorners(timgLeft, this->_s.boardSize, cornersLeft,
                                              CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);

//            cout << "Found R: " << foundRight << endl;
//            cout << "Found L: " << foundLeft << endl;

            if(foundRight && foundLeft)
            {
                if( scale > 1 )
                {
                    Mat cornersMatRight(cornersRight);
                    Mat cornersMatLeft(cornersLeft);
                    cornersMatRight *= 1./scale;
                    cornersMatLeft *= 1./scale;
                }
                #if DEBUG_CALIB_STEREO
                    cout << "SteroCalib::_pairDetect(): Corners FOUND!\n";
                #endif
                break;
            }
        }

        // If found both chess pattern //
        if(foundRight && foundLeft)
        {
            cvtColor(auxRight, blackRight, COLOR_BGR2GRAY);
            cvtColor(auxLeft, blackLeft, COLOR_BGR2GRAY);

            cornerSubPix( blackRight, cornersRight, Size(11,11),
                          Size(-1,-1), TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));
            cornerSubPix( blackLeft, cornersLeft, Size(11,11),
                          Size(-1,-1), TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));

            // Draw the corners.
            drawChessboardCorners(auxRight, this->_s.boardSize, Mat(cornersRight), foundRight);
            drawChessboardCorners(auxLeft, this->_s.boardSize, Mat(cornersLeft), foundLeft);

            imshow("Right", auxRight);
            imshow("Left", auxLeft);

            // Take a keyboard command. If 's', than save. Else discart and run again //
            key = (char)waitKey();


            if(key == consts::s_KEY){
                cout << "SteroCalib::_pairDetect(): Calib\n";

                // So save corners if found! //
                imageRightPoints.push_back(cornersRight);
                imageLeftPoints.push_back(cornersLeft);

                // Save the image itself in GRAYSCALE //
                _goodImageCamera.push_back(blackRight);
                _goodImageCamera.push_back(blackLeft);
            }
            else if(key == consts::ESC_KEY)
            {
                _imagePoints[0].resize(i);
                _imagePoints[1].resize(i);
                break;
            }
            else{
                i--;
            }
        }
        else{
            i--;
        }
    }

    // Whatever if is the right(0) or left(1) position for imagePoints, they must be the same //
    nimages = (int)_imagePoints[0].size();

    _objectPoints.resize(nimages);

    int i, j, k;

    // Calculates the points of the Pattern (in this case the chessboard) //
    // It acts like a mask //
    for( i = 0; i < nimages; i++ )
    {
        for( j = 0; j < this->_s.boardSize.height; j++ )
            for( k = 0; k < this->_s.boardSize.width; k++ )
                _objectPoints[i].push_back(Point3f(k*this->_s.squareSize, j*this->_s.squareSize, 0));
    }

    cout << "Image Point Size: " << _imagePoints[0].size() << endl;
    for(i=0; i<_imagePoints[0].size(); i++)
    {

    }

    if(LOG_CALIB_STEREO){cout << "CalibStereo::_pairDetectCamera(): Finish_OK!\n";}
    return 0;
}

int CalibStereo::_calibCheck()
{
    if(LOG_CALIB_STEREO){cout << "CalibStereo::_calibCheck(): Start...\n";}

    double err = 0;
    int npoints = 0;
    vector<Vec3f> lines[2];

    for(int i = 0; i < nimages; i++ )
    {
        int npt = (int)_imagePoints[0][i].size();
        Mat imgpt[2];
        for(int k = 0; k < 2; k++ )
        {
            imgpt[k] = Mat(_imagePoints[k][i]);
            undistortPoints(imgpt[k], imgpt[k], _cameraMatrix[k], _distCoeffs[k], Mat(), _cameraMatrix[k]);
            computeCorrespondEpilines(imgpt[k], k+1, _F, lines[k]);
        }
        for(int j = 0; j < npt; j++ )
        {
            double errij = fabs(_imagePoints[0][i][j].x*lines[1][j][0] +
                    _imagePoints[0][i][j].y*lines[1][j][1] + lines[1][j][2]) +
                    fabs(_imagePoints[1][i][j].x*lines[0][j][0] +
                    _imagePoints[1][i][j].y*lines[0][j][1] + lines[0][j][2]);
            err += errij;
        }
        npoints += npt;
    }

    #if DEBUG_CALIB_STEREO
        cout << "Average epipolar err = " <<  err/npoints << endl;
    #endif
    if(LOG_CALIB_STEREO){cout << "CalibStereo::_calibCheck(): Finish_OK!\n";}

    return 0;
}

int CalibStereo::_calibStereoSaveCameraParam(){
    if(LOG_CALIB_STEREO){cout << "CalibStereo::_calibStereoSaveCameraParam(): Start...\n";}
    // save intrinsic parameters
    FileStorage fs(this->_s.outputCameraFilename, FileStorage::WRITE);

    if( fs.isOpened() )
    {
        fs << "MAP1_CAM1" << _mapCam1[0]
           << "MAP2_CAM1" << _mapCam1[1]
           << "MAP1_CAM2" << _mapCam2[0]
           << "MAP2_CAM2" << _mapCam2[1]
           << "ROI1" << _validRoi[0]
           << "ROI2" << _validRoi[1];
        fs.release();
    }
    else{
        cerr << "SteroCalib::_calibStereoSaveIntrinsicParam(): Error! Can'n save the intrinsic parameters\n";
        return -1;
    }

    if(LOG_CALIB_STEREO){cout << "CalibStereo::_calibStereoSaveCameraParam(): Finish_OK!\n";}
    return 0;
}

int CalibStereo::_calibStereoSaveIntrinsicParam(){
    if(LOG_CALIB_STEREO){cout << "CalibStereo::_calibStereoSaveIntrinsicParam(): Start...\n";}

    #if DEBUG_CALIB_STEREO
        cout << "################################################\n";
        cout << "SteroCalib::_calibStereoSaveIntrinsicParam(): Starting Saving Calib Parameters.....\n";
    #endif

    // save intrinsic parameters
    FileStorage fs(this->_s.outputIntrinsicFilename, FileStorage::WRITE);

    #if DEBUG_CALIB_STEREO
        cout << "SteroCalib::_calibStereoSaveIntrinsicParam(): Saving Parameters on file '" << this->_s.outputIntrinsicFilename << "'\n";
    #endif

    if(fs.isOpened())
    {
        fs << "M1" << _cameraMatrix[0] <<
              "D1" << _distCoeffs[0] <<
              "M2" << _cameraMatrix[1] <<
              "D2" << _distCoeffs[1];
        fs.release();
    }
    else{
        cerr << "SteroCalib::_calibStereoSaveIntrinsicParam(): Error! Can'n save the intrinsic parameters\n";
        return -1;
    }

    if(LOG_CALIB_STEREO){cout << "CalibStereo::_calibStereoSaveIntrinsicParam(): Finish_OK!\n";}
    return 0;
}

int CalibStereo::_calibStereoSaveRectificateOuputParam(){
    if(LOG_CALIB_STEREO){cout << "CalibStereo::_calibStereoSaveRectificateOuputParam(): Start...\n";}

    FileStorage fs(this->_s.outputExtrinsicFilename, FileStorage::WRITE);
    if( fs.isOpened() )
    {
        fs << "R" << _R
           << "T" << _T
           << "R1" << _R1
           << "R2" << _R2
           << "P1" << _P1
           << "P2" << _P2
           << "Q" << _Q
           << "ROI1" << _validRoi[0]
           << "ROI2" << _validRoi[1];
        fs.release();
    }
    else
    {
        cerr << "SteroCalib::_calibStereoSaveRectificateOuputParam() Error: can not save the extrinsic parameters\n";
        return -1;
    }

    if(LOG_CALIB_STEREO){cout << "CalibStereo::_calibStereoSaveRectificateOuputParam(): Finish_OK!\n";}
    return 0;
}

void CalibStereo::_showRectification()
{
    if(LOG_CALIB_STEREO){cout << "CalibStereo::_showRectification(): Start...\n";}

    #if DEBUG_CALIB_STEREO
        cout << "################################################\n";
        cout << "SteroCalib::_showRectification(): Starting Showing Rectification.....\n";
    #endif

    int i, j, k;

    Mat rmap[2][2];
    // IF BY CALIBRATED (BOUGUET'S METHOD)
    if(this->_s.useCalibrated )
    {
        // we already computed everything
    }
    // OR ELSE HARTLEY'S METHOD
    else
        // use intrinsic parameters of each camera, but
        // compute the rectification transformation directly
        // from the fundamental matrix
    {
        cerr << "CalibStereo::_showRectification(): Using different calibration.\n";
        vector<Point2f> allimgpt[2];
        for(k = 0; k < 2; k++ )
        {
            for(i = 0; i < nimages; i++ )
                std::copy(_imagePoints[k][i].begin(), _imagePoints[k][i].end(), back_inserter(allimgpt[k]));
        }
        _F = findFundamentalMat(Mat(allimgpt[0]), Mat(allimgpt[1]), FM_8POINT, 0, 0);
        Mat H1, H2;
        stereoRectifyUncalibrated(Mat(allimgpt[0]), Mat(allimgpt[1]), _F, imageSize, H1, H2, 3);

        _R1 = _cameraMatrix[0].inv()*H1*_cameraMatrix[0];
        _R2 = _cameraMatrix[1].inv()*H2*_cameraMatrix[1];
        _P1 = _cameraMatrix[0];
        _P2 = _cameraMatrix[1];
    }

    //Precompute maps for cv::remap()
    initUndistortRectifyMap(_cameraMatrix[0], _distCoeffs[0], _R1, _P1, imageSize, CV_16SC2, rmap[0][0], rmap[0][1]);
    initUndistortRectifyMap(_cameraMatrix[1], _distCoeffs[1], _R2, _P2, imageSize, CV_16SC2, rmap[1][0], rmap[1][1]);

    // OpenCV can handle left-right
    // or up-down camera arrangements
    bool isVerticalStereo = fabs(_P2.at<double>(1, 3)) > fabs(_P2.at<double>(0, 3));

    Mat canvas;
    double sf;
    int w, h;
    if( !isVerticalStereo )
    {
        sf = 600./MAX(imageSize.width, imageSize.height);
        w = cvRound(imageSize.width*sf);
        h = cvRound(imageSize.height*sf);
        canvas.create(h, w*2, CV_8UC3);
    }
    else
    {
        sf = 300./MAX(imageSize.width, imageSize.height);
        w = cvRound(imageSize.width*sf);
        h = cvRound(imageSize.height*sf);
        canvas.create(h*2, w, CV_8UC3);
    }

    Mat img, rimg, cimg;

    for( i = 0; i < nimages; i++ )
    {
        for( k = 0; k < 2; k++ )
        {
            if(_s.inputType == consts::CAMERA){
                img = _goodImageCamera.at(i*2+k);
            }
            else if(_s.inputType == consts::IMAGE_LIST){
                img = imread(_goodImageList[i*2+k], 0);
            }

            remap(img, rimg, rmap[k][0], rmap[k][1], INTER_LINEAR);
            cvtColor(rimg, cimg, COLOR_GRAY2BGR);

            Mat canvasPart = !isVerticalStereo ? canvas(Rect(w*k, 0, w, h)) : canvas(Rect(0, h*k, w, h));
            resize(cimg, canvasPart, canvasPart.size(), 0, 0, INTER_AREA);
            if( this->_s.useCalibrated )
            {
                Rect vroi(cvRound(_validRoi[k].x*sf), cvRound(_validRoi[k].y*sf),
                          cvRound(_validRoi[k].width*sf), cvRound(_validRoi[k].height*sf));
                rectangle(canvasPart, vroi, Scalar(0,0,255), 3, 8);
            }
        }

        if( !isVerticalStereo )
            for( j = 0; j < canvas.rows; j += 16 )
                line(canvas, Point(0, j), Point(canvas.cols, j), Scalar(0, 255, 0), 1, 8);
        else
            for( j = 0; j < canvas.cols; j += 16 )
                line(canvas, Point(j, 0), Point(j, canvas.rows), Scalar(0, 255, 0), 1, 8);
        imshow("rectified", canvas);
        char c = (char)waitKey();
        if( c == 27 || c == 'q' || c == 'Q' )
            break;
    }

    if(LOG_CALIB_STEREO){cout << "CalibStereo::_showRectification(): Finish_OK!\n";}
}

int CalibStereo::_loadExtrinsic(string filename){
    if(LOG_CALIB_STEREO){cout << "CalibStereo::_loadExtrinsic(): Start...\n";}

    // Load the configuration extrinsic matrix //
    FileStorage fs(filename, FileStorage::READ);

    if( !fs.isOpened() ){
        cerr << "CalibStereo::_loadExtrinsic(): Error on opening File" << endl;
        return -1;
    }


    fs["R"] >> _R;
    fs["T"] >> _T;
    fs["R1"] >> _R1;
    fs["R2"] >> _R2;
    fs["P1"] >> _P1;
    fs["P2"] >> _P2;
    fs["Q"] >> _Q;
    fs["ROI1"] >> _validRoi[0];
    fs["ROI2"] >> _validRoi[1];

    fs.release();

    if(_R.empty()){
        cerr << "CalibStereo::_loadIntrinsic(): Error on reading R matrix!\n";
        return -1;
    }
    if(_T.empty()){
        cerr << "CalibStereo::_loadIntrinsic(): Error on reading T matrix!\n";
        return -1;
    }
    if(_R1.empty()){
        cerr << "CalibStereo::_loadIntrinsic(): Error on reading R1 matrix!\n";
        return -1;
    }
    if(_R2.empty()){
        cerr << "CalibStereo::_loadIntrinsic(): Error on reading R2 matrix!\n";
        return -1;
    }
    if(_P1.empty()){
        cerr << "CalibStereo::_loadIntrinsic(): Error on reading P1 matrix!\n";
        return -1;
    }
    if(_P2.empty()){
        cerr << "CalibStereo::_loadIntrinsic(): Error on reading P2 matrix!\n";
        return -1;
    }
    if(_Q.empty()){
        cerr << "CalibStereo::_loadIntrinsic(): Error on reading Q matrix!\n";
        return -1;
    }

    if(LOG_CALIB_STEREO){cout << "CalibStereo::_loadExtrinsic(): Finish_OK!\n";}
    return 0;
}

int CalibStereo::_loadIntrinsic(string filename){
    if(LOG_CALIB_STEREO){cout << "CalibStereo::_loadIntrinsic(): Start...\n";}

    // Load the configuration matrix //
    FileStorage fs(filename, FileStorage::READ);

    if( !fs.isOpened() ){
        cerr << "CalibStereo::_loadIntrinsic(): Error on opening Camera Matrix File" << endl;
        return -1;
    }

    fs["M1"] >> _cameraMatrix[0];
    fs["M2"] >> _cameraMatrix[1];
    fs["D1"] >> _distCoeffs[0];
    fs["D2"] >> _distCoeffs[1];
    fs.release();

    if(_cameraMatrix[0].empty() || _cameraMatrix[1].empty()){
        cerr << "CalibStereo::_loadIntrinsic(): Error on reading camera matrix!\n";
        return -1;
    }
    if(_distCoeffs[0].empty() || _distCoeffs[1].empty()){
        cerr << "CalibStereo::_loadIntrinsic(): Error on reading distance coefficients!\n";
        return -1;
    }

    if(LOG_CALIB_STEREO){cout << "CalibStereo::_loadIntrinsic(): Finish_OK!\n";}
    return 0;
}
