#include <Arduino.h>

//Dependencies
#include <Adafruit_SSD1306.h>
#include <Buttons.h>

#include "Module.h"
#include "Stopwatch.h"

Stopwatch::Stopwatch(Adafruit_SSD1306 &rdisplay, Buttons &rbuttons) : display(rdisplay), buttons(rbuttons)
{
}

void Stopwatch::setup()
{
  Serial.println("Stopwatch setup");
  strcpy(timerString,"0:00:00");
  running = false;
  startTime = 0;
  stopTime = 0;
  previousTime = 0;
  currentLap = 0;
  
  //HERE IS THE ERROR!!!
  //for (int i = 0; i <= laps_size; i++) memset(laps[i],0,laps_size);
}

void Stopwatch::loop()
{ 
  if (buttons.isHeld(0)) this->setNextModule(0);
  
  //Reset and lap 
  if (buttons.isPressed(0))
  {
    if (running) 
    {
      //Lapping NOT IMPLEMENTED
      startTime = millis();
      previousTime = 0;
      //snprintf(laps[currentLap], sizeof(laps[currentLap]), "Lap %d: %s", currentLap, time);
      currentLap++;
    }
    else
    {
      startTime = 0;
      stopTime = 0;
      previousTime = 0;
    }
  }
  
  //Start/Stop
  if (buttons.isDebounce(1)) 
  {
    running = !running;
    if (running) 
    {
      if (startTime != 0) previousTime += stopTime - startTime;
      startTime = millis();
    }
    else stopTime = millis();
  }
  
  //Scroll laps
  if (buttons.isPressed(2))
  {
    //NOT IMPLEMENTED
  }
  
  calculateTime();
  drawTime();
}

void Stopwatch::calculateTime()
{
  int currentTime = (running ? millis() : stopTime) - startTime + previousTime;
  
  int milliss = currentTime;
  int seconds = currentTime / 1000;
  milliss -= seconds * 1000;
  int minutes = seconds / 60;
  seconds -= minutes * 60;
  
  //6 = 360 / 60
  //int degree = 6 * seconds;
  snprintf(timerString, sizeof(timerString), "%d:%02d:%02d", minutes, seconds, milliss % 100);
}

void Stopwatch::drawTime()
{
  //drawArc(display.getWidth() / 2, display.getHeight() / 2, degree, STOPWATCH_RADIUS);
  display.drawCenteredText(timerString, display.height() / 2, 2);
  for (int i = laps_size; i <= 0; i--)
  {
    if (laps[i] != 0)
    {
      display.drawCenteredText(laps[i], display.height() - 5, 1);
      break;
    }
  }
}

//Copy and pasted from Adafruit GFX Library
void Stopwatch::drawArc(int x0, int y0, int degree, int r)
{  
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  checkPixel(x0, y0+r, degree);
  checkPixel(x0, y0-r, degree);
  checkPixel(x0+r, y0, degree);
  checkPixel(x0-r, y0, degree);

  while (x < y) 
  {
    if (f >= 0) 
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    checkPixel(x0 + x, y0 + y, degree);
    checkPixel(x0 - x, y0 + y, degree);
    checkPixel(x0 + x, y0 - y, degree);
    checkPixel(x0 - x, y0 - y, degree);
    checkPixel(x0 + y, y0 + x, degree);
    checkPixel(x0 - y, y0 + x, degree);
    checkPixel(x0 + y, y0 - x, degree);
    checkPixel(x0 - y, y0 - x, degree);
  }
}

void Stopwatch::checkPixel(int x, int y, int degree)
{
  //TODO Check if pixel is in bounds
  display.drawPixel(x,y,WHITE);
}

