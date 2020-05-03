#include <Arduino.h>
#include "GameControl.h"

int startButton = 12;
const int ON = 1;
const int OFF = 0;

Target frontTargets[] = {
    Target("Front Target One", 6, A5, LED_BUILTIN),
    Target("Front Target Two", 7, A4, LED_BUILTIN),
    Target("Front Target Three", 8, A3, LED_BUILTIN),
    Target("Front Target Four", 9, A2, LED_BUILTIN)
};
AdvancedTarget villainTarget("Villain Target", 10, A1, LED_BUILTIN, 5);
AdvancedTarget hostageTarget("Hostage Target", 11, A0, LED_BUILTIN, 10);
GameControl gameControl(frontTargets, villainTarget, hostageTarget);

void setup() {
    Serial.begin(9600);
    pinMode(startButton, INPUT);
}

void loop() {
    boolean startSelected = digitalRead(startButton);
    if (startSelected) {
        gameControl.runGame();
    } else if (Serial.readString().equalsIgnoreCase("troubleshoot")) {
        gameControl.runTroubleshooting();
    }
}
