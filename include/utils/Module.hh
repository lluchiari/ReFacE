#ifndef __MODULE_H__
#define __MODULE_H__

#include <Utils/common.h>
#include <Utils/Settings.hh>

using namespace std;
using namespace mySettings;

namespace myModule {
    class Module;
}

class myModule::Module : public QObject
{
    Q_OBJECT
public:
    virtual int config(string) = 0;
    virtual int run() = 0;
    virtual string getName(){return _name;}
    virtual ~Module()
    {
        if(_innerSetting != NULL){cout << "Module Setting Delete"; delete _innerSetting;}
    }

    /* The Name of the Module */
    string _name;
    consts::runMode _runMode;


protected:
    Settings *_innerSetting =NULL;
};

#endif //__MODULE_H__
