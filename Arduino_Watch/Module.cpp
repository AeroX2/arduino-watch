#include <Arduino.h>
#include "Module.h"

void Module::setup() { nextModule = 0; init = false; }
void Module::loop() {}
int Module::getNextModule() { return nextModule; }
void Module::setNextModule(int module) { nextModule = module; init = false; }
boolean Module::isInit() { return init; }
void Module::setInit(int rinit) { init = rinit; }
