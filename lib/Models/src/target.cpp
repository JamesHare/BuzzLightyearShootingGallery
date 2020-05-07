#include "Target.h"

/**
 * Target constructor.
 * 
 * @param name the name that will identify the target.
 * @param servoPinNumber the pin number that the servo is attached to. Cannot be NULL.
 * @param photoresistorPinNumer the pin number that the photoresistor is attached to. Cannot be NULL.
 * @param ledPinNumber the pin number that the led is attached to.
 * */
Target::Target(String name, int servoPinNumber, int photoresistorPinNumber, int ledPinNumber) {
    this->name = name;
    servo.attach(servoPinNumber);
    pinMode(ledPinNumber, OUTPUT);
    this->servoPinNumber = servoPinNumber;
    this->photoresistorPinNumber = photoresistorPinNumber;
    this->ledPinNumber = ledPinNumber;
}

Target::Target(){};

Target::~Target() {
    servo.write(0);
    servo.detach();
}

int Target::getLedPinNumber() {
    return ledPinNumber;
}

int Target::getLedStatus() {
    return ledPinNumber;
}

int Target::getPhotoresistorValue() {
    return analogRead(photoresistorPinNumber);
}

void Target::setLed(int status) {
    digitalWrite(ledPinNumber, status);
}

void Target::toggleLed() {
    int status = digitalRead(ledPinNumber);
    if (status == 1) {
        digitalWrite(ledPinNumber, LOW);
    } else {
        digitalWrite(ledPinNumber, HIGH);
    }
}

void Target::setTargetPosition(int degree) {
    if (degree > 0 && degree < 180) {
        servo.write(degree);
    } else {
        Serial.println("Not a valid degree for a this Targets servo. Must be between 0 and 180.");
    }
}

void Target::raiseTarget() {
    servo.write(180);
}

void Target::lowerTarget() {
    servo.write(0);
}

boolean Target::isRaised() {
    return getServoPosition() > 10;
}

boolean Target::evaluateTargetForHit(int lightThreshold) {
    return (isRaised() && getPhotoresistorValue() > lightThreshold);
}

AdvancedTarget::AdvancedTarget(String name, int servoPinNumber, int photoresistorPinNumber, int ledPinNumber, int moveDistance):Target(name, servoPinNumber, photoresistorPinNumber, ledPinNumber) {
    this->moveDistance = moveDistance;
    this->movingDirection = "left";
}

AdvancedTarget::AdvancedTarget(){};

void AdvancedTarget::moveAdvancedTarget() {
    int targetPosition = this->getServoPosition();
    if (this->getMovingDirection().equals("left")) {
        if (targetPosition < 170) {
            this->setTargetPosition(targetPosition + moveDistance);
        } else {
            this->setMovingDirection("right");
            this->setTargetPosition(targetPosition - moveDistance);
        }
    } else if (this->getMovingDirection().equals("right")) {
        if (targetPosition > 10) {
            this->setTargetPosition(targetPosition - moveDistance);
        } else {
            this->setMovingDirection("left");
            this->setTargetPosition(targetPosition + moveDistance);
        }
    }
}

void AdvancedTarget::resetTarget() {
    this->movingDirection = "left";
    lowerTarget();
}