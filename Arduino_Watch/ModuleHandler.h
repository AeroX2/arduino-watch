#ifndef ModuleHandler_H
#define ModuleHandler_H

#include "Module.h"

class ModuleHandler
{
  public:
    ModuleHandler();
    void setup(Module **rmodules, int rmoduleSize);
    void loop();
  private:
    Module **modules;
    int moduleSize;
    int currentModule;
};
    
#endif
