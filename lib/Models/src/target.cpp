#include "Target.h"

/**
 * Target constructor.
 * 
 * @param name the name that will identify the target.
 * @param servoPinNumber the pin number that the servo is attached to.
 * @param photoresistorPinNumer the pin number that the photoresistor is attached to.
 * @param ledPinNumber the pin number that the led is attached to.
 * */
Target::Target(String name, int servoPinNumber, int photoresistorPinNumber, int ledPinNumber) {
    this->name = name;
    this->servoPinNumber = servoPinNumber;
    this->photoresistorPinNumber = photoresistorPinNumber;
    this->ledPinNumber = ledPinNumber;
}

Target::Target(){};

Target::~Target() {
    servo.write(0);
    servo.detach();
}

void Target::init() {
    this->servo.attach(servoPinNumber);
    pinMode(ledPinNumber, OUTPUT);
    Serial.print(name);
    Serial.println(" is initiated successfully");
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
        Serial.print(degree);
        Serial.println(" is not a valid degree for a this Targets servo. Must be between 0 and 180.");
    }
}

void Target::raiseTarget() {
    this->servo.write(180);
    Serial.print(name);
    Serial.println(" is raised.");
}

void Target::lowerTarget() {
    this->servo.write(0);
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