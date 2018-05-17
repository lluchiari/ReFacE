#include <Calibration.h>


Calibration::Calibration()
{
}

Calibration::~Calibration()
{
}


/**
 * @brief read the configuration file to configure the calibration
 * @return (0) if ok. (-1) if any error occured
 */
int Calibration::config(string inputFile, string stackFile, string outFile)
{
    // Read the settings
    //    FileStorage fs(inputSettingsFile, FileStorage::READ);
    //    if (!fs.isOpened())
    //    {
    //        cout << "Could not open the configuration file: \"" << inputSettingsFile << "\"" << endl;
    //        return -1;
    //    }
    //    fs["Settings"] >> (this->_s);

    //    // Close Settings file
    //    fs.release();

    // Read Configuration File
    this->_s.read(inputFile);
    this->_s.setStackImage(stackFile);
    this->_s.setOutputFile(outFile);

    // Check if the input is valid
    this->_s.interprate();

if(DEBUG_CALIBRATION){cout << "After Read" << endl;}

    // Check if the configure file process is good
    if (!this->_s.goodInput)
    {
        cerr << "Invalid input detected. Application stopping. " << std::endl;
        return -1;
    }

    return 0;
}

/**
 * @brief read the configuration file to configure the calibration
 * @return (0) if ok. (-1) if any error occured
 */
int Calibration::config(string inputFile){

    this->_s.read(inputFile);
    // Check if the input is valid
    this->_s.interprate();

    // Check if the configure file process is good
    if (!this->_s.goodInput)
    {
        cerr << "Invalid input detected. Application stopping. " << std::endl;
        return -1;
    }

    return 0;
}

