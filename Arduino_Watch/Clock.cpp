#include <Arduino.h>

//Dependencies
#include <Adafruit_SSD1306.h>
#include <Buttons.h>
#include <Time.h>
#include <string.h>

#include "Module.h"
#include "Clock.h"

Clock::Clock(Adafruit_SSD1306 &rdisplay, Buttons &rbuttons) : display(rdisplay), buttons(rbuttons)
{
  //Hacky fix for "first" module
  this->setNextModule(1);
}

void Clock::setup()
{
  Serial.println("Clock setup");
  updateTime();
  drawTime();
}

void Clock::loop()
{
  if (buttons.isPressed(1)) this->setNextModule(0);
  updateTime();
  drawTime();
}

void Clock::updateTime()
{
  //Formating
  char days[12];
  switch (day() % 100)
  {
    case 1:
      snprintf(days, sizeof(days), "%dst", day());
      break;
    case 2:
      snprintf(days, sizeof(days), "%dnd", day());
      break;
    case 3:
      snprintf(days, sizeof(days), "%drd", day());
      break;
    default:
      snprintf(days, sizeof(days), "%dth", day());
  }
  
  snprintf(time, sizeof(time), "%d:%02d:%02d", hour(), minute(), second());
  strcpy(dayInWeek, dayStr(weekday()));
  strcpy(dayInMonth, days);
  strcpy(monthInYear, monthStr(month()));
}

void Clock::drawTime()
{
  display.setTextColor(WHITE);
  char thirdLine[15];
  snprintf(thirdLine, sizeof(thirdLine), "%s %s" , dayInMonth, monthInYear);
  
  display.drawCenteredText(time, FIRST_LINE_Y, 2);
  display.drawCenteredText(thirdLine, SECOND_LINE_Y, 1);
  display.drawCenteredText(dayInWeek, THIRD_LINE_Y, 1);
}
