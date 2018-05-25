#ifndef __MODULE_H__
#define __MODULE_H__

#include <utils/common.h>
#include <utils/Settings.hh>

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
    virtual ~Module() {}

    /* The Name of the Module */
    string _name;
    Settings *_innerSetting;
};


#endif __MODULE_H__
