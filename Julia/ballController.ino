#include <Wire.h>
#include <AccelStepper.h>

#define ADDRESS 1

//Units in in
#define WIDTH 15.5
#define HEIGHT 10.5

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

int string1Length = 0;
int string2Length = 0;

// change
#define STEPS_PER_REVOLUTION 200

AccelStepper stepper1(AccelStepper::DRIVER, STEP_PIN_1, DIR_PIN_1);
AccelStepper stepper2(AccelStepper::DRIVER, STEP_PIN_2, DIR_PIN_2);

void setup(){
    Wire.begin(ADDRESS);            
    Wire.onReceive(receiveEvent); 

    // julia is below. need?
    pinMode(STEP_PIN_1,OUTPUT); 
    pinMode(DIR_PIN_1,OUTPUT); 
    pinMode(STEP_PIN_2,OUTPUT);
    pinMode(DIR_PIN_2,OUTPUT); 
}

void loop(){
    driveBottomMotorToLength();
    driveTopMotorToLength();
}

void driveTopMotorToLength(){
    //TODO
    int steps = 100; // for testing: set = calculateSteps(string1Length) later
    stepper1.moveTo(steps);
    stepper1.run();
}

void driveBottomMotorToLength(){
    //TODO
    int steps = 100; // for testing: set = calculateSteps(string2Length) later
    stepper2.moveTo(steps);
    stepper2.run();
}

void calculateSteps(int length) {
    // TODO figure out conversion and fix later
    int steps = map(length, 0, maxStringLength, 0, maxSteps);
    return steps;
}

//Copiloted - double check this
void receiveEvent(int numBytes) {
    while (Wire.available() >= 2*sizeof(int)) { 
        int ballX = Wire.read() << 8 | Wire.read();
        int ballY = Wire.read() << 8 | Wire.read();
        calculateStringLengths(ballX, ballY);
    }
}


void calculateStringLengths(int x, int y){
    // Where we flip so that x correspodns to y_real and y corresponds to x_real
    // This orietnation has topStringLength corresponding to motor at (0,0) and bottomStringLength corresponding to motor at (0,gameHeight)
    //X increases from right to left (motor on right) and Y increases from top to bottom
    int topStringLength = sqrt(x*x + y*y);
    int bottomStringLength = sqrt((HEIGHT - y)*(HEIGHT - y) + x*x);

    string1Length = topStringLength;
    string2Length = bottomStringLength;
}

