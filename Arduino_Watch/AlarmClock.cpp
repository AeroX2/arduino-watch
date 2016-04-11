#include <Arduino.h>

//Dependencies
#include <Adafruit_SSD1306.h>
#include <Buttons.h>
#include <Time.h>
#include <TimeAlarms.h>

#include "Module.h"
#include "AlarmClock.h"

AlarmClock* AlarmClock::instance = 0;

AlarmClock::AlarmClock(Adafruit_SSD1306 &rdisplay, Buttons &rbuttons) : display(rdisplay), buttons(rbuttons)
{
  AlarmClock::instance = this;
  alarmID = -1;
  set = false;
}

void AlarmClock::setup()
{
  Serial.println("AlarmClock setup");
  blinker1 = millis();
  blinker2 = 0;
  type = 0;
  selected = false;
}      

void AlarmClock::loop()
{ 
  if (buttons.isHeld(0)) this->setNextModule(0);
  
  //Decrease time/(hour:minute:seconds)
  if (buttons.isPressed(0)) 
  {
    if (!set)
    {
      if (!selected) 
      {
        type--;
        if (type < 0) type = 2;
      }
      else 
      {
        times[type]--;
        if (times[type] < 0) times[type] = (type == 0) ? 24 : 59;
      }
    }
  }

  //Set alarm
  if (buttons.isPressed(1))
  {
    if (!set) selected = !selected;
  }
  
  //Set alarm
  if (buttons.isHeld(1))
  {
    set = !set;
    if (set) 
    {
      if (times[0] == 0 && times[1] == 0 && times[2] == 0)
      {
        if (alarmID != -1) Alarm.disable(alarmID);
      }
      else
      {
        alarmID = Alarm.alarmRepeat(times[0], times[1], times[2], alarmGoingOff);
      }
    }
  }
  
  //Increase time/(hour:minute:seconds)
  if (buttons.isPressed(2)) 
  {
    if (!set)
    {
      if (!selected)
      {
        type++;
        if (type > 2) type = 0;
      }
      else 
      {
        times[type]++;
        if (type == 0)
        {
          if (times[type] > 24) times[type] = 0;
        }
        else
        {
          if (times[type] > 59) times[type] = 0;
        }
      }
    }
  }

  if (!set) 
  {
    //Setting AlarmClock
    if (millis() - blinker1 < BLINK1_TIME)
    {
      blinker2 = millis();
      if (type == 0) snprintf(alarmClockString, sizeof(alarmClockString), (times[0] < 10) ? " :" : "  :");
      else snprintf(alarmClockString, sizeof(alarmClockString), "%d:", times[0]);
      if (type == 1) snprintf(alarmClockString + strlen(alarmClockString), sizeof(alarmClockString + strlen(alarmClockString)), "  :");
      else snprintf(alarmClockString + strlen(alarmClockString), sizeof(alarmClockString + strlen(alarmClockString)), "%02d:", times[1]);
      if (type == 2) snprintf(alarmClockString + strlen(alarmClockString), sizeof(alarmClockString + strlen(alarmClockString)), "  ");
      else snprintf(alarmClockString + strlen(alarmClockString), sizeof(alarmClockString + strlen(alarmClockString)), "%02d", times[2]);
    }
    else if (millis() - blinker2 < BLINK2_TIME)
    {
      snprintf(alarmClockString, sizeof(alarmClockString), "%d:%02d:%02d", times[0], times[1], times[2]);
    }
    else
    {
      blinker1 = millis();
    }
  }
  else
  {
    //Counting down
    //Serial.println(alarmID);
    time_t countdown = Alarm.readNextTrigger(alarmID) - now();
    snprintf(alarmClockString, sizeof(alarmClockString), "%d:%02d:%02d", hour(countdown), minute(countdown), second(countdown));
  }

  drawAlarmClock();
}

void AlarmClock::drawAlarmClock()
{
  display.drawCenteredText(alarmClockString, display.height() / 2, 2);
  if (selected) display.fillRect(0,0,10,10,WHITE);
}

void AlarmClock::alarmGoingOff()
{
  Serial.println("AlarmClock going off");
  instance->type = 0;
  unsigned long goingoff = millis();
  while (millis() - goingoff <= CLOCK_GOING_OFF_LENGTH)
  {
    instance->display.fillScreen(BLACK);
    instance->display.display();
    delay(500);
    instance->display.fillScreen(WHITE);
    instance->display.display();
    delay(500);
  }
}