int Calibration::calibrate() {

    vector<vector<Point2f> > imagePoints;       // Vector containig the points of each image
    Mat cameraMatrix;                           //
    Mat distCoeffs;                             //
    Size imageSize;                             //

    // Verify the input mode from the setting file
    int mode = (this->_s.inputType == SettingsSingle::IMAGE_LIST) ? CAPTURING : DETECTION;
    if(DEBUG_CALIBRATION) {cout << "Calibration::calibrate(): Mode " << ((mode == CAPTURING) ? "CAPTURING" : "DETECTION") << endl;}

    clock_t prevTimestamp = 0;

    //These are color for the message to the user
    const Scalar RED(0,0,255), GREEN(0,255,0);

    //Escape key to finish the program
    const char ESC_KEY = 27;
    for(int i=0;;i++)
    {
        if(DEBUG_CALIBRATION)
        {
            cout << "______________Loop Start i=" << i << "_______________" << endl;
        }
        Mat view;
        bool blinkOutput = false;

        view = this->_s.nextImage();

        //If no more image, or got enough, then stop calibration and show result
        if( mode == CAPTURING && imagePoints.size() >= (unsigned)this->_s.nrFrames )
        {
            if(DEBUG_CALIBRATION) {cout << "calibrate(1)" << endl;}
            if(this->runCalibrationAndSave(this->_s, imageSize,  cameraMatrix, distCoeffs, imagePoints))
                mode = CALIBRATED;
            else
                mode = DETECTION;
        }

        // If no more images then run calibration, save and stop loop.
        if(view.empty())
        {
            if(DEBUG_CALIBRATION) {cout << "calibrate(2)" << endl;}
            if(mode != CALIBRATED && !imagePoints.empty()){
                if(DEBUG_CALIBRATION) {cout << "calibrate(2.1)" << endl;}
                this->runCalibrationAndSave(this->_s, imageSize,  cameraMatrix, distCoeffs, imagePoints);
            }
            break;
        }

        // Format input image.
        imageSize = view.size();

        if(this->_s.flipVertical){
            if(DEBUG_CALIBRATION) {cout << "calibrate(3)" << endl;}
            flip( view, view, 0 );
        }

        vector<Point2f> pointBuf;

        bool found;

        // Find feature points on the input format
        switch(this->_s.calibrationPattern )
        {
        case SettingsSingle::CHESSBOARD:
            if(DEBUG_CALIBRATION) {cout << "Case CHESSBOARD" << endl;}
            found = findChessboardCorners( view, this->_s.boardSize, pointBuf,
                                           CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
            break;
        case SettingsSingle::CIRCLES_GRID:
            if(DEBUG_CALIBRATION) {cout << "Case CIRCLES_GRID" << endl;}
            found = findCirclesGrid( view, this->_s.boardSize, pointBuf );
            break;
        case SettingsSingle::ASYMMETRIC_CIRCLES_GRID:
            if(DEBUG_CALIBRATION) {cout << "Case ASYMMETRIC_CIRCLES_GRID" << endl;}
            found = findCirclesGrid( view, this->_s.boardSize, pointBuf, CALIB_CB_ASYMMETRIC_GRID );
            break;
        case SettingsSingle::NOT_EXISTING:
            if(DEBUG_CALIBRATION) {cout << "Case NOT_EXISTING" << endl;}
            found = false;
            break;
        }

        // If find pattern with success...
        if (found)
        {
            if(DEBUG_CALIBRATION) {cout << "calibrate(4)" << endl;}
            // improve the found corners' coordinate accuracy for chessboard
            if( this->_s.calibrationPattern == SettingsSingle::CHESSBOARD)
            {
                if(DEBUG_CALIBRATION) {cout << "calibrate(4.1)" << endl;}
                Mat viewGray;
                cvtColor(view, viewGray, COLOR_BGR2GRAY);
                cornerSubPix( viewGray, pointBuf, Size(11,11),
                              Size(-1,-1), TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));
            }

            // For camera only take new samples after delay time
            if( mode == CAPTURING &&
                    (!this->_s.inputCapture.isOpened() || (clock() - prevTimestamp) > this->_s.delay*1e-3*CLOCKS_PER_SEC) )
            {
                if(DEBUG_CALIBRATION) {cout << "calibrate(4.2)" << endl;}
                imagePoints.push_back(pointBuf);
                prevTimestamp = clock();
                blinkOutput = this->_s.inputCapture.isOpened();
            }

            // Draw the corners.
            drawChessboardCorners( view, this->_s.boardSize, Mat(pointBuf), found);
        }
        if(DEBUG_CALIBRATION) {cout << "calibrate(5)" << endl;}
        //----------------------------- Output Text ------------------------------------------------
        string msg = (mode == CAPTURING) ? "100/100" :
                                           mode == CALIBRATED ? "Calibrated" : "Press 'g' to start";
        int baseLine = 0;
        Size textSize = getTextSize(msg, 1, 1, 1, &baseLine);
        Point textOrigin(view.cols - 2*textSize.width - 10, view.rows - 2*baseLine - 10);

        if( mode == CAPTURING )
        {
            if(DEBUG_CALIBRATION) {cout << "calibrate(6)" << endl;}
            if(this->_s.showUndistorsed)
                msg = format( "%d/%d Undist", (int)imagePoints.size(), this->_s.nrFrames );
            else
                msg = format( "%d/%d", (int)imagePoints.size(), this->_s.nrFrames );
        }

        putText( view, msg, textOrigin, 1, 1, mode == CALIBRATED ?  GREEN : RED);

        if( blinkOutput )
            if(DEBUG_CALIBRATION) {cout << "calibrate(7)" << endl;}
            bitwise_not(view, view);

        //------------------------- Video capture  output  undistorted ------------------------------
        if( mode == CALIBRATED && this->_s.showUndistorsed )
        {
            if(DEBUG_CALIBRATION) {cout << "calibrate(8)" << endl;}
            Mat temp = view.clone();
            undistort(temp, view, cameraMatrix, distCoeffs);
            if(DEBUG_CALIBRATION) {cout << "calibrate(8.1)" << endl;}
        }

        //------------------------------ Show image and check for input commands -------------------
        imshow("Image View", view);
        if(DEBUG_CALIBRATION) {cout << "calibrate(9)" << endl;}
        char key = (char)waitKey(this->_s.inputCapture.isOpened() ? 50 : this->_s.delay);
        if(DEBUG_CALIBRATION) {cout << "calibrate(10)" << endl;}

        if( key  == ESC_KEY ){
            if(DEBUG_CALIBRATION) {cout << "calibrate(11)" << endl;}
            break;
        }

        if( key == 'u' && mode == CALIBRATED ){
            if(DEBUG_CALIBRATION) {cout << "calibrate(12)" << endl;}
            this->_s.showUndistorsed = !this->_s.showUndistorsed;
        }

        if( this->_s.inputCapture.isOpened() && key == 'g' )
        {
            if(DEBUG_CALIBRATION) {cout << "calibrate(13)" << endl;}
            mode = CAPTURING;
            imagePoints.clear();
        }
    }
    if(DEBUG_CALIBRATION) {cout << "End of calibrate" << endl;}
    return 0;
}

