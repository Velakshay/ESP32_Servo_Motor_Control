#include <ESP32Servo.h>

Servo myServo;
const int servoPin = 13; // GPIO pin connected to the servo signal wire
int currentAngle = 90;   // Start at the center position
const int jogStep = 5;   // Number of degrees to move per jog step

void setup() {
  Serial.begin(115200);   
  myServo.attach(servoPin); 
  
  // Set initial position
  myServo.write(currentAngle);
  
  // Print user instructions to the Serial Monitor
  Serial.println("--- ESP32 Incremental Servo Jogging ---");
  Serial.println("Send '+' to increase by 5°");
  Serial.println("Send '-' to decrease by 5°");
  Serial.print("Current Position: ");
  Serial.print(currentAngle);
  Serial.println("°");
}

void loop() {
  if (Serial.available() > 0) {
    // Read the incoming character
    char inputChar = Serial.read();
    
    bool positionChanged = false;

    if (inputChar == '+') {
      // Check if we can step up without exceeding the 180° limit
      if (currentAngle + jogStep <= 180) {
        currentAngle += jogStep;
        positionChanged = true;
      } else {
        Serial.println("Limit reached! Cannot exceed 180°");
      }
    } 
    else if (inputChar == '-') {
      // Check if we can step down without dropping below the 0° limit
      if (currentAngle - jogStep >= 0) {
        currentAngle -= jogStep;
        positionChanged = true;
      } else {
        Serial.println("Limit reached! Cannot drop below 0°");
      }
    }

    // Update the servo if a valid jog key was pressed
    if (positionChanged) {
      myServo.write(currentAngle);
      Serial.print("Jogged to: ");
      Serial.print(currentAngle);
      Serial.println("°");
    }
  }
}
