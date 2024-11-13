#include <Arduino.h>

const int RED_LED = 8;
const int GREEN_LED = 9;
const int SERVO_PIN = A3;

const int ENA = 3;
const int FIRST_RIGHT_WHEEL = 2;
const int SECOND_RIGHT_WHEEL = 4;
const int FIRST_LEFT_WHEEL = 5;
const int SECOND_LEFT_WHEEL = 7;
const int ENB = 6;

const int FLAME_SENSOR_RIGHT = A0;
const int FLAME_SENSOR_CENTER = A1;
const int FLAME_SENSOR_LEFT = A2;

const int WATER_PUMP_PIN = 10;

int speed = 255;

void moveForward();

void turnLeft();

void turnRight();

void moveBackward();

void stop();

void servoPulse(int angle);

void moveServo();

void turnOnOffLed();

void turnOffOnLed();

void setup() {
    Serial.begin(9600); // Initialize serial communication for debugging

    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(WATER_PUMP_PIN, OUTPUT);

    pinMode(ENA, OUTPUT);
    pinMode(FIRST_RIGHT_WHEEL, OUTPUT);
    pinMode(SECOND_RIGHT_WHEEL, OUTPUT);
    pinMode(FIRST_LEFT_WHEEL, OUTPUT);
    pinMode(SECOND_LEFT_WHEEL, OUTPUT);
    pinMode(ENB, OUTPUT);

    pinMode(FLAME_SENSOR_RIGHT, INPUT);
    pinMode(FLAME_SENSOR_CENTER, INPUT);
    pinMode(FLAME_SENSOR_LEFT, INPUT);

    analogWrite(ENA, speed);
    analogWrite(ENB, speed);

    stop();
}

void loop() {
    int centerValue = analogRead(FLAME_SENSOR_CENTER);

    // Map the value from 0-1023 to 1-100
    int centerScaled = (int) map(centerValue, 0, 1023, 1, 100);

    // Move forward if the center sensor detects a flame (value > threshold)
    if (centerScaled > 10 && centerScaled < 80) { // Adjust the threshold as needed
        moveForward();
        turnOnOffLed();
        digitalWrite(WATER_PUMP_PIN, LOW);
    } else if (centerScaled >= 1 && centerScaled <= 10) {
        stop();
        turnOffOnLed();
        digitalWrite(WATER_PUMP_PIN, HIGH);
    }

    delay(100); // Small delay to avoid rapid switching
}

void servoPulse(int angle) {
    int pwm = (angle * 11) + 500; // Convert angle to microseconds
    digitalWrite(SERVO_PIN, HIGH);
    delayMicroseconds(pwm);
    digitalWrite(SERVO_PIN, LOW);
    delay(50); // Refresh cycle of servo
}

void turnOnOffLed() {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
}

void turnOffOnLed() {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
}

void moveServo() {
    for (int angle = 70; angle < 140; ++angle) {
        delay(50);
    }

    delay(500);
}

void moveForward() {
    analogWrite(ENA, speed); // Set speed
    analogWrite(ENB, speed); // Set speed

    digitalWrite(FIRST_RIGHT_WHEEL, LOW);
    digitalWrite(SECOND_RIGHT_WHEEL, HIGH);

    digitalWrite(FIRST_LEFT_WHEEL, LOW);
    digitalWrite(SECOND_LEFT_WHEEL, HIGH);
}

void turnLeft() {
    analogWrite(ENA, speed); // Set speed
    analogWrite(ENB, speed); // Set speed

    digitalWrite(FIRST_RIGHT_WHEEL, LOW);
    digitalWrite(SECOND_RIGHT_WHEEL, HIGH);

    digitalWrite(FIRST_LEFT_WHEEL, HIGH);
    digitalWrite(SECOND_LEFT_WHEEL, LOW);
}

void turnRight() {
    analogWrite(ENA, speed); // Set speed
    analogWrite(ENB, speed); // Set speed

    digitalWrite(FIRST_RIGHT_WHEEL, HIGH);
    digitalWrite(SECOND_RIGHT_WHEEL, LOW);

    digitalWrite(FIRST_LEFT_WHEEL, LOW);
    digitalWrite(SECOND_LEFT_WHEEL, HIGH);
}

void moveBackward() {
    analogWrite(ENA, speed); // Set speed
    analogWrite(ENB, speed); // Set speed

    digitalWrite(FIRST_RIGHT_WHEEL, HIGH);
    digitalWrite(SECOND_RIGHT_WHEEL, LOW);

    digitalWrite(FIRST_LEFT_WHEEL, HIGH);
    digitalWrite(SECOND_LEFT_WHEEL, LOW);
}

void stop() {
    digitalWrite(FIRST_RIGHT_WHEEL, LOW);
    digitalWrite(SECOND_RIGHT_WHEEL, LOW);
    digitalWrite(FIRST_LEFT_WHEEL, LOW);
    digitalWrite(SECOND_LEFT_WHEEL, LOW);

    analogWrite(ENA, 0); // Stop speed
    analogWrite(ENB, 0); // Stop speed
}