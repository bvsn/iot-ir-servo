# Automated Garbage Can Lid Opener 🥲

This project uses an Arduino Nano to automatically open and close a garbage can lid based on the proximity of an object (like a hand).

## Hardware Components

- Arduino Nano V3.0 ATMEGA328P
- VL53L0X-v2 Laser Time-of-Flight (ToF) Sensor
- MG996R Tower Pro 120° Servo Motor

## Software

The Arduino code for this project is written in C++. It uses the built-in Servo library to control the servo motor, and analogRead to read the output from the IR sensor.

The behavior is as follows:

- If an object comes within a certain distance of the IR sensor (indicating that someone wants to throw something away), the servo motor turns to open the garbage can lid.
- If no object is detected within the range of the IR sensor, the servo motor turns to close the garbage can lid.

## Wiring

Connect MG 996R Servo Motor:

- **Power Wire (Red 🔴)**: Connect the power wire from the servo to the 5V pin on the Arduino Nano.
- **Ground Wire (Brown/Black ⚫️)**: Connect the ground wire from the servo to one of the GND pins on the Arduino Nano.
- **Signal Wire (Orange/Yellow 🟠)**: Connect the signal wire from the servo to a digital pin on the Arduino Nano (D9 as example).

Connect VL53L0X-v2 Laser Time-of-Flight (ToF) Sensor:

- **VIN**: Connect to the 5V pin.
- **GND**: Connect to any GND pin.
- **SDA**: Connect to the A4 pin (which acts as the SDA pin).
- **SCL**: Connect to the A5 pin (which acts as the SCL pin).

Note 🤔 The servo motor should be powered directly from the 5V power source, not through the Arduino, to prevent overloading the Arduino's power output.

## Author

Andrii Bovsunovskyi
