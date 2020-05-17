#include <Arduino.h>
#include "GameControl.h"

int startButton = 12;
const int ON = 1;
const int OFF = 0;

Servo targetOneServo;
Servo targetTwoServo;
Servo targetThreeServo;
Servo targetFourServo;
Servo targetVillainServo;
Servo targetHostageServo;

Target targetOne("Front Target One", targetOneServo, 6, A5, LED_BUILTIN);
Target targetTwo("Front Target Two", targetTwoServo, 7, A4, LED_BUILTIN);
Target targetThree("Front Target Three", targetThreeServo, 8, A3, LED_BUILTIN);
Target targetFour("Front Target Four", targetFourServo, 9, A2, LED_BUILTIN);

Target frontTargets[] = {targetOne, targetTwo, targetThree, targetFour};
AdvancedTarget villainTarget("Villain Target", targetVillainServo, 10, A1, LED_BUILTIN, 5);
AdvancedTarget hostageTarget("Hostage Target", targetHostageServo, 11, A0, LED_BUILTIN, 10);
GameControl gameControl(frontTargets, villainTarget, hostageTarget);

void setup() {
    Serial.begin(9600);
    pinMode(startButton, INPUT);
    targetOneServo.attach(6);
    targetTwoServo.attach(7);
    targetThreeServo.attach(8);
    targetFourServo.attach(9);
    targetVillainServo.attach(10);
    targetHostageServo.attach(11);
}

void loop() {
    targetOne.raiseTarget();
    targetTwo.raiseTarget();
    targetThree.raiseTarget();
    targetFour.raiseTarget();
    villainTarget.raiseTarget();
    hostageTarget.raiseTarget();
    delay(2000);
    targetOne.lowerTarget();
    targetTwo.lowerTarget();
    targetThree.lowerTarget();
    targetFour.lowerTarget();
    villainTarget.lowerTarget();
    hostageTarget.lowerTarget();
    delay(2000);
    // boolean startSelected = digitalRead(startButton);
    // if (startSelected) {
    //     gameControl.runGame();
    // } else if (Serial.readString().equalsIgnoreCase("troubleshoot")) {
    //     gameControl.runTroubleshooting();
    // }
}
