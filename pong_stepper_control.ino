#include <AccelStepper.h>

// define these pins with driver specs
#define STEP_PIN_1 2
#define DIR_PIN_1 3
#define ENABLE_PIN_1 4

#define STEP_PIN_2 5
#define DIR_PIN_2 6
#define ENABLE_PIN_2 7

// ?? need accel?
#define MAX_SPEED 1000.0
#define ACCELERATION 500.0

// change
#define STEPS_PER_REVOLUTION 200

AccelStepper stepper1(AccelStepper::DRIVER, STEP_PIN_1, DIR_PIN_1);
AccelStepper stepper2(AccelStepper::DRIVER, STEP_PIN_2, DIR_PIN_2);

void setup() {
  // setup
  pinMode(ENABLE_PIN_1, OUTPUT);
  pinMode(ENABLE_PIN_2, OUTPUT);

  // disable
  digitalWrite(ENABLE_PIN_1, LOW);
  digitalWrite(ENABLE_PIN_2, LOW);
  
  stepper1.setMaxSpeed(MAX_SPEED);
  stepper1.setAcceleration(ACCELERATION);
  stepper2.setMaxSpeed(MAX_SPEED);
  stepper2.setAcceleration(ACCELERATION);
}

void loop() {
  moveStepperToPosition(stepper1, 1000);
  moveStepperToPosition(stepper2, -1000);
}

void moveStepperToPosition(AccelStepper& stepper, long position) {
  digitalWrite(ENABLE_PIN_1, HIGH);
  digitalWrite(ENABLE_PIN_2, HIGH);

  stepper.moveTo(position);

  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

  digitalWrite(ENABLE_PIN_1, LOW);
  digitalWrite(ENABLE_PIN_2, LOW);
}
