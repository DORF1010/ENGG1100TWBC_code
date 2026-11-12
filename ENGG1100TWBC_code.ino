#include <Servo.h>

// enA, in1A, in2A are for motor movement
#define enA 9
#define in1A 5
#define in2A 6
// ECHO is for ultrasonic sensor (not yet implementd, will be on final design)
#define ECHO_PIN 8
#define SOUND_PIN 7
// Servo control
#define SERVO_PIN 10
// LED's
#define LED2_PIN 12
#define LED1_PIN 13
// Implroves redability of delay(); (see uses)
#define SECONDS 1000
// Other utilities/settings
#define DUMP_MAX_ANGLE 170
#define DUMP_MIN_ANGLE 45
#define middleOfBlinkTime 75
#define waitingTimeMS 750
#define RECYCLING_RUN_STOP_DISTANCE 20
#define RECYCLING_RUN_STOP_DISTANCE_TOLERANCE 1
#define SPEED_RUN_STOP_DISTANCE 60

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

    digitalWrite(enA, HIGH); // turn on the motor/motor controller (this dosen't actually start spinning it yet, thats digitalWrite(in1A/2A, HIGH))
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
    Serial.print("\n");
}

// Stops powering the motors, alowing the wheelchair to roll to a stop
void movementCoast() {
    digitalWrite(in1A, LOW);
    digitalWrite(in2A, LOW);
    Serial.print("movemnetCoast\n");
}

// Starts braking the motor at given amount (must be positive value)
void movementBrake(int speed) {
    analogWrite(in1A, HIGH);
    analogWrite(in2A, HIGH);
    Serial.print("movementCoast\n");
}

void dumpingUP() {
    dumpingServo.analogWrite(DUMP_MAX_ANGLE);
}

void dumpingDOWN() {
    dumpingServo.analogWrite(DUMP_MIN_ANGLE)''
}

void dumpingCustom(float percent) {
    // calculate the difference between min and max dumping servo angle, and add percent amount of that to the min angle and send to the servo
    dumpingServo.analogWrite(DUMP_MIN_ANGLE+(DUMP_MAX_ANGLE-DUMP_MIN_ANGLE)*percent);
}

void testMotorMovement() {
    Serial.print("testMotorMovement\n");
    /*movementForward(1);
    delay(2*SECONDS);
    movementReverse(1);
    delay(2*SECONDS);*/
    

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
double getDistance() {
    digitalWrite(SOUND_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(SOUND_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(SOUND_PIN, LOW);
    double duration = pulseIn(ECHO_PIN, HIGH);
    double distance = duration * 0.024/2;
    return distance;
}

void testDumpingServo() {
    dumpingUP();
    delay(waitingTimeMS);
    dumpingDOWN();
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

void recyclingRun() {
    movementForward(1);
    delay(5*SECONDS); // get most of the way to the recycling bin
    while (1) {
        Serial.write(getDistance());
        if (getDistance()>RECYCLING_RUN_STOP_DISTANCE-RECYCLING_RUN_STOP_DISTANCE_TOLERANCE) {
            movementForward(1);
        }
        else if (getDistance()<RECYCLING_RUN_STOP_DISTANCE+RECYCLING_RUN_STOP_DISTANCE_TOLERANCE) {
            movementReverse(1);
        }
        else {
            Serial.write("In tolerance of distance")
            break;
        }
    }
}

void speedRun() {
    movementForward(1);
    while (getDistance()>SPEED_RUN_STOP_DISTANCE) {
        movementForward(1);
    }
    movementReverse(1);
    delay(5*SECONDS);
    movementBrake(1);
}

void loop() {
    // testMotorMovement();
    // testDumpingServo();
    Serial.write(getDistance());
}