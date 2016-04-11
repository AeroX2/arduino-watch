#include <Arduino.h>

//Dependencies
#include <Adafruit_SSD1306.h>
#include <Buttons.h>

#include "Module.h"
#include "Menu.h"

Menu::Menu(Adafruit_SSD1306 &rdisplay, Buttons &rbuttons) : display(rdisplay), buttons(rbuttons)
{
}

void Menu::setup()
{
  Serial.println("Menu setup");
  selectedModule = 0;
  SPACING_X = (display.width() - 2 * SIZE_X) / 3;
  SPACING_Y = (display.height() - 2 * SIZE_Y) / 3;
}

void Menu::loop()
{
  if (buttons.isPressed(0)) selectedModule--;
  if (buttons.isPressed(2)) selectedModule++;
  if (selectedModule < 0) selectedModule = 3;
  if (selectedModule > 3) selectedModule = 0;

  if (buttons.isPressed(1)) this->setNextModule(selectedModule+1);

  for (int i = 0; i <= 1; i++)
  {
    for (int ii = 0; ii <= 1; ii++)
    {
      int x = SPACING_X + ii * (SPACING_X + SIZE_X);
      int y = SPACING_Y + i * (SPACING_Y + SIZE_Y);
      if (ii + (i * 2) == selectedModule) display.fillRect(x, y, SIZE_X, SIZE_Y, WHITE);
      else display.drawRect(x, y, SIZE_X, SIZE_Y, WHITE);
    }
  }
}