/**
 * @brief runCalibrationAndSave is a function that
 * @param s is the setting file doccument loaded before
 * @param imageSize
 * @param cameraMatrix
 * @param distCoeffs
 * @param imagePoints
 * @return
 */
bool Calibration::runCalibrationAndSave(SettingsSingle& s, Size imageSize, Mat&  cameraMatrix,
                                        Mat& distCoeffs, vector<vector<Point2f>> imagePoints )
{
    vector<Mat> rvecs, tvecs;
    vector<float> reprojErrs;
    double totalAvgErr = 0;

    bool ok = this->runCalibration(s,imageSize, cameraMatrix, distCoeffs, imagePoints, rvecs, tvecs, reprojErrs, totalAvgErr);
    cout << (ok ? "Calibration succeeded" : "Calibration failed")
         << ". avg re projection error = "  << totalAvgErr ;

    if( ok )
        this->saveCameraParams( s, imageSize, cameraMatrix, distCoeffs, rvecs ,tvecs,
                                reprojErrs, imagePoints, totalAvgErr);
    return ok;
}

double computeReprojectionErrors( const vector<vector<Point3f> >& objectPoints,
                                  const vector<vector<Point2f> >& imagePoints,
                                  const vector<Mat>& rvecs, const vector<Mat>& tvecs,
                                  const Mat& cameraMatrix , const Mat& distCoeffs,
                                  vector<float>& perViewErrors)
{
    vector<Point2f> imagePoints2;
    int i, totalPoints = 0;
    double totalErr = 0, err;
    perViewErrors.resize(objectPoints.size());

    for( i = 0; i < (int)objectPoints.size(); ++i )
    {
        projectPoints( Mat(objectPoints[i]), rvecs[i], tvecs[i], cameraMatrix,
                       distCoeffs, imagePoints2);
        err = norm(Mat(imagePoints[i]), Mat(imagePoints2), CV_L2);

        int n = (int)objectPoints[i].size();
        perViewErrors[i] = (float) std::sqrt(err*err/n);
        totalErr        += err*err;
        totalPoints     += n;
    }

    return std::sqrt(totalErr/totalPoints);
}

void calcBoardCornerPositions(Size boardSize, float squareSize, vector<Point3f>& corners,
                              SettingsSingle::Pattern patternType /*= SettingsSingle::CHESSBOARD*/)
{
    corners.clear();

    switch(patternType)
    {
    case SettingsSingle::CHESSBOARD:
    case SettingsSingle::CIRCLES_GRID:
        for( int i = 0; i < boardSize.height; ++i )
            for( int j = 0; j < boardSize.width; ++j )
                corners.push_back(Point3f(float( j*squareSize ), float( i*squareSize ), 0));
        break;

    case SettingsSingle::ASYMMETRIC_CIRCLES_GRID:
        for( int i = 0; i < boardSize.height; i++ )
            for( int j = 0; j < boardSize.width; j++ )
                corners.push_back(Point3f(float((2*j + i % 2)*squareSize), float(i*squareSize), 0));
        break;
    default:
        break;
    }
}

bool Calibration::runCalibration( SettingsSingle& s, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs,
                                  vector<vector<Point2f> > imagePoints, vector<Mat>& rvecs, vector<Mat>& tvecs,
                                  vector<float>& reprojErrs,  double& totalAvgErr)
{

    cameraMatrix = Mat::eye(3, 3, CV_64F);
    if( s.flag & CV_CALIB_FIX_ASPECT_RATIO )
        cameraMatrix.at<double>(0,0) = 1.0;

    distCoeffs = Mat::zeros(8, 1, CV_64F);

    vector<vector<Point3f> > objectPoints(1);
    calcBoardCornerPositions(s.boardSize, s.squareSize, objectPoints[0], s.calibrationPattern);

    objectPoints.resize(imagePoints.size(),objectPoints[0]);

    //Find intrinsic and extrinsic camera parameters
    double rms = calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix,
                                 distCoeffs, rvecs, tvecs, s.flag|CV_CALIB_FIX_K4|CV_CALIB_FIX_K5);

    cout << "Re-projection error reported by calibrateCamera: "<< rms << endl;

    bool ok = checkRange(cameraMatrix) && checkRange(distCoeffs);

    totalAvgErr = computeReprojectionErrors(objectPoints, imagePoints,
                                            rvecs, tvecs, cameraMatrix, distCoeffs, reprojErrs);

    return ok;
}

