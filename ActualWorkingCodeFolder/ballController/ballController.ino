#include <AccelStepper.h>
#include "PinChangeInterrupt.h"

#define FDELAY 100

#define CLK1 10
#define DT1 11
#define SW1 12

#define CLK2 5
#define DT2 6
#define SW2 7

unsigned long debounceDelay1 = 0;
unsigned long debounceDelay2 = 0;

int init1;
int init2;

int p1Encoder = 0;
int p2Encoder = 0;


//Units in mm
//#define WIDTH 394
//#define HEIGHT 267

#define HEIGHT 394
#define WIDTH 267

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
#define MAXSPEED 200
#define ACCELERATION 200

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

//Paddle stuff

//20 = 1 rotation on encoder
void paddle1_value(){
    int new1 = digitalRead(CLK1);
    if (init1 != new1) {
        if (digitalRead(DT1) != new1) {
            p1Encoder++;
        } else {
            p1Encoder--;
        }

        if(p1Encoder < 0){
            p1Encoder = 0;
        }

        if(p1Encoder > 50){
            p1Encoder = 50;
        }

        //CHANGE THIS BACK TO 1
        p2DistN = -1 * p1Encoder * 10;

        Serial.print("Paddle 1: ");
        Serial.println(p1Encoder);
    }
    init1 = new1;
}

void paddle2_value(){
    int new2 = digitalRead(CLK2);
    if (init2 != new2) {
        if (digitalRead(DT2) != new2) {
            p2Encoder++;
        } else {
            p2Encoder--;
        }
        if(p2Encoder < 0){
            p2Encoder = 0;
        }

        if(p2Encoder > 50){
            p2Encoder = 50;
        }

        p2DistN = -1 * p2Encoder * 10;

        Serial.print("Paddle 2: ");
        Serial.println(p2Encoder);
    }
    init2 = new2;
}

void button_press1() {
    int buttonVal = digitalRead(SW1);
    //If we detect LOW signal, button is pressed
    if (buttonVal == LOW) {
        if (millis() - debounceDelay1 > 200) {
            Serial.println("Button 1 pressed!");
        }
        debounceDelay1 = millis();
    }
}

void button_press2() {
    int buttonVal = digitalRead(SW2);
    //If we detect LOW signal, button is pressed
    if (buttonVal == LOW) {
        if (millis() - debounceDelay2 > 200) {
            Serial.println("Button 2 pressed!");
        }
        debounceDelay2 = millis();
    }
}

void setup() {
  Serial.begin(9600);

  //Paddle stuff
    pinMode(CLK1, INPUT);
    pinMode(DT1, INPUT);
    pinMode(SW1, INPUT_PULLUP);
    
    pinMode(CLK2, INPUT);
    pinMode(DT2, INPUT);
    pinMode(SW2, INPUT_PULLUP);

    init1 = digitalRead(CLK1);
    init2 = digitalRead(CLK2);

    attachPCINT(digitalPinToPCINT(CLK1), paddle1_value, CHANGE);
    attachPCINT(digitalPinToPCINT(CLK2), paddle2_value, CHANGE);
    attachPCINT(digitalPinToPCINT(DT1), paddle1_value, CHANGE);
    attachPCINT(digitalPinToPCINT(DT2), paddle2_value, CHANGE);
    attachPCINT(digitalPinToPCINT(SW1), button_press1, CHANGE);
    attachPCINT(digitalPinToPCINT(SW2), button_press2, CHANGE);


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

  //calculateStringLengths(0,100);    
}


int i = 0;
int toggle = 0;

void loop() {

  //Move motors
  top.run();
  bottom.run();
  p1.run();
  p2.run();


/*
  if((millis() % 10000) - i > 1000){
    i = millis() % 10000;
    toggle = !toggle;
    if(toggle){
        p1DistN = 100;
        p2DistN = 100;
    }else{
        p1DistN = 0;
        p2DistN = 0;
    }
  
  }*/

/*
  if (millis() - i > 2000 && millis() - i < 4000) {
    calculateStringLengths(0,200);
  }else if(millis() - i > 4000 && millis() - i < 6000){
    calculateStringLengths(200,200);
  }else if(millis() - i > 6000 && millis() - i < 8000){
    calculateStringLengths(200,0);
  }else if (millis() - i > 8000) {
    calculateStringLengths(0,0);
    i = millis();
}*/
  
  //Update goals
  if(topStringN != topStringL || bottomStringN != bottomStringL || p1DistN != p1DistL || p2DistN != p2DistL){
    Serial.println("Setting new positions");
    topStringL = topStringN;
    bottomStringL = bottomStringN;
    p1DistL = p1DistN;
    p2DistL = p2DistN;

    top.moveTo(topStringL);
    bottom.moveTo(bottomStringL);

    //p1.moveTo(p1DistL);
    p2.moveTo(p2DistL);

    Serial.println(p1DistL);
    Serial.print("P1 currently at ");
    Serial.println(p1.currentPosition());
  }



  //updateGameState();

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
    }
}

void setPlotterMotors(int toop, int bot){
    topStringN = toop;
    bottomStringN = bot;
}
