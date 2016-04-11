#ifndef Logic_H
#define Logic_H

#include "ModuleHandler.h"
#include "Module.h"

#include "Menu.h"
#include "Clock.h"
#include "Stopwatch.h"
#include "AlarmClock.h"
#include "Timer.h"

class Logic
{
  public:
    Logic();
    void setup();
    void loop();
  private:    
    int buttonPinsSize = 3;
    int buttonPins[3] = {2, 3, 4};
    char battery[6];
    Adafruit_SSD1306 display;
    Buttons buttons;
    
    //Modules (passive)
    ModuleHandler moduleHandler;
    Menu menu;
    Clock clock;
    AlarmClock alarmclock;
    Stopwatch stopwatch;
    Timer timer;
    
    Module* modules[5] = { &menu, &clock, &alarmclock, &stopwatch, &timer };
    int modulesSize = 5;
    
    static time_t teensyTime();
    uint32_t getBatteryVoltage();
};

#endif
