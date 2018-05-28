#ifndef __MODULE_H__
#define __MODULE_H__

#include <utils/common.h>
#include <utils/Settings.hh>

using namespace std;
using namespace mySettings;

namespace myModule {
    class Module;
}

class myModule::Module
{
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

protected:
    Settings *_innerSetting =NULL;
};

#endif //__MODULE_H__
