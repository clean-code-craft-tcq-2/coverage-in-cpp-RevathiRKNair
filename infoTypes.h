#pragma once

#include <stdio.h>
#include <map>
#include<vector>
using namespace std;

struct Limit
{
  double lower;
  double upper;
};

typedef enum
{
    PASSIVE_COOLING,
    HI_ACTIVE_COOLING,
    MED_ACTIVE_COOLING
} CoolingType;

typedef enum 
{
    NORMAL,
    TOO_LOW,
    TOO_HIGH
} BreachType;

typedef enum 
{
    TO_CONTROLLER,
    TO_EMAIL
} AlertTarget;

typedef struct 
{
    CoolingType coolingType;
    char brand[48];
} BatteryCharacter;



