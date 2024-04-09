// Define the range for the paddle positions
#define PADDLE_MIN 0
#define PADDLE_MAX 100

// Variables to hold the current and last encoder values for both paddles
int currentEncoderValue1 = 0;
int lastEncoderValue1 = 0;
int currentEncoderValue2 = 0;
int lastEncoderValue2 = 0;

// Variables to hold the mapped paddle positions
int paddlePosition1 = 0;
int paddlePosition2 = 0;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Update currentEncoderValue for both paddles with the actual encoder readings
  // Replace readEncoder(ID) with your actual method to read each encoder
  currentEncoderValue1 = readEncoder(1); // Hypothetical function to read the first encoder
  currentEncoderValue2 = readEncoder(2); // Hypothetical function to read the second encoder
  
  // Normalize and update paddle positions
  normalizePaddlePosition(currentEncoderValue1, lastEncoderValue1, paddlePosition1);
  normalizePaddlePosition(currentEncoderValue2, lastEncoderValue2, paddlePosition2);
  
  // Debugging: print the current paddle positions
  Serial.print("Paddle 1 Position: ");
  Serial.println(paddlePosition1);
  Serial.print("Paddle 2 Position: ");
  Serial.println(paddlePosition2);
  
  // Add a small delay to make the serial output readable
  delay(100);
}

void normalizePaddlePosition(int &currentEncoderValue, int &lastEncoderValue, int &paddlePosition) {
  // Compute the difference in encoder values
  int encoderDiff = currentEncoderValue - lastEncoderValue;
  
  // Update the paddle position based on this difference
  paddlePosition += encoderDiff;
  
  // Constrain the paddle position to be within the defined limits
  paddlePosition = constrain(paddlePosition, PADDLE_MIN, PADDLE_MAX);
  
  // Update lastEncoderValue for the next iteration
  lastEncoderValue = currentEncoderValue;
}

// Replace this with your actual method to read an encoder value based on its ID
int readEncoder(int encoderID) {
  // Placeholder for reading encoder values
  // You'll need to implement this function based on how your encoders are connected and read
  return 0; // Placeholder return value
}
