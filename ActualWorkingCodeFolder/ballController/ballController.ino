#include <AccelStepper.h>
#include <Wire.h>

#define ADDRESS 1
#define MAXSPEED 1000
#define ACCELERATION 700

#define FDELAY 1

//Units in mm
#define WIDTH 394
#define HEIGHT 267

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

#define DISTANCE_PER_REVOLUTION 15.24 * 3.14159

int topString = 0;
int bottomString = 0;
float ballX = 0;
float ballY = 0;
float p2Dist = 0;
float p1Dist = 0;


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

  //top.moveTo(200);
  //bottom.moveTo(1000);
}

void loop() {
  //Move motors
  top.run();
  bottom.run();
  p1.run();
  p2.run();

  top.moveTo(ballX);
  bottom.moveTo(ballY);

  p1.moveTo(p1Dist);
  p2.moveTo(p2Dist);

  Serial.println(topString);

  updateGameState();


  Serial.print("Top Goal: ");
  Serial.println(topString);

  Serial.print("Top Current Position: ");
  Serial.println(top.currentPosition());

  Serial.print("Bottom Current Position: ");
  Serial.println(bottom.currentPosition());
  

  delay(FDELAY);
}

void updateGameState(){
  
}
