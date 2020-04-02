#include "Target.h"

/**
 * Target constructor.
 * 
 * @param servoPinNumber the pin number that the servo is attached to. Cannot be NULL.
 * @param photoresistorPinNumer the pin number that the photoresistor is attached to. Cannot be NULL.
 * @param ledPinNumber the pin number that the led is attached to.
 * */
Target::Target(int servoPinNumber, int photoresistorPinNumber, int ledPinNumber) {
    if (servoPinNumber == NULL) {
        throw "Servo pin number cannot be NULL.";
    }
    if (photoresistorPinNumber == NULL) {
        throw "photoresistor pin number cannot be NULL";
    }
    servo.attach(servoPinNumber);
    pinMode(ledPinNumber, OUTPUT);
    this->servoPinNumber = servoPinNumber;
    this->photoresistorPinNumber = photoresistorPinNumber;
    this->ledPinNumber = ledPinNumber;
}

Target::~Target() {
    servo.write(0);
    servo.detach();
}

int Target::getPhotoresistorValue() {
    return analogRead(photoresistorPinNumber);
}

void Target::setLed(int status) {
    if (ledPinNumber != NULL) {
        digitalWrite(ledPinNumber, status);
    }
}

void Target::toggleLed() {
    if (ledPinNumber != NULL) {
        int status = digitalRead(ledPinNumber);
        if (status == 1) {
            digitalWrite(ledPinNumber, LOW);
        } else {
            digitalWrite(ledPinNumber, HIGH);
        }
    }
}

void Target::setTargetPosition(int degree) {
    if (degree > 0 && degree < 180) {
        servo.write(degree);
    } else {
        throw "Not a valid degree for a this Targets servo. Must be between 0 and 180.";
    }
}

void Target::raiseTarget() {
    servo.write(180);
}

void Target::lowerTarget() {
    servo.write(0);
}

boolean Target::isRaised() {
    return servo.read() > 10;
}

boolean Target::evaluateTargetForHit(int lightThreshold) {
    return (isRaised() && getPhotoresistorValue() > lightThreshold);
}