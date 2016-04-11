#ifndef Stopwatch_H
#define Stopwatch_H

class Stopwatch : public Module
{
  public:
    Stopwatch(Adafruit_SSD1306 &rdisplay, Buttons &rbuttons);
    void setup();
    void loop();
  private:
    void drawArc(int x, int y, int degree, int radius);
    void calculateTime();
    void drawTime();
    void checkPixel(int x, int y, int degree);
    
    Adafruit_SSD1306 &display;
    Buttons &buttons;
    
    boolean running;
    long startTime;
    long stopTime;
    long previousTime;
    char timerString[9];
    
    int degree;
    
    int currentLap;
    int laps_size = 15;
    char laps[15][15];
    
    //Constants
    const int STOPWATCH_RADIUS = 10;
};
  
#endif
