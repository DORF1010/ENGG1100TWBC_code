#include <Servo.h>

// enA, in1A, in2A are for motor movement
#define enA 9
#define in1A 2
#define in2A 3
// ECHO is for ultrasonic sensor (not yet implementd, will be on final design)
#define ECHO_PIN 6
#define SOUND_PIN 7
// Servo control
#define SERVO_PIN 10
// LED's
#define LED2_PIN 12
#define LED1_PIN 13
// Implroves redability of delay(); (see uses)
#define SECONDS 1000

const int middleOfBlinkTime = 75;
const int waitingTimeMS = 750;

Servo dumpingServo; // the servo motor object

void setup() {
    Serial.begin(9600);
    // pinMode(LED1_PIN, OUTPUT);
    // pinMode(LED2_PIN, OUTPUT);
    dumpingServo.attach(SERVO_PIN);
    // pinMode(SOUND_PIN, OUTPUT);
    // pinMode(ECHO_PIN, INPUT);
    pinMode(enA, OUTPUT);
    pinMode(in1A, OUTPUT);
    pinMode(in2A, OUTPUT);

    digitalWrite(enA, HIGH);
}

// Starts moving the motor forward at given speed (must be positive value)
void movementForward(float speed) {
    digitalWrite(in1A, HIGH);
    digitalWrite(in2A, LOW);
    Serial.print("movementForward ");
    Serial.print(speed);
    Serial.print("\n");
}

// Starts moving the motor reverse at given speed (must be positive value)
void movementReverse(float speed) {
    digitalWrite(in1A, LOW);
    digitalWrite(in2A, HIGH);
    Serial.print("movementReverse ");
    Serial.print(speed);
    Serial.print("\n");
}

// Stops powering the motors, alowing the wheelchair to roll to a stop
void movementCoast() {
    digitalWrite(in1A, LOW);
    digitalWrite(in2A, LOW);
    digitalWrite(enA, LOW);
    Serial.print("movemnetCoast\n");
}

// Starts braking the motor at given amount (must be positive value)
void movementBrake(int speed) {
    analogWrite(in1A, HIGH);
    analogWrite(in2A, HIGH);
    analogWrite(enA, speed);
    Serial.print("movementCoast\n");
}

void testMotorMovement() {
    Serial.print("testMotorMovement\n");
    movementForward(1);
    delay(1*SECONDS);
    movementReverse(1);
    delay(1*SECONDS);

}

void testSoundControl() {
    // the following section code is a copy-paste from 'Sensor & DC Motor Guide' section 3.1 sample ultrasonic sensor Arduino code with a few minor edits
    // Clears the SOUND_PIN condition as a precaution
    digitalWrite(SOUND_PIN, LOW);
    delayMicroseconds(2);
    // Sets the SOUND_PIN HIGH (ACTIVE) for 10 microseconds, then turn it off
    digitalWrite(SOUND_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(SOUND_PIN, LOW);
    // Reads the ECHO_PIN, returns the sound wave travel time in microseconds into variable duration
    int duration = pulseIn(ECHO_PIN, HIGH);
    // Multiply distance by speed of sound (0.034) and divide by 2 (For pulse to go and come back)
    int distance = duration * 0.034 / 2;
    // Output the distance to the Serial Monitor
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.print("cm\n");
}

void testDumpingServo() {
    dumpingServo.write(45);
    delay(waitingTimeMS);
    dumpingServo.write(170);
    delay(waitingTimeMS);
}

void flash() {
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH);
    delay(middleOfBlinkTime);
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
}

void flashingBeacons() {
    delay(1*SECONDS);
    flash();
    delay(middleOfBlinkTime);
    flash();
}

void loop() {
    // testMotorMovement();

  // spin the motor in one direction
  digitalWrite(in1A, HIGH);
  digitalWrite(in2A, LOW);
  Serial.println("Spinning one direction"); // print status message to serial monitor

  delay(1500); // run for 1500ms

  // stop the motor
  digitalWrite(in1A, LOW);
  digitalWrite(in2A, LOW);
  Serial.println("Stopped"); // print status message to serial monitor

  delay(1500); // wait for 1500ms

  // spin the motor in the other direction
  digitalWrite(in1A, LOW);
  digitalWrite(in2A, HIGH);
  Serial.println("Spinning the other direction"); // print status message to serial monitor

  delay(1500); // run for 1500ms

  // stop the motor
  digitalWrite(in1A, LOW);
  digitalWrite(in2A, LOW);
  Serial.println("Stopped"); // print status message to serial monitor

  delay(1500); // wait for 1500ms
    */

}