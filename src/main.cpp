#include <Arduino.h>
#include "GameControl.h"

int startButton = 12;
const int ON = 1;
const int OFF = 0;

Target targetOne("Front Target One", 6, A5, LED_BUILTIN);
Target targetTwo("Front Target Two", 7, A4, LED_BUILTIN);
Target targetThree("Front Target Three", 8, A3, LED_BUILTIN);
Target targetFour("Front Target Four", 9, A2, LED_BUILTIN);

Target frontTargets[] = {targetOne, targetTwo, targetThree, targetFour};
AdvancedTarget villainTarget("Villain Target", 10, A1, LED_BUILTIN, 5);
AdvancedTarget hostageTarget("Hostage Target", 11, A0, LED_BUILTIN, 10);
GameControl gameControl(frontTargets, villainTarget, hostageTarget);

void setup() {
    Serial.begin(9600);
    pinMode(startButton, INPUT);
    for (Target target : frontTargets) {
        target.init();
    }
    villainTarget.init();
    hostageTarget.init();
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
