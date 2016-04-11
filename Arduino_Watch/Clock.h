#ifndef Clock_H
#define Clock_H

class Clock : public Module
{
  public:
    Clock(Adafruit_SSD1306 &rdisplay, Buttons &rbuttons);
    void setup();
    void loop();
  private:
    void updateTime();
    void drawTime();
    void drawCenteredText(char* string, int y, int size);
    
    Adafruit_SSD1306 &display;
    Buttons &buttons;
    
    char time[9];
    char dayInWeek[10];
    char dayInMonth[5];
    char monthInYear[10];
    
    //Constants
    const static int FIRST_LINE_Y = 20;
    const static int SECOND_LINE_Y = 40;
    const static int THIRD_LINE_Y = 48;
};
  
#endif
