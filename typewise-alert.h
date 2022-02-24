#pragma once

#include "infoTypes.h"

BreachType inferBreach(double value, Limit thresholdLimits);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendAlertToController(BreachType breachType);
void sendAlertToEmail(BreachType breachType);
