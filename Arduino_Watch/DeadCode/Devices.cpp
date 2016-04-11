//Dependencies
#include <Wire.h>
#include <SPI.h>

//Display
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Buttons
#include <Buttons.h>

#include "Devices.h"

Devices::buttons = 0;
Devices::display = 0;

Devices::Devices()
{
  //Empty
}
