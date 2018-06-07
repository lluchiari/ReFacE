#ifndef __CONNECTION_HH__
#define __CONNECTION_HH__

#include <Utils/common.h>
#include <Utils/consts.h>
#include <Utils/Module.hh>

using namespace cv;
using namespace std;
using namespace myModule;

namespace myConnection{
    class Connection;
    class Connector;
}

class myConnection::Connection : public Module
{
    Q_OBJECT

public:
    Connection(){}
    virtual ~Connection(){}


signals:
    void view_Input(Mat);

public slots:
    virtual void match_Output(Mat){}


private:
    Mat _matchOut;              // Output from Match Module
};


#endif //__CONNECTION_HH__
