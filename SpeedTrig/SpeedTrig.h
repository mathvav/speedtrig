/*
==============================================================
 SpeedTrig Library
==============================================================
 Original Code (C) 2012-2013 Oscar Liang
 Ported September 2014 with permission from original author
 Licensed under the MIT licence.
 
 This is a library to quickly do common trigonometry functions
 on Arduinos/other microprocessors.
 
 This is the main header file.
==============================================================
*/

//Include Guard:
#ifndef SpeedTrig_h
#define SpeedTrig_h

//Arduino libraries:
#include "Arduino.h"

class Speed_Trig {
  public:
    Speed_Trig();
    int radToMicro(float rad);
    int floatToInt(float input);
    float sin(int deg);
    float cos(int deg);
    float acos(float num);
    float atan2(float opp, float adj);
};

//Create class to use:
extern Speed_Trig SpeedTrig;

#endif //#ifndef SpeedTrig_h

