#ifndef __CALIBRATION_H__
#define __CALIBRATION_H__

/* QT Libs */
#include <QFileDialog>
#include <QWidget>
#include <QString>

/* STL Libs */
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>
#include <string>

/* OPENCV Libs */
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

/* Internal Libs */
#include <mainwindow.h>
#include <Settings/SettingsSingle.h>
#include <common.h>

class Calibration
{
public:
    Calibration(QWidget *);
    Calibration();
	~Calibration();

    int config(string, string, string);
    int config(string);
    int calibrate();

private:
    SettingsSingle _s;            //Setting file to be read by the funciton

    enum {
        DETECTION = 0,      // This mode takes the images direct from a file
        CAPTURING = 1,      // This mode is capturing images from the camera or image list
        CALIBRATED = 2      // This mode indicate that is already calibrated
    };

    string _inputSettingsFile;
    string _inputStackImageFile;
    string _OutputFileURL;

    bool runCalibrationAndSave(SettingsSingle&, Size, Mat&, Mat&, vector<vector<Point2f>>);
    void saveCameraParams( SettingsSingle&, Size&, Mat&, Mat&, const vector<Mat>&, const vector<Mat>&,
                                  const vector<float>&, const vector<vector<Point2f> >&, double);
    bool runCalibration( SettingsSingle&, Size&, Mat&, Mat&, vector<vector<Point2f>>, vector<Mat>&, vector<Mat>&,
                                vector<float>&,  double&);
};

#endif