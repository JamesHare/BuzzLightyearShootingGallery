#include "Target.h"

Target::Target(int servoPinNumber, int photoresistorPinNumber, int ledPinNumber) {
    servo.attach(servoPinNumber);
    servoPinNumber = servoPinNumber;
    photoresistorPinNumber = photoresistorPinNumber;
    ledPinNumber = ledPinNumber;
}

void Target::setTarget(int degree) {
    servo.write(degree);
}

int Target::getPhotoresistorValue() {
    return analogRead(photoresistorPinNumber);
}