#define LED 2

void setup(void) {
  pinMode(LED, OUTPUT); 
}
 
// main loop
void loop() {
  digitalWrite(LED, HIGH);
  delay(500);               
  digitalWrite(LED, LOW);  
  delay(500);
}
