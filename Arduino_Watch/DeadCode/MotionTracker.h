#ifndef MotionTracker_H
#define MotionTracker_H

class MotionTracker
{
  public:
    MotionTracker(Adafruit_SSD1306 &rdisplay, Accelerometer &raccelerometer);
    void setup();
    void loop();
  private:
    boolean accelerometerOutside();
    void resetTimes();
    
    Adafruit_SSD1306 &display;
    Accelerometer &accelerometer;
    
    enum StateTypes { OUTSIDE, INSIDE, INSIDE_TIMEOUT };
    StateTypes state;
    long timeInside;
    long timeOutside;
};
  
#endif
