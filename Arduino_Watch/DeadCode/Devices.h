#ifndef Devices_H
#define Devices_H

class Devices
{
  public:
    Devices();
  private:
    static Buttons buttons;
    static Adafruit_SSD1306 display;
};

#endif
