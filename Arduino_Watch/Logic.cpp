//Dependencies
#include <Wire.h>
#include <SPI.h>

//Display
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Time
#include <Time.h>
#include <TimeAlarms.h>
#include <string.h>

//Buttons
#include <Buttons.h>

//Include Modules Dependencies
#include "Module.h"
#include "ModuleHandler.h"

//Include Modules
#include "Clock.h"
#include "Menu.h"
#include "AlarmClock.h"
#include "Timer.h"
#include "Stopwatch.h"

#include "Logic.h"

//Ugly but unsure how to do otherwise
Logic::Logic(): display(0),
                buttons(buttonPins, buttonPinsSize),
                menu(display, buttons), 
                clock(display, buttons), 
                alarmclock(display, buttons), 
                stopwatch(display, buttons),
                timer(display, buttons)
{
}

void Logic::setup()
{
  //Serial.begin(9600);
  //Serial.println("Waiting for high DTR");
  //while (!Serial.dtr()) {}
  delay(500);

  //Battery measuring
  analogReference(EXTERNAL);
  analogReadResolution(12);
  analogReadAveraging(32); // this one is optional.
  
  Serial.println("Setup");
  
  //RTC
  setSyncProvider(Logic::teensyTime);
  if (timeStatus() != timeSet) Serial.println("Unable to sync with the RTC");
  else Serial.println("RTC has set the system time");
  
  //DONT COMMENT OUT THIS LINE
  buttons.setup();
  
  display.begin();
  Serial.println("Module setup");
  moduleHandler.setup(modules, modulesSize);
  display.display();
  Serial.println("Display setup");
}

void Logic::loop()
{
  Alarm.delay(0);

  //Serial.println(getBatteryVoltage());
  
  display.clearDisplay();
  moduleHandler.loop();
  snprintf(battery, sizeof(battery), "%%%lu", getBatteryVoltage()/3500*100);
  display.drawCenteredText(battery, 56, 1);
  display.display();
}

time_t Logic::teensyTime() 
{
  return Teensy3Clock.get();
}

uint32_t Logic::getBatteryVoltage(){ // for Teensy 3.1, only valid between 2.0V and 3.5V. Returns in millivolts.
    uint32_t x = analogRead(39);
    return (178*x*x + 2688743864 - 1182047 * x) / 371794;
}
