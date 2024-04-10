#include <Wire.h>
#define ADDRESS 2

int slider1 = 0;
int slider2 = 0;

void setup(){
    Wire.begin(ADDRESS);
    Wire.onRequest(requestEvent);
}

//Copiloted - double check this
void requestEvent(){
    Wire.write((byte*)&slider1, sizeof(slider1));
    Wire.write((byte*)&slider2, sizeof(slider2));
}

void driveSlider1ToLength(){
    //TODO
}

void driveSlider2ToLength(){
    //TODO
}

void updateSliders(){
    //TODO
}

void loop(){
    driveSlider1ToLength();
    driveSlider2ToLength();
    updateSliders();
}


