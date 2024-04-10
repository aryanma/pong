#include <Wire.h>

#define SLAVE1_ADDRESS 1
#define SLAVE2_ADDRESS 2

//Units in in
#define WIDTH 15.5
#define HEIGHT 10.5


int slider1 = 0;
int slider2 = 0;

int ballX = 0;
int ballY = 0;

void setup() {
    Wire.begin(); // Initialize I2C communication
    Serial.begin(9600); // Initialize serial communication
}

void loop() {
    sendToBallController();
    requestFromSliderController();
    updateGame();
    delay(1000);
}

void updateGame(){
    Serial.print("Slider1: ");
    Serial.println(slider1);
    Serial.print("Slider2: ");
    Serial.println(slider2);
    Serial.print("BallX: ");
    Serial.println(ballX);
    Serial.print("BallY: ");
    Serial.println(ballY);

    //TODO

}

//Copiloted - double check this
void sendToBallController(){
    Wire.beginTransmission(SLAVE1_ADDRESS);
    Wire.write((byte*)&ballX, sizeof(ballX));
    Wire.write((byte*)&ballY, sizeof(ballY));
    Wire.endTransmission();
}

//Copiloted - double check this
void requestFromSliderController(){
    Wire.requestFrom(SLAVE2_ADDRESS, 2 * sizeof(int));
    
    if (Wire.available() >= 2 * sizeof(int)) {
        int var1 = Wire.read() << 8 | Wire.read();
        int var2 = Wire.read() << 8 | Wire.read();
        slider1 = var1;
        slider2 = var2;
    }
}
