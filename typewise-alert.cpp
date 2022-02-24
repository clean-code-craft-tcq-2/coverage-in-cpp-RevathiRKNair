#include "typewise-alert.h"
#include <stdio.h>

std::map < BreachType, const char*> alertMessageMap = {
	{ TOO_LOW, "The temperature is too low" },
	{ TOO_HIGH, "the temperature is too high" }
};

std::map < CoolingType, Limit> coolingTypeLimits = {
	{ PASSIVE_COOLING, {0.00,35.00} },
	{ HI_ACTIVE_COOLING, {0.00,45.00} },
  { MED_ACTIVE_COOLING, {0.00,40.00} }
};





bool sendAlertToController(BreachType breachType) 
{
  const unsigned short header = 0xfeed;

  printf("%x : %x\n", header, breachType);

  return true;
}



bool sendAlertToEmail(BreachType breachType) 
{
  const char* recepient = "a.b@c.com";
  
  if(breachType != NORMAL)
  {
    const char* breachMessage = alertMessageMap[breachType];
    printf("To: %s\n", recepient);
    printf("%s\n", breachMessage);
    return true;
  }
  else
  {
    return false;
  }
}

void sendAlert(AlertTarget target, BreachType breachType)
{
  switch(target) 
  {
    case TO_CONTROLLER:
      sendAlertToController(breachType);
      break;
    case TO_EMAIL:
      sendAlertToEmail(breachType);
      break;
  }
}

BreachType inferBreach(double value, Limit limits) {
  if(value < limits.lower) {
    return TOO_LOW;
  }
  if(value > limits.upper) {
    return TOO_HIGH;
  }
  return NORMAL;
}

Limit getLimitsForCoolingType(CoolingType coolingType)
{

  Limit thresholdLimits;
  std::map < CoolingType, Limit>::iterator it = coolingTypeLimits.find(coolingType);

  if(it != coolingTypeLimits.end())
  {
    thresholdLimits = coolingTypeLimits.find(coolingType)->second; 

  }
  
  return thresholdLimits;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
 
  return inferBreach(temperatureInC, getLimitsForCoolingType(coolingType));
}



void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  sendAlert(alertTarget, breachType);
}

