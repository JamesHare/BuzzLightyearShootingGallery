#include "troubleshooter.h"

/**
 * Runs troubleshooting on a single target.
 * */
void testTarget(Target target) {
    Serial.println('Starting tests on Target ' + target.getName());
    Serial.println("");

    testTargetServo(target);
    testTargetLed(target);
    testTargetPhotoresistor(target);

    Serial.println('Ending tests on Target ' + target.getName());
    Serial.println("");
}

void testTargetServo(Target target) {
    target.raiseTarget();
    delay(2000);
    Serial.println('The servo on Target ' + target.getName() + ' should be raised.');
    if (target.getServoPosition() == 180) {
        Serial.println('The servo on Target ' + target.getName() + ' has passed the raise test.');
    } else {
        Serial.println('The servo on Target ' + target.getName() + ' has failed the raise test.');
    }

    target.lowerTarget();
    delay(2000);
    Serial.println('The servo on Target ' + target.getName() + ' should be lowered.');
    if (target.getServoPosition() == 0) {
        Serial.println('The servo on Target ' + target.getName() + ' has passed the lower test.');
    } else {
        Serial.println('The servo on Target ' + target.getName() + ' has failed the lower test.');
    }
    Serial.println("");
}

void testTargetLed(Target target) {
    if (target.getLedPinNumber() != NULL) {
        target.setLed(HIGH);
        Serial.println('The LED on Target ' + target.getName() + ' should be on.');
        if (target.getLedStatus() == 1) {
            Serial.println('The LED on Target ' + target.getName() + ' has passed the on test.');
        } else {
            Serial.println('The LED on Target ' + target.getName() + ' has failed the on test.');
        }

        target.setLed(LOW);
        Serial.println('The LED on Target ' + target.getName() + ' should be off.');
        if (target.getLedStatus() == 0) {
            Serial.println('The LED on Target ' + target.getName() + ' has passed the off test.');
        } else {
            Serial.println('The LED on Target ' + target.getName() + ' has failed the off test.');
        }
        Serial.println("");
    }
}

void testTargetPhotoresistor(Target target) {
    target.raiseTarget();
    delay(2000);

    Serial.println("TEST INSTRUCTION: Shine light into target photoresistor.");
    delay(3000);
    Serial.print("Beginning test in 3... ");
    delay(1000);
    Serial.print("2... ");
    delay(1000);
    Serial.print("1");
    delay(1000);
    
    int testValue = target.getPhotoresistorValue();
    Serial.println('The value of the photoresistor on Target ' + target.getName() + ' is ' + testValue);
    if (testValue > 0) {
        Serial.println('The photoresistor on Target ' + target.getName() + ' has passed the test.');
    } else {
        Serial.println('The photoresistor on Target ' + target.getName() + ' has failed the test.');
    }

    target.lowerTarget();
    delay(2000);
    Serial.println("");
}