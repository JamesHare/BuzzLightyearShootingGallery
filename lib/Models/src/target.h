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
        String name;
        Servo servo;
        int servoPinNumber;
        int photoresistorPinNumber;
        int ledPinNumber;

    public:
        Target();
        Target(String name, int servoPinNumber, int photoresistorPinNumber, int ledPinNumber);
        ~Target();

        String getName() { return name; }
        Servo getServo() { return servo; }
        int getServoPinNumber() { return servoPinNumber; }
        int getServoPosition() { return servo.read(); }
        int getPhotoresistorPinNumber() { return photoresistorPinNumber; }
        int getLedPinNumber();
        int getLedStatus();
        int getPhotoresistorValue();
        boolean isRaised();
        boolean evaluateTargetForHit(int lightThreshold);

        void setLed(int status);
        void toggleLed();
        void setTargetPosition(int degree);
        void raiseTarget();
        void lowerTarget();

};

class AdvancedTarget : public Target {

    private:
        String movingDirection;
        int moveDistance;

    public:
        AdvancedTarget();
        AdvancedTarget(String name, int servoPinNumber, int photoresistorPinNumber, int ledPinNumber, int moveDistance):Target(name, servoPinNumber, photoresistorPinNumber, ledPinNumber){};
        void setMovingDirection(String movingDirection) { this->movingDirection = movingDirection; }
        String getMovingDirection() { return movingDirection; }
        void moveAdvancedTarget();
        void resetTarget();

};

#endif