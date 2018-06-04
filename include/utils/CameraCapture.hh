#ifndef __CAMERA_CAPTURE_H__
#define __CAMERA_CAPTURE_H__


#include <utils/common.h>
#include <utils/consts.h>

// OpenCV Includes
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

namespace myCameraCapture{
    class CameraCapture;
}

class myCameraCapture::CameraCapture {
public:
    static int stereoCapture(string fileLocation, string defaultName, int camRightID, int camLeftID, bool generateList=false, string listFileLocation="")
    {
        VideoCapture rightCam, leftCam;
        vector<Mat> images;
        vector<string> imagesFiles;
        string auxName = "";
        Mat right, left;
        char key;

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
            cout << "CameraCapture::stereoCapture(): Capturing Image " << images.size() << endl;
            do{
                rightCam >> right ;
                leftCam >> left ;

                imshow("Right", right);
                imshow("Left", left);

                key = (char) waitKey(10);
            }while(key != consts::t_KEY && key != consts::ESC_KEY);

            if(key == consts::ESC_KEY){break;}
            else if(key == t_KEY)
            {
                images.push_back(right);
                images.push_back(left);
            }
            else{
                //Do nothing
                // Is the same as deleting and not save the image
            }
        }

        //Saving loop //
        cout << "CameraCapture::stereoCapture(): Saving:\n";
        for(int i=0; i<images.size()/2; i++)
        {
            for(int k=0;k<2;k++)
            {
                auxName.clear();
                auxName.append(fileLocation+defaultName);
                if(k==0){auxName.append("Right");}
                else{auxName.append("Left");}
                auxName.append(to_string(i));
                auxName.append(".png");

                cout << "\t" << auxName << endl;
                imagesFiles.push_back(auxName);

                try {
                    imshow("Saving", images.at(i*2+k));
                    waitKey();
                    imwrite(auxName, images.at(i*2+k), compression_params);
                }
                catch (runtime_error& ex) {
                    cerr << "Exception converting image to PNG format: %s\n" << ex.what();
                    return -1;
                }
            }
            cout << endl;
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
