#ifndef AlarmClock_H
#define AlarmClock_H

class AlarmClock : public Module
{
  public:
    AlarmClock(Adafruit_SSD1306 &rdisplay, Buttons &rbuttons);
    void setup();
    void loop();
    
    static AlarmClock* instance;
  private:
    Adafruit_SSD1306 &display;
    Buttons &buttons;

    boolean set;
    boolean selected;
    
    int type;
    int times[3];
    unsigned long blinker1;
    unsigned long blinker2;

    AlarmID_t alarmID;
    
    char alarmClockString[9];
    
    static void alarmGoingOff();
   
    void drawAlarmClock();

    //Constants
    const static int BLINK1_TIME = 180;
    const static int BLINK2_TIME = 800;
    const static int CLOCK_GOING_OFF_LENGTH = 8000;
};
  
#endif
