#include "Target.h"

#ifndef GAMECONTROL_H
#define GAMECONTROL_H

/**
 * Serves as a class for the main game control. Has the functionality to run a game, calibrate photoresistors
 * and call the troubleshooter.
 * */
class GameControl {

    private:
        Target frontTargets[4];
        Target zurg;
        Target hostage;
        int lightThreshold;

        void startRound(int mode, int score);
        void raiseTargets();
        void raiseFrontTargets();
        void lowerTargets();
        int calibratePhotoresistors();
        void evaluatePhotoresistor(int currentLightThreashold, int newValue);
        boolean evaluateFrontTargetForHit(int target);
        boolean evaluateZurgTargetForHit();
        boolean evaluateHostageTargetForHit();
    
    public:
        GameControl();
        GameControl(Target frontTargets[], Target zurg, Target hostage);

        Target* getfrontTargets() { return frontTargets; }
        Target getZurgTarget() { return zurg; }
        Target getHostageTarget() { return hostage; }
        void runGame();
        void runTroubleshooting();

};

#endif