#ifndef Buttons_H
#define Buttons_H

class Buttons
{
  public:
    Buttons(int rbuttonPins[], int rbuttonPinsSize);
    void setup();
	boolean isDebounce(int button);
    boolean isPressed(int button);
	boolean isHeld(int button);
    boolean read(int button);
  private:
    int buttonPins[10];
	int buttonPinsSize;
	boolean pressed[10];
	boolean held[10];
	unsigned long pressedTime[10];
	unsigned long heldTime[10];

	//Constants
	const static int HELD_TIME = 1100;
	const static int DEBOUNCE_TIME = 10;
};
    
#endif
