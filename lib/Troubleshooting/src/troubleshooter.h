#include <Arduino.h>
#include <Servo.h>
#include "Target.h"

#ifndef TROUBLESHOOTER_H
#define TROUBLESHOOTER_H

/**
 * Serves as a class to run troubleshooting on a single target.
 * */
void testTarget(Target target);
void testTargetServo(Target target);
void testTargetLed(Target target);
void testTargetPhotoresistor(Target target);

#endif