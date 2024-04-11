#include <AccelStepper.h>
#include <Wire.h>

#define ADDRESS 1
#define MAXSPEED 1000
#define ACCELERATION 100

#define FDELAY 100

//Units in mm
#define WIDTH 394
#define HEIGHT 267

// Define pin connections
#define stepPinTop 2
#define dirPinTop 5
#define stepPinBottom 3
#define dirPinBottom 6

#define STEPS_PER_REVOLUTION 200
#define DISTANCE_PER_REVOLUTION 15.24 * 3.14159

// Initialize the stepper
AccelStepper top(AccelStepper::DRIVER, stepPinTop, dirPinTop);
//AccelStepper bottom(AccelStepper::DRIVER, stepPinBottom, dirPinBottom);

int topString = 0;
int bottomString = 0;


void calculateStringLengths(int x, int y) {
  // Where we flip so that x correspodns to y_real and y corresponds to x_real
  // This orietnation has topStringLength corresponding to motor at (0,0) and bottomStringLength corresponding to motor at (0,gameHeight)
  //X increases from right to left (motor on right) and Y increases from top to bottom
  int topStringLength = sqrt(x * x + y * y);
  int bottomStringLength = sqrt((HEIGHT - y) * (HEIGHT - y) + x * x);

  topString = topStringLength * STEPS_PER_REVOLUTION * (1/DISTANCE_PER_REVOLUTION);
  bottomString = bottomStringLength * STEPS_PER_REVOLUTION * DISTANCE_PER_REVOLUTION;
  Serial.println("Set strings");
}


void setup() {
  Wire.begin(ADDRESS);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);

  // Set up the steppers
  top.setMaxSpeed(MAXSPEED);          // Max speed in steps per second, adjust as necessary
  top.setAcceleration(ACCELERATION);  // Adjust as necessary to smooth out the movement

  //bottom.setMaxSpeed(MAXSPEED);          // Max speed in steps per second, adjust as necessary
  //bottom.setAcceleration(ACCELERATION);  // Adjust as necessary to smooth out the movement

  // Optionally reset the position to zero at startup
  top.setCurrentPosition(0);
  //bottom.setCurrentPosition(0);

  top.moveTo(200);
//  bottom.moveTo(1000);
}

void loop() {
  top.run();
  //bottom.run();

  //top.moveTo(topString);
  //bottom.moveTo(bottomString);

  Serial.println(topString);

/*
  Serial.print("Top Goal: ");
  Serial.println(topString);

  Serial.print("Top Current Position: ");
  Serial.println(top.currentPosition());

  Serial.print("Bottom Current Position: ");
  Serial.println(bottom.currentPosition());
  */

  delay(FDELAY);
}

void receiveEvent(int numBytes) {
  Serial.println("Received Event");
    int ballX = Wire.read();
    int ballY = Wire.read();
    Serial.print(ballX);
    Serial.print(ballY);
    Serial.println(" :)");
    calculateStringLengths(ballX, ballY);
  
}
