#include <Arduino.h>
#include <Servo.h>

#ifndef TARGET_H
#define TARGET_H

/**
 * Serves as a class for a game target. Provides the functionality to attach a servo
 * to a pin, set the servo to a degree and read the value of a photoresistor to signify
 * that the user has hit the target.
 * */
class Target {
    
    private:
        Servo servo;
        int servoPinNumber;
        int photoresistorPinNumber;
        int ledPinNumber;

    public:
        Target();
        Target(int servoPinNumber, int photoresistorPinNumber, int ledPinNumber);
        ~Target();

        Servo getServo() { return servo; }
        int getServoPinNumber() { return servoPinNumber; }
        int getPhotoresistorPinNumber() { return photoresistorPinNumber; }
        int getLedPinNumber() { return ledPinNumber; }
        int getLedStatus() { return digitalRead(ledPinNumber); }
        int getPhotoresistorValue();
        boolean isRaised();
        boolean evaluateTargetForHit(int lightThreshold);

        void setLed(int status);
        void toggleLed();
        void setTargetPosition(int degree);
        void raiseTarget();
        void lowerTarget();

};

#endif