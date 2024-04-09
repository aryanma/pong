// Define the range for the paddle position
#define PADDLE_MIN 0
#define PADDLE_MAX 100

// Variables to hold the current encoder value and the last encoder value
int currentEncoderValue = 0;
int lastEncoderValue = 0;

// Variable to hold the mapped paddle position
int paddlePosition = 0;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Update currentEncoderValue with the actual encoder reading
  // Example: currentEncoderValue = readEncoder();
  
  // Map the current encoder value to the paddle's range
  // First, compute the difference in encoder values
  int encoderDiff = currentEncoderValue - lastEncoderValue;
  
  // Then, update the paddle position based on this difference
  // This way, the paddle can move up even if the encoder value is at its maximum
  paddlePosition += encoderDiff;
  
  // Constrain the paddle position to be within the defined limits
  paddlePosition = constrain(paddlePosition, PADDLE_MIN, PADDLE_MAX);
  
  // Update lastEncoderValue for the next iteration
  lastEncoderValue = currentEncoderValue;
  
  // Debugging: print the current paddle position
  Serial.println(paddlePosition);
  
  // Add a small delay to make the serial output readable
  delay(100);
}
