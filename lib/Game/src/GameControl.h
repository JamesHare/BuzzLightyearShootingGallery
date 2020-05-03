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
        AdvancedTarget villain;
        AdvancedTarget hostage;
        int lightThreshold;

        void startRound(int mode, int score);
        void raiseTargets();
        void raiseFrontTargets();
        void lowerTargets();
        int calibratePhotoresistors();
        void evaluatePhotoresistor(int currentLightThreashold, int newValue);
        boolean evaluateFrontTargetForHit(int target);
    
    public:
        GameControl();
        GameControl(Target frontTargets[], AdvancedTarget villain, AdvancedTarget hostage);

        Target* getfrontTargets() { return frontTargets; }
        AdvancedTarget getVillainTarget() { return villain; }
        AdvancedTarget getHostageTarget() { return hostage; }
        void runGame();
        void runTroubleshooting();

};

#endif