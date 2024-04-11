#include <Wire.h>

#define BALL_CONTROLLER_ADDRESS 1
#define FDELAY 100

int i=0;

void setup(){
    Wire.begin();
    Serial.begin(9600);
}

void updateBallPosition(int x, int y){
    Wire.beginTransmission(BALL_CONTROLLER_ADDRESS);
    Wire.write(x);
    Wire.write(y);
    Wire.endTransmission();
}

void loop(){
    //delay(FDELAY*5);
    i++;
    updateBallPosition(400,400);
    //Serial.println(i*5);
}

void getPositionFromSerial(){
    if(Serial.available() >= 2 * sizeof(int)){
        int x = Serial.read();
        int y = Serial.read();
        updateBallPosition(x, y);
    }
}


