#include <SteroCalib.h>

SteroCalib::SteroCalib()
{
    _configFlag = false;
}

int SteroCalib::config(string configFile)
{
    if(DEBUG_CALIBRATION_STEREO){
        cout << "Configurating....\n";
    }
    this->_s.read(configFile);
    this->_s.interprate();
    _configFlag = true;
    return 0;
}

int SteroCalib::calibrate()
{
    if(DEBUG_CALIBRATION_STEREO){
        cout << "Calibrating...\n";
    }

    // Check if the configuration was previously done //
    if(!_configFlag){
        cerr << "StereoCalib::calibrate(): Please run config() method first!\n";
        return -1;
    }

    // Check if the image list contain correct files //
    // Find the pattern points in the image //
    if(this->_pairDetect() != 0){
        cerr << "SteroCalib::calibrate(): Error on the list image pair detection,"
             << "please verify your image and configuration files.\n";
        return -1;
    }

    if(DEBUG_CALIBRATION_STEREO)
    {
        cout << "Running stereo calibration ...\n";
    }

    _cameraMatrix[0] = initCameraMatrix2D(_objectPoints,_imagePoints[0],imageSize,0);
    _cameraMatrix[1] = initCameraMatrix2D(_objectPoints,_imagePoints[1],imageSize,0);

    double rms = stereoCalibrate(_objectPoints, _imagePoints[0], _imagePoints[1],
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

    if(DEBUG_CALIBRATION_STEREO)
    {
        cout << "Done with RMS error=" << rms << endl;
    }

    // CALIBRATION QUALITY CHECK
    // because the output fundamental matrix implicitly
    // includes all the output information,
    // we can check the quality of calibration using the
    // epipolar geometry constraint: m2^t*F*m1=0
    _calibCheck();


    // Save the output parameters in the file //
    _calibStereoSaveOutputParam();

    if(DEBUG_CALIBRATION_STEREO)
    {
        cout << "End of Calibration! Everything is fine!\n";
    }
    return 0;
}

int SteroCalib::rectificate()
{
    Rect validRoi[2];

    stereoRectify(_cameraMatrix[0], _distCoeffs[0],
            _cameraMatrix[1], _distCoeffs[1],
            imageSize, _R, _T, _R1, _R2, _P1, _P2, _Q,
            CALIB_ZERO_DISPARITY, 1, imageSize, &validRoi[0], &validRoi[1]);


    FileStorage fs(this->_s.outputFileName, FileStorage::WRITE);
    if( fs.isOpened() )
    {
        fs << "R" << _R << "T" << _T << "R1" << _R1 << "R2" << _R2 << "P1" << _P1 << "P2" << _P2 << "Q" << _Q;
        fs.release();
    }
    else
    {
        cout << "SteroCalib::rectificate() Error: can not save the extrinsic parameters\n";
        return -1;
    }

    // COMPUTE AND DISPLAY RECTIFICATION
    if(this->_s._showRectified)
    {
       _showRectification();
    }

    if(DEBUG_CALIBRATION_STEREO){
        cout << "End of Rectification!\n";
    }
    return 0;
}

int SteroCalib::_pairDetect()
{

    vector<string>& imagelist = this->_s._imageList;

    // Check if the image list is odd //
    if( imagelist.size() % 2 != 0 )
    {
        cout << "SteroCalib::_pairDetect(): Error! The image list contains odd (non-even) number of elements\n";
        return -1;
    }

    // ARRAY AND VECTOR STORAGE:
    _imagePoints[0].resize(nimages);
    _imagePoints[1].resize(nimages);

    // i is the image list iterator
    // j is the seccess image identified
    // k represents the right and left images iterator
    int i, j, k;
    nimages = (int)imagelist.size()/2;

    // This for iterates the images list and check if there is a correspondent
    // pair of image and detects the corner in these images
    for( i = j = 0; i < nimages; i++ )
    {
        for( k = 0; k < 2; k++ )
        {
            const string& filename = imagelist[i*2+k];
            Mat img = imread(filename, 0);
            if(img.empty())
                break;
            if( this->_s._boardSize == Size() )
            {
                imageSize = img.size();
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
                if( scale == 1 )
                    timg = img;
                else
                    resize(img, timg, Size(), scale, scale, INTER_LINEAR_EXACT);
                found = findChessboardCorners(timg, this->_s._boardSize, corners,
                                              CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);
                if( found )
                {
                    if( scale > 1 )
                    {
                        Mat cornersMat(corners);
                        cornersMat *= 1./scale;
                    }
                    break;
                }
            }

            // Debug of points//
            if(this->_s._displayCorners)
            {
                cout << filename << endl;
                Mat cimg, cimg1;
                cvtColor(img, cimg, COLOR_GRAY2BGR);
                drawChessboardCorners(cimg, this->_s._boardSize, corners, found);
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
            if( !found )
                break;
            cornerSubPix(img, corners, Size(11,11), Size(-1,-1),
                         TermCriteria(TermCriteria::COUNT+TermCriteria::EPS,
                                      30, 0.01));
        }

        // Stores the good pair of images  //
        if( k == 2 )
        {
            _goodImageList.push_back(imagelist[i*2]);
            _goodImageList.push_back(imagelist[i*2+1]);
            j++;
        }
    }


    if(DEBUG_CALIBRATION_STEREO) {cout << j << " pairs have been successfully detected.\n";}

    // Number of pair of images correctlly detected //
    nimages = j;
    if( nimages < 2 )
    {
        std::cout << "SteroCalib::_pairDetect(): Error! Too little pairs to run the calibration\n";
        return -1;
    }

    _imagePoints[0].resize(nimages);
    _imagePoints[1].resize(nimages);
    _objectPoints.resize(nimages);

    // Calculates the points of the Pattern (in this case the chessboard) //
    // It acts like a mask //
    for( i = 0; i < nimages; i++ )
    {
        for( j = 0; j < this->_s._boardSize.height; j++ )
            for( k = 0; k < this->_s._boardSize.width; k++ )
                _objectPoints[i].push_back(Point3f(k*this->_s._squareSize, j*this->_s._squareSize, 0));
    }

   return 0;

}

int SteroCalib::_calibCheck()
{
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

    if(DEBUG_CALIBRATION_STEREO)
    {
        cout << "Average epipolar err = " <<  err/npoints << endl;
    }

    return 0;
}

int SteroCalib::_calibStereoSaveOutputParam(){
    // save intrinsic parameters
    FileStorage fs("intrinsics.yml", FileStorage::WRITE);
    if( fs.isOpened() )
    {
        fs << "M1" << _cameraMatrix[0] << "D1" << _distCoeffs[0] <<
              "M2" << _cameraMatrix[1] << "D2" << _distCoeffs[1];
        fs.release();
        return 0;
    }
    else{

        cout << "SteroCalib::_calibStereoSaveOutputParam(): Error! Can'n save the intrinsic parameters\n";
        return -1;
    }
}

void SteroCalib::_showRectification()
{
//    Mat rmap[2][2];
//    // IF BY CALIBRATED (BOUGUET'S METHOD)
//    if(this->_s._useCalibrated )
//    {
//        // we already computed everything
//    }
//    // OR ELSE HARTLEY'S METHOD
//    else
//        // use intrinsic parameters of each camera, but
//        // compute the rectification transformation directly
//        // from the fundamental matrix
//    {
//        vector<Point2f> allimgpt[2];
//        for( k = 0; k < 2; k++ )
//        {
//            for( i = 0; i < nimages; i++ )
//                std::copy(_imagePoints[k][i].begin(), _imagePoints[k][i].end(), back_inserter(allimgpt[k]));
//        }
//        F = findFundamentalMat(Mat(allimgpt[0]), Mat(allimgpt[1]), FM_8POINT, 0, 0);
//        Mat H1, H2;
//        stereoRectifyUncalibrated(Mat(allimgpt[0]), Mat(allimgpt[1]), F, imageSize, H1, H2, 3);

//        R1 = cameraMatrix[0].inv()*H1*cameraMatrix[0];
//        R2 = cameraMatrix[1].inv()*H2*cameraMatrix[1];
//        P1 = cameraMatrix[0];
//        P2 = cameraMatrix[1];
//    }

//    //Precompute maps for cv::remap()
//    initUndistortRectifyMap(cameraMatrix[0], distCoeffs[0], R1, P1, imageSize, CV_16SC2, rmap[0][0], rmap[0][1]);
//    initUndistortRectifyMap(cameraMatrix[1], distCoeffs[1], R2, P2, imageSize, CV_16SC2, rmap[1][0], rmap[1][1]);

//    // OpenCV can handle left-right
//    // or up-down camera arrangements
//    bool isVerticalStereo = fabs(_P2.at<double>(1, 3)) > fabs(_P2.at<double>(0, 3));

//    Mat canvas;
//    double sf;
//    int w, h;
//    if( !isVerticalStereo )
//    {
//        sf = 600./MAX(imageSize.width, imageSize.height);
//        w = cvRound(imageSize.width*sf);
//        h = cvRound(imageSize.height*sf);
//        canvas.create(h, w*2, CV_8UC3);
//    }
//    else
//    {
//        sf = 300./MAX(imageSize.width, imageSize.height);
//        w = cvRound(imageSize.width*sf);
//        h = cvRound(imageSize.height*sf);
//        canvas.create(h*2, w, CV_8UC3);
//    }

//    for( i = 0; i < nimages; i++ )
//    {
//        for( k = 0; k < 2; k++ )
//        {
//            Mat img = imread(goodImageList[i*2+k], 0), rimg, cimg;
//            remap(img, rimg, rmap[k][0], rmap[k][1], INTER_LINEAR);
//            cvtColor(rimg, cimg, COLOR_GRAY2BGR);
//            Mat canvasPart = !isVerticalStereo ? canvas(Rect(w*k, 0, w, h)) : canvas(Rect(0, h*k, w, h));
//            resize(cimg, canvasPart, canvasPart.size(), 0, 0, INTER_AREA);
//            if( useCalibrated )
//            {
//                Rect vroi(cvRound(validRoi[k].x*sf), cvRound(validRoi[k].y*sf),
//                          cvRound(validRoi[k].width*sf), cvRound(validRoi[k].height*sf));
//                rectangle(canvasPart, vroi, Scalar(0,0,255), 3, 8);
//            }
//        }

//        if( !isVerticalStereo )
//            for( j = 0; j < canvas.rows; j += 16 )
//                line(canvas, Point(0, j), Point(canvas.cols, j), Scalar(0, 255, 0), 1, 8);
//        else
//            for( j = 0; j < canvas.cols; j += 16 )
//                line(canvas, Point(j, 0), Point(j, canvas.rows), Scalar(0, 255, 0), 1, 8);
//        imshow("rectified", canvas);
//        char c = (char)waitKey();
//        if( c == 27 || c == 'q' || c == 'Q' )
//            break;
//    }
}
