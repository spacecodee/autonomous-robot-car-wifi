#include <Arduino.h>

const int ENA = 3;
const int FIRST_RIGHT_WHEEL = 2;
const int SECOND_RIGHT_WHEEL = 4;
const int FIRST_LEFT_WHEEL = 5;
const int SECOND_LEFT_WHEEL = 7;
const int ENB = 6;

const int FLAME_SENSOR_RIGHT = A0;
const int FLAME_SENSOR_CENTER = A1;
const int FLAME_SENSOR_LEFT = A2;

void moveForward();

void turnLeft();

void turnRight();

void moveBackward();

void stop();

void setup() {
    pinMode(ENA, OUTPUT);
    pinMode(FIRST_RIGHT_WHEEL, OUTPUT);
    pinMode(SECOND_RIGHT_WHEEL, OUTPUT);
    pinMode(FIRST_LEFT_WHEEL, OUTPUT);
    pinMode(SECOND_LEFT_WHEEL, OUTPUT);
    pinMode(ENB, OUTPUT);

    pinMode(FLAME_SENSOR_RIGHT, INPUT);
    pinMode(FLAME_SENSOR_CENTER, INPUT);
    pinMode(FLAME_SENSOR_LEFT, INPUT);
    Serial.begin(9600); // Initialize serial communication for debugging

    stop();
}

void loop() {
    int centerValue = analogRead(FLAME_SENSOR_CENTER);

    // Map the value from 0-1023 to 1-100
    int centerScaled = (int) map(centerValue, 0, 1023, 1, 100);

    // Move forward if the center sensor detects a flame (value > threshold)
    if (centerScaled > 10 && centerScaled < 80) { // Adjust the threshold as needed
        moveForward();
    } else {
        stop();
    }

    delay(100); // Small delay to avoid rapid switching
}

void moveForward() {
    digitalWrite(FIRST_RIGHT_WHEEL, LOW);
    digitalWrite(SECOND_RIGHT_WHEEL, HIGH);

    digitalWrite(FIRST_LEFT_WHEEL, LOW);
    digitalWrite(SECOND_LEFT_WHEEL, HIGH);

    analogWrite(ENA, 255); // Full speed
    analogWrite(ENB, 255); // Full speed
}

void turnLeft() {
    digitalWrite(FIRST_RIGHT_WHEEL, LOW);
    digitalWrite(SECOND_RIGHT_WHEEL, HIGH);

    digitalWrite(FIRST_LEFT_WHEEL, HIGH);
    digitalWrite(SECOND_LEFT_WHEEL, LOW);

    analogWrite(ENA, 255); // Full speed
    analogWrite(ENB, 255); // Full speed
}

void turnRight() {
    digitalWrite(FIRST_RIGHT_WHEEL, HIGH);
    digitalWrite(SECOND_RIGHT_WHEEL, LOW);

    digitalWrite(FIRST_LEFT_WHEEL, LOW);
    digitalWrite(SECOND_LEFT_WHEEL, HIGH);

    analogWrite(ENA, 255); // Full speed
    analogWrite(ENB, 255); // Full speed
}

void moveBackward() {
    digitalWrite(FIRST_RIGHT_WHEEL, HIGH);
    digitalWrite(SECOND_RIGHT_WHEEL, LOW);

    digitalWrite(FIRST_LEFT_WHEEL, HIGH);
    digitalWrite(SECOND_LEFT_WHEEL, LOW);

    analogWrite(ENA, 255); // Full speed
    analogWrite(ENB, 255); // Full speed
}

void stop() {
    digitalWrite(FIRST_RIGHT_WHEEL, LOW);
    digitalWrite(SECOND_RIGHT_WHEEL, LOW);
    digitalWrite(FIRST_LEFT_WHEEL, LOW);
    digitalWrite(SECOND_LEFT_WHEEL, LOW);

    analogWrite(ENA, 0); // Stop speed
    analogWrite(ENB, 0); // Stop speed
}