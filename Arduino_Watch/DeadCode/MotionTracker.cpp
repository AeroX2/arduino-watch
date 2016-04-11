#include <Arduino.h>

//Dependencies
#include <Adafruit_SSD1306.h>
#include <Accelerometer.h>

#include "Module.h"
#include "MotionTracker.h"

MotionTracker::MotionTracker(Adafruit_SSD1306 &rdisplay, Accelerometer &raccelerometer) : display(rdisplay), accelerometer(raccelerometer)
{
  state = INSIDE;
  timeInside = 0;
  timeOutside = 0;
}

void MotionTracker::setup()
{
  Serial.println("MotionTracker setup");
}

void MotionTracker::loop()
{
  long currentTime = millis();
  switch (state)
  {
    case INSIDE:
      if (accelerometerOutside())
      {
        if (timeOutside <= 0) timeOutside = currentTime;
        else if (currentTime - timeOutside > 500)
        {
          resetTimes();
          display.ssd1306_command(SSD1306_DISPLAYOFF);
          state = OUTSIDE;
        }
      }
      else
      {
        if (timeInside <= 0) timeInside = currentTime;
        else if (currentTime - timeInside > 2000)
        {
          Serial.println("Derp");
          resetTimes();
          display.dim(true);
          state = INSIDE_TIMEOUT;
        }
      }
      break;
    case INSIDE_TIMEOUT:
      if (accelerometerOutside())
      {
          resetTimes();
          display.dim(false);
          state = OUTSIDE;
      }
      break;
    case OUTSIDE:      
      if (!accelerometerOutside())
      {
        if (timeInside <= 0) timeInside = currentTime;
        else if (currentTime - timeInside > 500) 
        {
          resetTimes();
          display.ssd1306_command(SSD1306_DISPLAYON);
          state = INSIDE_TIMEOUT;
        }
      }
      break;
  } 
}

boolean MotionTracker::accelerometerOutside()
{
  if (Serial.available() > 0)
  {
    char c = Serial.read();
    if (c == '1')
    {
      Serial.println("Boo!");
      return true;
    }
  }
  return false;
}

void MotionTracker::resetTimes()
{
  timeInside = 0;
  timeOutside = 0;
}
