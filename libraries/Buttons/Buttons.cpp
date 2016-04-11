#include <Arduino.h>

//Dependencies
#include "Buttons.h"

Buttons::Buttons(int rbuttonPins[], int rbuttonPinsSize)
{
  memcpy(buttonPins, rbuttonPins, rbuttonPinsSize * sizeof(int));
  buttonPinsSize = rbuttonPinsSize;
  
  memset(pressed,false,sizeof(buttonPins));
  memset(held,false,sizeof(buttonPins));
  memset(pressedTime,0,sizeof(buttonPins));
  memset(heldTime,0,sizeof(buttonPins));
}

void Buttons::setup()
{
  for (int i = 0; i < buttonPinsSize; i++) 
  {
	pinMode(buttonPins[i], INPUT_PULLUP);
	delayMicroseconds(10);
  }
  Serial.println("Buttons setup");
}

boolean Buttons::isPressed(int button)
{  
  /*Serial.println("Button");
  Serial.println(button);
  Serial.println(buttonPins[button]);
  Serial.println(read(button));*/
  if (read(button))
  {
	pressed[button] = true;
	if (pressedTime[button] == 0) pressedTime[button] = millis();
  }
  else 
  {
	if (millis() - pressedTime[button] < HELD_TIME && pressed[button]) 
	{
	  pressed[button] = false;
	  pressedTime[button] = 0;
      Serial.printf("Button %d pressed\n", button);
	  return true;
	}
	pressed[button] = false;
	pressedTime[button] = 0;
  }
  return false;
}

boolean Buttons::isDebounce(int button)
{  
  /*Serial.println("Button");
  Serial.println(button);
  Serial.println(buttonPins[button]);
  Serial.println(read(button));*/
  if (read(button))
  {
	if (!pressed[button])
	{
		Serial.printf("Button %d pressed (debounced)\n", button);
		pressed[button] = true;
		return true;
	}
  }
  else 
  {
	pressed[button] = false;
  }
  return false;
}


boolean Buttons::isHeld(int button)
{
  if (read(button))
  {
    if (heldTime[button] == 0) heldTime[button] = millis();
    if (millis() - heldTime[button] > HELD_TIME && !held[button])
	{
		heldTime[button] = 0;
		held[button] = true;
		Serial.printf("Button %d held\n", button);
		return true;	
	}
  }
  else 
  {
	heldTime[button] = 0;
	held[button] = false;
  }
  return false;
}

boolean Buttons::read(int button) { return !digitalRead(buttonPins[button]); }