/**
 * @brief saveCameraParams print camera parameters to the output file
 * @param s
 * @param imageSize
 * @param cameraMatrix
 * @param distCoeffs
 * @param rvecs
 * @param tvecs
 * @param reprojErrs
 * @param imagePoints
 * @param totalAvgErr
 */
void Calibration::saveCameraParams( SettingsSingle& s, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs,
                                    const vector<Mat>& rvecs, const vector<Mat>& tvecs,
                                    const vector<float>& reprojErrs, const vector<vector<Point2f> >& imagePoints,
                                    double totalAvgErr )
{
    FileStorage fs( s.outputFileName, FileStorage::WRITE );

    time_t tm;
    time( &tm );
    struct tm *t2 = localtime( &tm );
    char buf[1024];
    strftime( buf, sizeof(buf)-1, "%c", t2 );

    fs << "calibration_Time" << buf;

    if( !rvecs.empty() || !reprojErrs.empty() )
        fs << "nrOfFrames" << (int)std::max(rvecs.size(), reprojErrs.size());
    fs << "image_Width" << imageSize.width;
    fs << "image_Height" << imageSize.height;
    fs << "board_Width" << s.boardSize.width;
    fs << "board_Height" << s.boardSize.height;
    fs << "square_Size" << s.squareSize;

    if( s.flag & CV_CALIB_FIX_ASPECT_RATIO )
        fs << "FixAspectRatio" << s.aspectRatio;

    if( s.flag )
    {
        sprintf( buf, "flags: %s%s%s%s",
                 s.flag & CV_CALIB_USE_INTRINSIC_GUESS ? " +use_intrinsic_guess" : "",
                 s.flag & CV_CALIB_FIX_ASPECT_RATIO ? " +fix_aspectRatio" : "",
                 s.flag & CV_CALIB_FIX_PRINCIPAL_POINT ? " +fix_principal_point" : "",
                 s.flag & CV_CALIB_ZERO_TANGENT_DIST ? " +zero_tangent_dist" : "" );
        cvWriteComment( *fs, buf, 0 );

    }

    fs << "flagValue" << s.flag;

    fs << "Camera_Matrix" << cameraMatrix;
    fs << "Distortion_Coefficients" << distCoeffs;

    fs << "Avg_Reprojection_Error" << totalAvgErr;
    if( !reprojErrs.empty() )
        fs << "Per_View_Reprojection_Errors" << Mat(reprojErrs);

    if( !rvecs.empty() && !tvecs.empty() )
    {
        CV_Assert(rvecs[0].type() == tvecs[0].type());
        Mat bigmat((int)rvecs.size(), 6, rvecs[0].type());
        for( int i = 0; i < (int)rvecs.size(); i++ )
        {
            Mat r = bigmat(Range(i, i+1), Range(0,3));
            Mat t = bigmat(Range(i, i+1), Range(3,6));

            CV_Assert(rvecs[i].rows == 3 && rvecs[i].cols == 1);
            CV_Assert(tvecs[i].rows == 3 && tvecs[i].cols == 1);
            //*.t() is MatExpr (not Mat) so we can use assignment operator
            r = rvecs[i].t();
            t = tvecs[i].t();
        }
        cvWriteComment( *fs, "a set of 6-tuples (rotation vector + translation vector) for each view", 0 );
        fs << "Extrinsic_Parameters" << bigmat;
    }

    if( !imagePoints.empty() )
    {
        Mat imagePtMat((int)imagePoints.size(), (int)imagePoints[0].size(), CV_32FC2);
        for( int i = 0; i < (int)imagePoints.size(); i++ )
        {
            Mat r = imagePtMat.row(i).reshape(2, imagePtMat.cols);
            Mat imgpti(imagePoints[i]);
            imgpti.copyTo(r);
        }
        fs << "Image_points" << imagePtMat;
    }
}
