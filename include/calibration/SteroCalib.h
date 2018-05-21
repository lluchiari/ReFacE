#ifndef __STEROCALIB_H__
#define __STEROCALIB_H__


// OpenCV Includes
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


// STL Includes
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Internal Libs
#include <Settings/SettingsStereo.h>

using namespace std;
using namespace cv;



class SteroCalib
{
public:
    SteroCalib();
public:
    int config(string);
    int calibrate();
    int rectificate();
    int load(string);

    int nimages;                                         // Variable to store the number of images in different steps of the program //
    const int maxScale = 2;                              // Scale value that the image migth be resized to search for pattern //
    cv::Size imageSize;                                  // Contains the size of the images pairs. Used to check if pairs have the same size //


private:
    /* Inner functions */
    int _pairDetect();                                   // Check the pairs of images and detects the detected points. //
    int _calibCheck();
    int _calibStereoSaveOutputParam();
    void _showRectification();

    /* Stereo Camera Parameters */
    Mat _cameraMatrix[2];                                // Stores the cameras matrix containing all the information for stereo process. //
    Mat _distCoeffs[2];                                  // Distortion coeficient matrix //
    Mat _R, _T, _E, _F;                                  // All the main matrix that describes the camera and the image system //

    /* Rectified coeficients for stereo matching */
    Mat _R1;                                             // Output 3x3 rectification transform (rotation matrix) for the first camera.
    Mat _R2;                                             // Output 3x3 rectification transform (rotation matrix) for the second camera.
    Mat _P1;                                             // Output 3x4 projection matrix in the new (rectified) coordinate systems for the first camera.
    Mat _P2;                                             // Output 3x4 projection matrix in the new (rectified) coordinate systems for the second camera.
    Mat _Q;                                              // Output 4x4 disparity-to-depth mapping matrix (see reprojectImageTo3D()).

    Rect _validRoi[2];
    bool _configFlag;
    double _rms;                                         // Erro for calibration
    vector<vector<Point2f> > _imagePoints[2];            // The corners of the chessboard found //
    vector<vector<Point3f> > _objectPoints;              // Vector of vectors containing the calibration pattern points. If changes the pattern, than changes the way this is calculated //
    vector<string> _goodImageList;                       // Vector containnig the path of good pair of images //


    SettingsStereo _s;                                   // Configuration object. Stores all the informations about the calibration. //
};

#endif // __STEROCALIB_H__
