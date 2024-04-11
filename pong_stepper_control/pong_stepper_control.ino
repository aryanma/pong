#include <AccelStepper.h>

// Define pin connections
#define stepPin 2
#define dirPin 5

#define STEPS_PER_REVOLUTION 200

// Initialize the stepper
AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);

void setup() {
  // Set up the stepper
  stepper.setMaxSpeed(1000); // Max speed in steps per second, adjust as necessary
  stepper.setAcceleration(0); // Acceleration in steps per second squared, adjust as necessary
  
  // Optionally reset the position to zero at startup
  stepper.setCurrentPosition(0);
}

void loop() {
  // Calculate the absolute target positions
  static int targetPosition = 0;  // This will keep track of the next target position

  // Move the stepper 2 revolutions forward
  targetPosition += 2 * STEPS_PER_REVOLUTION;  // Add 2 revolutions worth of steps
  stepper.moveTo(targetPosition);
  stepper.runToPosition(); // Block until the stepper reaches the position

  delay(1000); // Wait for a second

  // Move the stepper 1 revolution backward
  targetPosition -= 1 * STEPS_PER_REVOLUTION;  // Subtract 1 revolution worth of steps
  stepper.moveTo(targetPosition);
  stepper.runToPosition(); // Block until the stepper reaches the position

  delay(1000); // Wait for a second

  // The loop will continue to repeat this sequence
}
