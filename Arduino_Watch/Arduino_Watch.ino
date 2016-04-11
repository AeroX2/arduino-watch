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

#include "Logic.h"
Logic logic;

void setup()
{
  logic.setup();
}

void loop()
{
  logic.loop();
}
