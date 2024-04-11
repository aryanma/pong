#include <AccelStepper.h>

#define FDELAY 100

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
#define MAXSPEED 2000
#define ACCELERATION 1000

#define DISTANCE_PER_REVOLUTION (15.24 * 3.14159)


int cycle = 0;

// Initialize the stepper
AccelStepper top(AccelStepper::DRIVER, stepPinTop, dirPinTop);
AccelStepper bottom(AccelStepper::DRIVER, stepPinBottom, dirPinBottom);
AccelStepper p1(AccelStepper::DRIVER, stepPinP1, dirPinP1);
AccelStepper p2(AccelStepper::DRIVER, stepPinP2, dirPinP2);


//Old values
double topStringL = 0;
double bottomStringL = 0;
double p2DistL = 0;
double p1DistL = 0;

//New values
double topStringN = 0;
double bottomStringN = 0;
double p2DistN = 0;
double p1DistN = 0;

//x, y in mm
void calculateStringLengths(int x, int y) {
    // Where we flip so that x correspodns to y_real and y corresponds to x_real
    // This orietnation has topStringLength corresponding to motor at (0,0) and bottomStringLength corresponding to motor at (0,gameHeight)
    //X increases from right to left (motor on right) and Y increases from top to bottom
    int topStringLength = sqrt(x * x + y * y);
    int bottomStringLength = sqrt((HEIGHT - y) * (HEIGHT - y) + x * x);

    int topGoal = topStringLength * STEPS_PER_REVOLUTION * (1/DISTANCE_PER_REVOLUTION);
    int bottomGoal = bottomStringLength * STEPS_PER_REVOLUTION * (1/DISTANCE_PER_REVOLUTION);

    Serial.print("New goals: ");
    Serial.print(topGoal);
    Serial.print(" ");
    Serial.println(bottomGoal);

    setPlotterMotors(topGoal, bottomGoal);
}


void setup() {
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
}


int i = 0;

void loop() {
    i++;

    if(i % 10000 == 0){
        calculateStringLengths(i/100, i/100);
    }

  //Move motors
  top.run();
  bottom.run();
  p1.run();
  p2.run();

  
  //Update goals
  if(topStringN != topStringL || bottomStringN != bottomStringL || p1DistN != p1DistL || p2DistN != p2DistL){
    Serial.println("Setting new positions");
    topStringL = topStringN;
    bottomStringL = bottomStringN;
    p1DistL = p1DistN;
    p2DistL = p2DistN;

    top.moveTo(topStringL);
    bottom.moveTo(bottomStringL);

    p1.moveTo(p1DistL);
    p2.moveTo(p2DistL);

    Serial.println(topStringL);
  }



  updateGameState();

}


void updateGameState(){
    if (Serial.available() >= 2) {
        int x = Serial.read();
        int y = Serial.read();

        Serial.print("Received: ");
        Serial.print(x);
        Serial.print(" ");
        Serial.println(y);

        calculateStringLengths(x, y);

        /*
        if(x == 'a'){
            setPlotterMotors(200, 200);
        }else if(x == 'b'){
            setPlotterMotors(0, 0);
        }*/
    }
}

void setPlotterMotors(int toop, int bot){
    topStringN = toop;
    bottomStringN = bot;
}
