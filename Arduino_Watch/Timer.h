#ifndef Timer_H
#define Timer_H

class Timer : public Module
{
  public:
    Timer(Adafruit_SSD1306 &rdisplay, Buttons &rbuttons);
    void setup();
    void loop();
    
    static Timer* instance;
  private:
    Adafruit_SSD1306 &display;
    Buttons &buttons;
    
    int type;
    int times[3];
    unsigned long blinker1;
    unsigned long blinker2;

    AlarmID_t alarmID;
    
    char timerString[9];
    
    static void timerGoingOff();
   
    void drawTimer();

    //Constants
    const static int BLINK1_TIME = 180;
    const static int BLINK2_TIME = 800;
    const static int TIMER_GOING_OFF_LENGTH = 8000;
};
  
#endif
