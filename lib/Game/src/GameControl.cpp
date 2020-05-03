#include "GameControl.h"
#include "troubleshooter.h"

/**
 * GameControl constructor.
 * 
 * @param frontTargets an array of targets that will be attached to front of physical game box. Cannot be NULL.
 * @param villain a target that represents the villain target. Cannot be NULL.
 * @param hostage a target that represents the hostage target. Cannot be NULL.
 * */
GameControl::GameControl(Target frontTargets[], AdvancedTarget villain, AdvancedTarget hostage) {
    for (int i = 0; i < 4; i++) {
        this->frontTargets[i] = frontTargets[i];
    }
    this->villain = villain;
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

    // main round
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
        if(frontTargets[randomNum].isRaised()) {
            frontTargets[randomNum].lowerTarget();
        }
    }

    // bonus round
    if (score * 100 > mode * 500) {
        Serial.println("You have reached the bonus round!");
        Serial.println("The villain has taken a hostage! Hit the villain but do not hit the hostage.");

        long bonusRoundEndTime = millis() + 10000;
        boolean villainHit = false;
        boolean hostageHit = false;
        while (millis() > bonusRoundEndTime && !villainHit && !hostageHit) {
            villain.moveAdvancedTarget();
            hostage.moveAdvancedTarget();
            villainHit = villain.evaluateTargetForHit(lightThreshold);
            hostageHit = hostage.evaluateTargetForHit(lightThreshold);
        }
        score = score + (villainHit * 20) - (hostageHit * 5);
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
        for (int mode = 0; mode < 4; mode++) {
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
    Serial.println("----- START TROUBLESHOOTING REPORT -----");

    for (int i = 0; i < 4; i++) {
        testTarget(frontTargets[i]);
    }
    testTarget(villain);
    testTarget(hostage);

    Serial.println("----- END TROUBLESHOOTING REPORT -----");
}

void GameControl::raiseFrontTargets() {
    for (int i = 0; i < 4; i++) {
        frontTargets[i].raiseTarget();
    }
}

void GameControl::raiseTargets() {
    raiseFrontTargets();
    villain.setTargetPosition(120);
    hostage.setTargetPosition(60);
}

void GameControl::lowerTargets() {
    for (int i = 0; i < 4; i++) {
        frontTargets[i].lowerTarget();
    }
    villain.lowerTarget();
    hostage.lowerTarget();
}

int GameControl::calibratePhotoresistors() {
    raiseTargets();
    int lightThreshold = 0;
    for (int i = 0; i < 4; i++) {
        evaluatePhotoresistor(lightThreshold, frontTargets[i].getPhotoresistorValue());
    }
    evaluatePhotoresistor(lightThreshold, villain.getPhotoresistorValue());
    evaluatePhotoresistor(lightThreshold, hostage.getPhotoresistorValue());
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