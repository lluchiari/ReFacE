#ifndef __SETTINGS_H__
#define __SETTINGS_H__

/* Internal Libs */
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>

#include <opencv2/core/persistence.hpp>

using namespace std;
using namespace cv;

namespace mySettings {
    class Settings;
}

class mySettings::Settings
{
public:

    virtual int read(string) = 0;
    virtual int interprate() = 0;
    virtual int print() =0;
    virtual ~Settings(){}

    /**
     * @brief Settings::readStringList Read the xml file containing the list of images
     * @param filename is the path of the xml file
     * @param l is the list where the images will be saved
     * @return true if everything is ok. False otherwise
     * @author OpenCV Library
     */
    static bool readStringList( const string& filename, vector<string>& l )
    {
        l.clear();
        FileStorage fs(filename, FileStorage::READ);
        if( !fs.isOpened() ){
            cerr << "Settings::readStringList: Error on opening Stacks File" << endl;
            return false;
        }
        FileNode n = fs.getFirstTopLevelNode();
        if( n.type() != FileNode::SEQ ){
            cerr << "Settings::readStringList: Error! Incorrect Syntax on file or File is not a sequence." << endl;
            return false;
        }
        FileNodeIterator it = n.begin(), it_end = n.end();
        for( ; it != it_end; ++it ){
            l.push_back((string)*it);
        }
        return true;
    }

    static bool isListOfImages( const string& filename)
    {
        string s(filename);

        // Look for file extension
        if(s.find(".xml") == string::npos)
        {
            cerr << "Settings::isListOfImages(): File extension is incorrect!" << endl;
            return false;
        }
        else{
            return true;
        }
    }

};

#endif // SETTINGS_H
