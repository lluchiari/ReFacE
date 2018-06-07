#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include <Utils/common.h>
#include <Utils/consts.h>
#include <Utils/Module.hh>
#include <Modules/Connection/Connection.hh>

using namespace cv;
using namespace std;
using namespace myModule;
using namespace myConnection;

class myConnection::Connector : public Connection
{
    Q_OBJECT

public:
    Connector();
    ~Connector();


    // Module Inheritance //
    int config(string);
    int run();



signals:
    void view_Input(Mat);

public slots:
    void match_Output(Mat);


private:
    Mat _matchOut;              // Output from Match Module
};


#endif //__CONNECTOR_H__
