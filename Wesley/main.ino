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
    int playerX = WIDTH - 1.2109375;
    int playerY = HEIGHT / 2;
    int playerY = map(slider1, 0, fromHigh, 0, HEIGHT);
    int opponentX = 1.2109375;
    int opponentY = map(slider2, 0, ?, fromHigh, HEIGHT);

    int ballX = WIDTH / 2;
    int ballY = HEIGHT / 2;

    int playerScore = 0;
    int opponentScore = 0;

    int xSpeed = 1;
    int ySpeed = 1;

    /*
    if (Serial.available() > 0) {
        char key = Serial.read();
        if (key == 'W' && playerY > 0) {
            playerY -= 2;
        }
        if (key == 'S' && playerY < HEIGHT) {
            playerY += 2;
        }
    }
    */

    ballX += xSpeed * 2;
    ballY += ySpeed * 2;
    
    // bouncing logic (top, bottom)
    if (ballY >= HEIGHT || ballY <= 0) {
        ySpeed = -ySpeed;
    }

    // collision detection (paddle)
    if (ballX <= playerX + 1 && ballY >= playerY && ballY <= playerY + 2) {
        xSpeed = -xSpeed;
    }
    
    // collision detection (opponent paddle)
    if (ballX >= opponentX - 1 && ballY >= opponentY && ballY <= opponentY + 2) {
        xSpeed = -xSpeed;
    }

    // scoring and reset
    if (ballX <= 0) {
        playerScore++;
        ballX = WIDTH / 2;
        ballY = HEIGHT / 2;
        xSpeed = random(2) == 0 ? 1 : -1;
        ySpeed = random(2) == 0 ? 1 : -1;
    }

    // scoring and reset
    if (ballX >= WIDTH) {
        opponentScore++;
        ballX = WIDTH / 2;
        ballY = HEIGHT / 2;
        xSpeed = random(2) == 0 ? 1 : -1;
        ySpeed = random(2) == 0 ? 1 : -1;
    }
    
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
