#include <Wire.h>
#define ADDRESS 1

//Units in in
#define WIDTH 15.5
#define HEIGHT 10.5


int string1Length = 0;
int string2Length = 0;

void setup(){
    Wire.begin(ADDRESS);            
    Wire.onReceive(receiveEvent); 
}

void loop(){
    driveBottomMotorToLength();
    driveTopMotorToLength();
}

void driveTopMotorToLength(){
    //TODO
}

void driveBottomMotorToLength(){
    //TODO
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



//Motor Driver code do3wn here
