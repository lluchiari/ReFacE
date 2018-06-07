#ifndef __CAMERA_CAPTURE_H__
#define __CAMERA_CAPTURE_H__

#include <Utils/common.h>
#include <Utils/consts.h>

// OpenCV Includes
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

namespace myCameraCapture {
    class CameraCapture;
}


/**
 * @brief The myCameraCapture::CameraCapture class for capturing images from the stereo rig and save it to the directory indicated
 * TODO: Implement the Image List generator
 */
class myCameraCapture::CameraCapture {
public:
    static int stereoCapture(string fileLocation, string defaultName, int camRightID, int camLeftID, bool generateList=false, string listFileLocation="")
    {
        VideoCapture rightCam, leftCam;
        vector<string> imagesFiles;
        string nameRight, nameLeft;
        Mat right, left;
        char key;
        int count=0;

        vector<int> compression_params;
        compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);

        //For PNG, it can be the compression level ( CV_IMWRITE_PNG_COMPRESSION ) from 0 to 9.
        //A higher value means a smaller size and longer compression time.
        compression_params.push_back(0);


        rightCam.open(camRightID);
        leftCam.open(camLeftID);
        if(!rightCam.isOpened()){
            cerr << "CameraCapture::stereoCapture(): Right Camera couldn't be opened\n";
            return -1;
        }
        if(!leftCam.isOpened()){
            cerr << "CameraCapture::stereoCapture(): Left Camera couldn't be opened\n";
            return -1;
        }

        for(int i=0;;i++)
        {
            cout << "CameraCapture::stereoCapture(): Capturing Image " << count << endl;
            do{
                rightCam.read(right);
                leftCam.read(left);

                imshow("Right", right);
                imshow("Left", left);

                key = (char) waitKey(10);
            }while(key != consts::t_KEY && key != consts::ESC_KEY);

            if(key == consts::ESC_KEY){break;}
            else if(key == t_KEY)
            {
                nameRight.clear();
                nameLeft.clear();

                nameRight.append(fileLocation+defaultName);
                nameLeft.append(fileLocation+defaultName);

                nameRight.append("Right");
                nameLeft.append("Left");

                nameRight.append(to_string(count));
                nameLeft.append(to_string(count));

                nameRight.append(".png");
                nameLeft.append(".png");

                try {
                    imwrite(nameRight, right, compression_params);
                    imwrite(nameLeft, left, compression_params);
                }
                catch (runtime_error& ex) {
                    cerr << "Exception converting image to PNG format: %s\n" << ex.what();
                    return -1;
                }

                imagesFiles.push_back(nameRight);
                imagesFiles.push_back(nameLeft);
                count++;

            }
            else{
                //Do nothing
                // Is the same as deleting and not save the image
            }
        }

        //Close camera //
        rightCam.release();
        leftCam.release();


        // Generate List //
        if(generateList){
            cout << "Generate List\n";
            if(listFileLocation.empty()){
                return -1;
            }

            FileStorage fs(listFileLocation, FileStorage::WRITE);
            if(fs.isOpened()){
                fs << "images" << imagesFiles;
                fs.release();
            }
            else{
                cerr << "CameraCapture::stereoCapture(): Error on opening list location";
                return -1;
            }

        }
        return 0;
    }
};

#endif
