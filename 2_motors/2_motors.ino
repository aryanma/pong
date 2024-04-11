#include <AccelStepper.h>

// Define pin connections
#define stepPin 2
#define dirPin 5

#define STEPS_PER_REVOLUTION 200

// Initialize the stepper
AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);

/*
void setup() {
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);

  // Set up the stepper
  stepper.setMaxSpeed(1000); // Max speed in steps per second, adjust as necessary
  stepper.setAcceleration(100); // Adjust as necessary to smooth out the movement
  
  // Optionally reset the position to zero at startup
  stepper.setCurrentPosition(0);

  // Move the stepper to the first target position
  stepper.moveTo(400); // Move to 400 steps
  stepper.runToPosition(); // This is a blocking call
  Serial.print("Reached Position 400: ");
  Serial.println(stepper.currentPosition());

  // Start the non-blocking movement sequence
  stepper.moveTo(200); // Next target is 200 steps
}*/

void setup(){
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);

  // Set up the stepper
  stepper.setMaxSpeed(1000); // Max speed in steps per second, adjust as necessary
  stepper.setAcceleration(100); // Adjust as necessary to smooth out the movement
  
  // Optionally reset the position to zero at startup
  stepper.setCurrentPosition(0);

  stepper.moveTo(200); // Next target is 200 steps

}

/*

void loop() {
  // Run the stepper motor without blocking
  stepper.run();

  // Check if the stepper has reached the intermediate target position of 200 steps
  if (stepper.distanceToGo() == 0 && stepper.currentPosition() == 200) {
    Serial.print("Reached Position 200: ");
    Serial.println(stepper.currentPosition());
    stepper.moveTo(0); // Set the next target to 0 steps
  }

  // Check if the stepper has reached the final target position of 0 steps
  if (stepper.distanceToGo() == 0 && stepper.currentPosition() == 0) {
    Serial.print("Reached Position 0: ");
    Serial.println(stepper.currentPosition());
    // Optionally, you can reset the sequence or stop the motor here
    delay(1000); // Wait a second before any next actions

    // Reset the sequence to start over
    stepper.moveTo(400); // Move to 400 steps
    stepper.runToPosition(); // This is a blocking call
    Serial.print("Reached Position 400: ");
    Serial.println(stepper.currentPosition());
    stepper.moveTo(200); // Next target is 200 steps
  }
}

*/


void loop() {
  // Run the stepper motor without blocking
  stepper.run();
  Serial.println("Current pos: " + stepper.currentPosition());

  // Check if the stepper has reached the intermediate target position of 200 steps
  if (stepper.distanceToGo() == 0 && stepper.currentPosition() == 200) {
    Serial.print("Reached Position 200: ");
    Serial.println(stepper.currentPosition());
    stepper.moveTo(0); // Set the next target to 0 steps
  }

  // Check if the stepper has reached the final target position of 0 steps
  if (stepper.distanceToGo() == 0 && stepper.currentPosition() == 0) {
    Serial.print("Reached Position 0: ");
    Serial.println(stepper.currentPosition());
    // Optionally, you can reset the sequence or stop the motor here
    delay(1000); // Wait a second before any next actions

    // Reset the sequence to start over
    stepper.moveTo(200); // Next target is 200 steps
  }
}
