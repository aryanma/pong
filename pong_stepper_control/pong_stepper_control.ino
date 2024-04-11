#include <AccelStepper.h>

// Define pin connections
#define stepPinTop 2
#define dirPinTop 5
#define stepPinBottom 3
#define dirPinBottom 6

#define stepPinP1 4
#define dirPinP1 7
#define stepPinP2 9
#define dirPinP2 8

#define STEPS_PER_REVOLUTION 200
#define MAXSPEED 1000
#define ACCELERATION 700

// Initialize the stepper
AccelStepper top(AccelStepper::DRIVER, stepPinTop, dirPinTop);
AccelStepper bottom(AccelStepper::DRIVER, stepPinBottom, dirPinBottom);
AccelStepper p1(AccelStepper::DRIVER, stepPinP1, dirPinP1);
AccelStepper p2(AccelStepper::DRIVER, stepPinP2, dirPinP2);


void setup() {
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);

  // Set up the steppers
  top.setMaxSpeed(MAXSPEED);          // Max speed in steps per second, adjust as necessary
  top.setAcceleration(ACCELERATION);  // Adjust as necessary to smooth out the movement

  bottom.setMaxSpeed(MAXSPEED);          // Max speed in steps per second, adjust as necessary
  bottom.setAcceleration(ACCELERATION);  // Adjust as necessary to smooth out the movement

  p1.setMaxSpeed(MAXSPEED);          // Max speed in steps per second, adjust as necessary
  p1.setAcceleration(ACCELERATION);  // Adjust as necessary to smooth out the movement

  p2.setMaxSpeed(MAXSPEED);          // Max speed in steps per second, adjust as necessary
  p2.setAcceleration(ACCELERATION);  // Adjust as necessary to smooth out the movement

  // Optionally reset the position to zero at startup
  top.setCurrentPosition(0);
  bottom.setCurrentPosition(0);
  p1.setCurrentPosition(0);
  p2.setCurrentPosition(0);


  // Move the stepper to the first target position
  Serial.print("Reached Position 200: ");
  Serial.println(top.currentPosition());
}
/*
void setup(){
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);

  // Set up the stepper
  top.setMaxSpeed(1000); // Max speed in steps per second, adjust as necessary
  top.setAcceleration(100); // Adjust as necessary to smooth out the movement
  
  // Optionally reset the position to zero at startup
  top.setCurrentPosition(0);

  top.moveTo(200); // Next target is 200 steps

}*/

/*

void loop() {
  // Run the stepper motor without blocking
  top.run();

  // Check if the stepper has reached the intermediate target position of 200 steps
  if (top.distanceToGo() == 0 && top.currentPosition() == 200) {
    Serial.print("Reached Position 200: ");
    Serial.println(top.currentPosition());
    top.moveTo(0); // Set the next target to 0 steps
  }

  // Check if the stepper has reached the final target position of 0 steps
  if (top.distanceToGo() == 0 && top.currentPosition() == 0) {
    Serial.print("Reached Position 0: ");
    Serial.println(top.currentPosition());
    // Optionally, you can reset the sequence or stop the motor here
    delay(1000); // Wait a second before any next actions

    // Reset the sequence to start over
    top.moveTo(400); // Move to 400 steps
    top.runToPosition(); // This is a blocking call
    Serial.print("Reached Position 400: ");
    Serial.println(top.currentPosition());
    top.moveTo(200); // Next target is 200 steps
  }
}

*/


void loop() {
  // Run the stepper motor without blocking
  top.run();
  bottom.run();
  p1.run();
  p2.run();

  // Check if the stepper has reached the intermediate target position of 200 steps
  if (top.distanceToGo() == 0 && top.currentPosition() == 200) {
    Serial.print("Reached Position 200: ");
    Serial.println(top.currentPosition());
    top.moveTo(0); // Set the next target to 0 steps
    bottom.moveTo(0);
    p1.moveTo(0);
    p2.moveTo(0);
  }

  // Check if the stepper has reached the final target position of 0 steps
  if (top.distanceToGo() == 0 && top.currentPosition() == 0) {
    Serial.print("Reached Position 0: ");
    Serial.println(top.currentPosition());
    // Optionally, you can reset the sequence or stop the motor here
    delay(1000); // Wait a second before any next actions

    // Reset the sequence to start over
    top.moveTo(400); // Move to 400 steps
    bottom.moveTo(400);
    p1.moveTo(400);
    p2.moveTo(400);
    bottom.run();
    p1.run();
    p2.run();
    top.run(); // This is a blocking call
    Serial.print("Reached Position 400: ");
    Serial.println(top.currentPosition());
    top.moveTo(200); // Next target is 200 steps
    bottom.moveTo(200);
    p1.moveTo(200);
    p2.moveTo(200);
  }

}
