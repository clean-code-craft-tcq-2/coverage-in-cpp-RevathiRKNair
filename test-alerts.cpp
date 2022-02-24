#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

BatteryCharacter batteryCharTest;


TEST_CASE("infers the breach according to limits") 
{
  Limit lowerLimit = {25,35};
  REQUIRE(inferBreach(12, lowerLimit) == TOO_LOW);
  
  Limit upperLimit = {20,40};
  REQUIRE(inferBreach(46, upperLimit) == TOO_HIGH);

  Limit normalLimit = {10,40};
  REQUIRE(inferBreach(40, normalLimit) == NORMAL);
  REQUIRE(inferBreach(20, normalLimit) == NORMAL);
}



TEST_CASE("classifyTemperatureBreach the breach according to limits") 
{

  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 30) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -10) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 36) == TOO_HIGH);

  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 45) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -20) == TOO_LOW);

  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 40) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 100) == TOO_HIGH);
}



TEST_CASE("test check and alert") 
{
  batteryCharTest.coolingType = CoolingType::PASSIVE_COOLING;
  checkAndAlert(TO_CONTROLLER, batteryCharTest , 30);
  checkAndAlert(TO_EMAIL, batteryCharTest , 35) ;
  
  batteryCharTest.coolingType = CoolingType::HI_ACTIVE_COOLING;
  checkAndAlert(TO_CONTROLLER, batteryCharTest , 42);
  checkAndAlert(TO_EMAIL, batteryCharTest , 45);

  batteryCharTest.coolingType = CoolingType::MED_ACTIVE_COOLING;
  checkAndAlert(TO_CONTROLLER, batteryCharTest , -10);
  checkAndAlert(TO_EMAIL, batteryCharTest , -15);
}


TEST_CASE("test send to controller") 
{
  sendAlertToController(NORMAL);
  sendAlertToController(TOO_LOW);
  sendAlertToController(TOO_HIGH);
}

TEST_CASE("test send to email") 
{
  sendAlertToEmail(NORMAL);
  sendAlertToEmail(TOO_LOW);
  sendAlertToEmail(TOO_HIGH);
}
