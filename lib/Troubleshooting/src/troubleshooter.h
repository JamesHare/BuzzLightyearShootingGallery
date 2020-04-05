#include <Arduino.h>
#include <Servo.h>
#include "Target.h"

#ifndef TROUBLESHOOTER_H
#define TROUBLESHOOTER_H

void testTarget(Target target);
void testTargetServo(Target target);
void testTargetLed(Target target);
void testTargetPhotoresistor(Target target);

#endif