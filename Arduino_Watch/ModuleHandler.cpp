#include <Arduino.h>

#include "Module.h"
#include "ModuleHandler.h"

ModuleHandler::ModuleHandler()
{
  currentModule = 1;
}

void ModuleHandler::setup(Module **rmodules, int rmoduleSize)
{
  modules = rmodules;
  moduleSize = rmoduleSize;
  //for (int i = 0; i < moduleSize; i++) modules[i]->setup();
}

void ModuleHandler::loop()
{
  currentModule = modules[currentModule]->getNextModule();

  if (!modules[currentModule]->isInit()) 
  {
    modules[currentModule]->setup();
    //Hacky fix prevents flick between 2 modules
    modules[currentModule]->setNextModule(currentModule);
    
    modules[currentModule]->setInit(true);
  }
  modules[currentModule]->loop();
}
