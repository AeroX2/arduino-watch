#ifndef Menu_H
#define Menu_H

class Menu : public Module
{
  public:
    Menu(Adafruit_SSD1306 &rdisplay, Buttons &rbuttons);
    void setup();
    void loop();
  private:
    Adafruit_SSD1306 &display;
    Buttons &buttons;
    int selectedModule;
    
    //Constants
    int SPACING_X = 0;
    int SPACING_Y = 0;
    const int SIZE_X = 35;
    const int SIZE_Y = 20;
};

#endif
