#include <Wire.h>

// Encoder pins
const int encoderA1 = 2; // Encoder 1 Channel A
const int encoderB1 = 3; // Encoder 1 Channel B
const int encoderA2 = 18; // Encoder 2 Channel A (ensure your Arduino model supports interrupts on this pin)
const int encoderB2 = 19; // Encoder 2 Channel B (ensure your Arduino model supports interrupts on this pin)

// Encoder positions (volatile because they are modified in ISRs)
volatile int encoderPos1 = 0;
volatile int encoderPos2 = 0;

// Paddle positions, normalized
int paddlePosition1 = 50; // Start in the middle of the range
int paddlePosition2 = 50; // Start in the middle of the range

// Define the range for the paddle positions
#define PADDLE_MIN 0
#define PADDLE_MAX 100

// Interrupt Service Routines for the encoders
void ISR_encoder1() {
  if (digitalRead(encoderA1) == digitalRead(encoderB1)) {
    encoderPos1++;
  } else {
    encoderPos1--;
  }
}

void ISR_encoder2() {
  if (digitalRead(encoderA2) == digitalRead(encoderB2)) {
    encoderPos2++;
  } else {
    encoderPos2--;
  }
}

void setup() {
  Serial.begin(9600); // Start serial communication

  // Encoder 1 setup
  pinMode(encoderA1, INPUT_PULLUP);
  pinMode(encoderB1, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderA1), ISR_encoder1, CHANGE);
  
  // Encoder 2 setup
  pinMode(encoderA2, INPUT_PULLUP);
  pinMode(encoderB2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderA2), ISR_encoder2, CHANGE);
}

void loop() {
  // Normalize and update paddle positions based on encoder positions
  normalizePaddlePosition(encoderPos1, paddlePosition1);
  normalizePaddlePosition(encoderPos2, paddlePosition2);
  
  // Debugging: Print the current paddle positions
  Serial.print("Paddle 1 Position: ");
  Serial.println(paddlePosition1);
  Serial.print("Paddle 2 Position: ");
  Serial.println(paddlePosition2);
  
  // Add a small delay to slow down the loop and make serial output readable
  delay(100);
}

void normalizePaddlePosition(volatile int &encoderPos, int &paddlePosition) {
  // Map the encoder position to the paddle's range
  // This simplistic approach resets the encoder position whenever it's read,
  // which may not be suitable for all applications.
  if (encoderPos != 0) {
    int newPos = paddlePosition + encoderPos;
    paddlePosition = constrain(newPos, PADDLE_MIN, PADDLE_MAX);
    encoderPos = 0; // Reset encoder position after adjusting paddle position
  }
}
