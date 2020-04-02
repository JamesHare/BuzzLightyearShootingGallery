#include "GameControl.h"

/**
 * GameControl constructor.
 * 
 * @param frontTargets an array of targets that will be attached to front of physical game box. Cannot be NULL.
 * @param zurg a target that represents the zurg target. Cannot be NULL.
 * @param hostage a target that represents the hostage target. Cannot be NULL.
 * */
GameControl::GameControl(Target frontTargets[], Target zurg, Target hostage) {
    for (int i = 0; i < 4; i++) {
        this->frontTargets[i] = frontTargets[i];
    }
    this->zurg = zurg;
    this->hostage = hostage;
    this->lightThreshold = calibratePhotoresistors();
}

/**
 * Starts a round.
 * 
 * @param mode the game mode. 0 = easy, 1 = medium, 2 = hard, 3 = impossible.
 * @param score the score counter for the round.
 * */
void GameControl::startRound(int mode, int score) {
    long roundEndTime = millis() + 30000;

    while (millis() < roundEndTime) {
        int randomNum = random(0, 3);
        frontTargets[randomNum].raiseTarget();

        long targetTimeLimit = millis() + 10000 - (2500 * mode);
        while (millis() < targetTimeLimit) {
            score = score + evaluateFrontTargetForHit(randomNum);
            if (!frontTargets[randomNum].isRaised()) {
                break;
            }
        }
    }

    if (score * 100 > mode * 500) {
        // TODO impl bonus round with Zurg and hostage.
    }
}

void GameControl::runGame() {
    int score = 0;
    raiseFrontTargets();
    Serial.println("Shoot a target to make a game mode selection.");
    Serial.println("From left to right: East | Medium | Hard | Impossible");

    long selectionTimer = millis() + 30000;

    // 30 seconds to select a mode and initiate the game
    while (millis() < selectionTimer) {
        for (int mode = 0; mode < 3; mode++) {
            if (frontTargets[mode].getPhotoresistorValue() > lightThreshold) {
                lowerTargets();
                startRound(mode, score);
                break;
            }
        }
    }

    lowerTargets(); // lower targets when game is over or a mode selection has not been made
    Serial.println("!! GAME OVER !!");
    Serial.println('You scored ' + (score * 100) + ' points.');
}

void GameControl::runTroubleshooting() {
    // TODO impl for running troubleshooting
}

void GameControl::raiseFrontTargets() {
    for (int i = 0; i < 4; i++) {
        frontTargets[i].raiseTarget;
    }
}

void GameControl::raiseTargets() {
    raiseFrontTargets();
    zurg.setTargetPosition(120);
    hostage.setTargetPosition(60);
}

void GameControl::lowerTargets() {
    for (int i = 0; i < 4; i++) {
        frontTargets[i].lowerTarget;
    }
    zurg.lowerTarget;
    hostage.lowerTarget;
}

int GameControl::calibratePhotoresistors() {
    raiseTargets();
    int lightThreshold = 0;
    for (int i = 0; i < 4; i++) {
        evaluatePhotoresistor(lightThreshold, frontTargets[i].getPhotoresistorValue());
    }
    evaluatePhotoresistor(lightThreshold, zurg.getPhotoresistorValue());
    evaluatePhotoresistor(lightThreshold, hostage.getPhotoresistorValue);
    return lightThreshold + 500;
}

void GameControl::evaluatePhotoresistor(int currentLightThreashold, int newValue) {
    if (newValue > currentLightThreashold) {
        currentLightThreashold = newValue;
    }
}

boolean GameControl::evaluateFrontTargetForHit(int target) {
    boolean successfulHit = frontTargets[target].evaluateTargetForHit(lightThreshold);
    if (successfulHit) {
        frontTargets[target].lowerTarget();
    }
    return successfulHit;
}

boolean GameControl::evaluateZurgTargetForHit() {
    return zurg.evaluateTargetForHit(lightThreshold);
}

boolean GameControl::evaluateHostageTargetForHit() {
    return hostage.evaluateTargetForHit(lightThreshold);
}