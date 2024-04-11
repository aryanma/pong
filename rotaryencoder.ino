#include <AccelStepper.h>
#include "PinChangeInterrupt.h"
#define CLK 2
#define DT 3
#define SW 4

int counter = 0;
int currentState;
int initState;

unsigned long debounceDelay = 0;

void setup() {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);

  // Setup Serial Monitor
  Serial.begin(9600);

  // Read the initial state of CLK
  initState = digitalRead(CLK);

  // Call encoder_value() when any high/low changed seen on interrupt 0 (pin 2), or interrupt 1 (pin 3)
  attachInterrupt(0, encoder_value, CHANGE);
  attachInterrupt(1, encoder_value, CHANGE);
  attachPCINT(digitalPinToPCINT(SW), button_press, CHANGE);
}

void loop()
{

}

void button_press() 
{
  int buttonVal = digitalRead(SW);
  //If we detect LOW signal, button is pressed
  if (buttonVal == LOW) {
    if (millis() - debounceDelay > 200) {
      Serial.println("Button pressed!");
    }
    debounceDelay = millis();
  }
}

void encoder_value() {
  // Read the current state of CLK
  currentState = digitalRead(CLK);

  // If last and current state of CLK are different, then we can be sure that the pulse occurred
  if (currentState != initState  && currentState == 1) {
    // Encoder is rotating counterclockwise so we decrement the counter
    if (digitalRead(DT) != currentState) {
      counter ++;
    } else {
      // Encoder is rotating clockwise so we increment the counter
      counter --;
    }

    // print the value in the serial monitor window
    Serial.print("Counter: ");
    Serial.println(counter);
  }

  // Remember last CLK state for next cycle
  initState = currentState;
}