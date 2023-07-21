#include <Servo.h>
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor_vl53l0x;
Servo servo_mg996r;

#define HIGH_ACCURACY

#define LID_CLOSED 0
#define LID_OPEN 120

#define LID_CLOSING_DELAY 1000 // 1s

#define SERVO_PIN 9
#define SERVO_SPEED 7  // ms per degree

unsigned long timeObjectDetected;
int lastPos = LID_CLOSED;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  servo_mg996r.attach(SERVO_PIN);
  servo_mg996r.write(LID_CLOSED);

  if (!servo_mg996r.attached()) {
    Serial.println("Servo not attached");
    while (1) {}
  }

  sensor_vl53l0x.setTimeout(2000);
  while (!sensor_vl53l0x.init()) { // Try to initialize the sensor in a loop
    Serial.println("Failed to detect and initialize sensor");
    delay(1000); // Wait a second before trying again
  }

  sensor_vl53l0x.startContinuous(1000); // Start continuous back-to-back mode
}

void moveServo(int pos) {
  if (pos == LID_OPEN) {
    for (int step = lastPos; step <= pos; step += 1) {
      servo_mg996r.write(step);
      delay(SERVO_SPEED);
    }
  } else {
    for (int step = lastPos; step >= pos; step -= 1) {
      servo_mg996r.write(step);
      delay(SERVO_SPEED);
    }
  }
}

void loop() {
  int distance = sensor_vl53l0x.readRangeContinuousMillimeters();
  int pos = lastPos;

  if (distance < 300) { // 30cm
    pos = LID_CLOSED;
    timeObjectDetected = millis();
  } else if (millis() - timeObjectDetected > LID_CLOSING_DELAY) {
    pos = LID_OPEN;
  }

  if (pos != lastPos) { // only write to the servo if the position has changed
    moveServo(pos);
    lastPos = pos;
  }
}
