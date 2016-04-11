#include <Arduino.h>

//Dependencies
#include <Adafruit_SSD1306.h>
#include <Buttons.h>
#include <Time.h>
#include <TimeAlarms.h>

#include "Module.h"
#include "Timer.h"

Timer* Timer::instance = 0;

Timer::Timer(Adafruit_SSD1306 &rdisplay, Buttons &rbuttons) : display(rdisplay), buttons(rbuttons)
{
  Timer::instance = this;
  blinker1 = 0;
  blinker2 = 0;
}

void Timer::setup()
{
  Serial.println("Timer setup");
  strcpy(timerString,"00:00:00");                  
  //memset(times,0,3);
  type = 0;
  blinker1 = millis();
}      

void Timer::loop()
{ 
  if (buttons.isHeld(0)) this->setNextModule(0);
  
  //Decrease time/(hour:minute:seconds)
  if (buttons.isPressed(0)) 
  {
    times[type]--;
    if (times[type] < 0) times[type] = (type == 0) ? 24 : 59;
  }
  
  //Set alarm
  if (buttons.isPressed(1))
  {
    type += 1;
    if (type > 2) 
    {
      Serial.println("Timer set");
      alarmID = Alarm.timerOnce(times[0], times[1], times[2], timerGoingOff);
    }
  }
  
  //Increase time/(hour:minute:seconds)
  if (buttons.isPressed(2)) 
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

  if (type <= 2) 
  {
    //Setting timer
    if (millis() - blinker1 < BLINK1_TIME)
    {
      blinker2 = millis();
      if (type == 0) snprintf(timerString, sizeof(timerString), (times[0] < 10) ? " :" : "  :");
      else snprintf(timerString, sizeof(timerString), "%d:", times[0]);
      if (type == 1) snprintf(timerString + strlen(timerString), sizeof(timerString + strlen(timerString)), "  :");
      else snprintf(timerString + strlen(timerString), sizeof(timerString + strlen(timerString)), "%02d:", times[1]);
      if (type == 2) snprintf(timerString + strlen(timerString), sizeof(timerString + strlen(timerString)), "  ");
      else snprintf(timerString + strlen(timerString), sizeof(timerString + strlen(timerString)), "%02d", times[2]);
    }
    else if (millis() - blinker2 < BLINK2_TIME)
    {
      snprintf(timerString, sizeof(timerString), "%d:%02d:%02d", times[0], times[1], times[2]);
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
    snprintf(timerString, sizeof(timerString), "%d:%02d:%02d", hour(countdown), minute(countdown), second(countdown));
  }

  drawTimer();
}

void Timer::drawTimer()
{
  display.drawCenteredText(timerString, display.height() / 2, 2);
}

void Timer::timerGoingOff()
{
  Serial.println("Timer going off");
  instance->type = 0;
  unsigned long goingoff = millis();
  while (millis() - goingoff <= TIMER_GOING_OFF_LENGTH)
  {
    instance->display.fillScreen(BLACK);
    instance->display.display();
    delay(500);
    instance->display.fillScreen(WHITE);
    instance->display.display();
    delay(500);
  }
}

