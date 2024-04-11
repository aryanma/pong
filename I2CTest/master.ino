#include <Wire.h>

char* message = "Hello, I am the master";
char* outgoing[30]
int i = 0;

void setup(){
    Wire.begin();          
    Serial.begin(9600);  
}

void loop(){
    Serial.println("Sending message");
    i++;
    delay(1000);
    Wire.beginTransmission(1);
    sprintf(outgoing, "%s %d", message, i); // Append i to message
    Wire.write(outgoing); // Send message
    Wire.endTransmission();
}
