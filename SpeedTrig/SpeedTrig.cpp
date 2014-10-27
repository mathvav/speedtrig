/*
==============================================================
 SpeedTrig Library
==============================================================
 Original Code (C) 2012-2013 Oscar Liang
 Ported September 2014 with permission from original author
 Licensed under the MIT licence.
 
 This is a library to quickly do common trigonometry functions
 on Arduinos/other microprocessors.
 
 This file is the main code file.
==============================================================
*/// ____                _              _         
//  / ___|___  _ __  ___| |_ __ _ _ __ | |_ ___ _ 
// | |   / _ \| '_ \/ __| __/ _` | '_ \| __/ __(_)
// | |__| (_) | | | \__ \ || (_| | | | | |_\__ \_ 
//  \____\___/|_| |_|___/\__\__,_|_| |_|\__|___(_)
// 

#include "SpeedTrig.h"

const float PIby2 = PI / 2;

#define MAX_UINT  65535
#define MIN_INT -32768
#define MAX_INT  32767

#define DEC1 10
#define DEC2 100
#define DEC3 1000
#define DEC4 10000

//Sin Lookup table
const float SIN_TABLE[181]={
  0.000000, 0.008727, 0.017452, 0.026177, 0.034899, 0.043619, 0.052336, 0.061049, 0.069756, 0.078459, 0.087156, 0.095846, 0.104528,
  0.113203, 0.121869, 0.130526, 0.139173, 0.147809, 0.156434, 0.165048, 0.173648, 0.182236, 0.190809, 0.199368, 0.207912, 0.216440,
  0.224951, 0.233445, 0.241922, 0.250380, 0.258819, 0.267238, 0.275637, 0.284015, 0.292372, 0.300706, 0.309017, 0.317305, 0.325568,
  0.333807, 0.342020, 0.350207, 0.358368, 0.366501, 0.374607, 0.382683, 0.390731, 0.398749, 0.406737, 0.414693, 0.422618, 0.430511,
  0.438371, 0.446198, 0.453990, 0.461749, 0.469472, 0.477159, 0.484810, 0.492424, 0.500000, 0.507538, 0.515038, 0.522499, 0.529919,
  0.537300, 0.544639, 0.551937, 0.559193, 0.566406, 0.573576, 0.580703, 0.587785, 0.594823, 0.601815, 0.608761, 0.615661, 0.622515,
  0.629320, 0.636078, 0.642788, 0.649448, 0.656059, 0.662620, 0.669131, 0.675590, 0.681998, 0.688355, 0.694658, 0.700909, 0.707107,
  0.713250, 0.719340, 0.725374, 0.731354, 0.737277, 0.743145, 0.748956, 0.754710, 0.760406, 0.766044, 0.771625, 0.777146, 0.782608,
  0.788011, 0.793353, 0.798636, 0.803857, 0.809017, 0.814116, 0.819152, 0.824126, 0.829038, 0.833886, 0.838671, 0.843391, 0.848048,
  0.852640, 0.857167, 0.861629, 0.866025, 0.870356, 0.874620, 0.878817, 0.882948, 0.887011, 0.891007, 0.894934, 0.898794, 0.902585,
  0.906308, 0.909961, 0.913545, 0.917060, 0.920505, 0.923880, 0.927184, 0.930418, 0.933580, 0.936672, 0.939693, 0.942641, 0.945519,
  0.948324, 0.951057, 0.953717, 0.956305, 0.958820, 0.961262, 0.963630, 0.965926, 0.968148, 0.970296, 0.972370, 0.974370, 0.976296,
  0.978148, 0.979925, 0.981627, 0.983255, 0.984808, 0.986286, 0.987688, 0.989016, 0.990268, 0.991445, 0.992546, 0.993572, 0.994522,
  0.995396, 0.996195, 0.996917, 0.997564, 0.998135, 0.998630, 0.999048, 0.999391, 0.999657, 0.999848, 0.999962, 1.000000
};

/*
  acos lookup table is split into three parts, which has a higher accuracy nearer acos(1).
    - 0 to 0.9 is done in steps of 0.0079 rads. (1/127)
    - 0.9 to 0.99 is done in steps of 0.0008 rads. (0.01/127)
    - 0.99 to 1 is done in steps of 0.0002 rads. (0.01/64)	
*/
const byte ACOS_TABLE[278] = {
  255, 254, 252, 251, 250, 249, 247, 246, 245, 243, 242, 241, 240, 238, 237, 236, 234, 233, 232, 231, 229, 228, 227, 225, 224, 223,
  221, 220, 219, 217, 216, 215, 214, 212, 211, 210, 208, 207, 206, 204, 203, 201, 200, 199, 197, 196, 195, 193, 192, 190, 189, 188,
  186, 185, 183, 182, 181, 179, 178, 176, 175, 173, 172, 170, 169, 167, 166, 164, 163, 161, 160, 158, 157, 155, 154, 152, 150, 149,
  147, 146, 144, 142, 141, 139, 137, 135, 134, 132, 130, 128, 127, 125, 123, 121, 119, 117, 115, 113, 111, 109, 107, 105, 103, 101,
  98, 96, 94, 92, 89, 87, 84, 81, 79, 76, 73, 73, 73, 72, 72, 72, 71, 71, 71, 70, 70, 70, 70, 69, 69, 69, 68, 68, 68, 67, 67, 67,
  66, 66, 66, 65, 65, 65, 64, 64, 64, 63, 63, 63, 62, 62, 62, 61, 61, 61, 60, 60, 59, 59, 59, 58, 58, 58, 57, 57, 57, 56, 56, 55,
  55, 55, 54, 54, 53, 53, 53, 52, 52, 51, 51, 51, 50, 50, 49, 49, 48, 48, 47, 47, 47, 46, 46, 45, 45, 44, 44, 43, 43, 42, 42, 41,
  41, 40, 40, 39, 39, 38, 37, 37, 36, 36, 35, 34, 34, 33, 33, 32, 31, 31, 30, 29, 28, 28, 27, 26, 25, 24, 23, 23, 23, 23, 22, 22,
  22, 22, 21, 21, 21, 21, 20, 20, 20, 19, 19, 19, 19, 18, 18, 18, 17, 17, 17, 17, 16, 16, 16, 15, 15, 15, 14, 14, 13, 13, 13, 12,
  12, 11, 11, 10, 10, 9, 9, 8, 7, 6, 6, 5, 3, 0
};

//============================================================
//  _   _ _   _ _ _ _   _             
// | | | | |_(_) (_) |_(_) ___  ___ _ 
// | | | | __| | | | __| |/ _ \/ __(_)
// | |_| | |_| | | | |_| |  __/\__ \_ 
//  \___/ \__|_|_|_|\__|_|\___||___(_)
// 

Speed_Trig::Speed_Trig() {
  //Nothing to setup here!
}

int Speed_Trig::radToMicro(float rad) {
  //600 - 180 degree
  //2400 - 0 degree
  
  //y = ax + b
  //x = 0: y = a*0 + b = 2400, so b = 2400
  //x = pi (180'): y = a*pi + 2400 = 600, so a = -1800/pi
  //therefore y = 2400 - 1800/pi*x
  
  //Make sure rad isn't negative:
  if(rad < 0) {
    rad = -rad;
  }
  
  while(rad > PI) {
    rad -= PI;
  }
  
  return 2400 - SpeedTrig.floatToInt(572.958 * rad);
}

int Speed_Trig::floatToInt(float input) {
  //Rounding a number avoiding truncation:
  return (int)(input + 0.5);
}

//============================================================
//  _____     _         
// |_   _| __(_) __ _ _ 
//   | || '__| |/ _` (_)
//   | || |  | | (_| |_ 
//   |_||_|  |_|\__, (_)
//              |___/   
// 

//The functions for sin and cos use lookup table to determine the sin or cos value of the input angle.
//Input for these functions are scaled up 10 times. e.g. -450 = -45.0 deg
//  - Both functions return a value between -1 and 1. (e.g. input: -450, output -> -0.7071)
float Speed_Trig::sin(int deg) {
  deg *= 10;
  float result = 0;
  int sign = 1;
  
  if (deg < 0) {
    deg = -deg;
    sign = -1;
  }
  
  while(deg >= 3600) {
    deg =- 3600;
  }
  
  if((deg >= 0) && (deg <= 900)) {
    //0 and 90 degrees.
    result = SIN_TABLE[deg / 5];
    
  } else if((deg > 900) && (deg <= 1800)) {
    //90 and 180 degrees.
    result = SIN_TABLE[(1800 - deg) / 5];
    
  } else if((deg > 1800) && (deg <= 2700)) {
    //180 and 270 degrees.
    result = -SIN_TABLE[(deg - 1800) / 5];
    
  } else if((deg > 2700) && (deg <= 3600)) {
    //270 and 360 degrees.
    result = -SIN_TABLE[(3600 - deg) / 5];
  
  }
  return sign * result;
}

float Speed_Trig::cos(int deg) {
  deg *= 10;
  float result = 0;           
  if (deg < 0) {
    deg = -deg;
  }
  
  while(deg >= 3600) {
    deg =- 3600;
  }
  
  if((deg >= 0) && (deg <= 900)) {
    //0 and 90 degrees.
    result = SIN_TABLE[(900 - deg) / 5];
  
  } else if((deg > 900) && (deg <= 1800)) {
    //90 and 180 degrees.
    result = -SIN_TABLE[(deg - 900) / 5];
  
  } else if((deg > 1800) && (deg <= 2700)) {
    //180 and 270 degrees.
    result = -SIN_TABLE[(2700 - deg) / 5];
  
  } else if((deg >= 2700) && (deg <= 3600)) {
    //270 and 360 degrees.
    result = SIN_TABLE[(deg - 2700) / 5];
    
  }
  return result;
}


//The acos function uses a lookup table for corresponding output. 
//Output data are stored as byte values (0 - 255), they are scaled down to float number (0.0 - 1.0) for output.
float Speed_Trig::acos(float num) {
  float rads = 0;
  bool negative = false;
  
  //Get sign of input
  if(num < 0) {
    negative = true;
    num = -num;
  }
  
  if((num >= 0) && (num < 0.9)) {
    //num between 0 and 0.9.
    rads = (float)ACOS_TABLE[SpeedTrig.floatToInt(num * DEC4 / 79)] * 0.00616;
    
  } else if ((num >= 0.9) && (num < 0.99)) {
    //num between 0.9 and 0.99.
    rads = (float)ACOS_TABLE[SpeedTrig.floatToInt((num * DEC4 - 9000) / 8) + 114] * 0.00616;
    
  } else if ((num >= 0.99) && (num <= 1)) {
    //num between 0.99 and 1.0.
    rads = (float)ACOS_TABLE[SpeedTrig.floatToInt((num * DEC4 - 9900) / 2) + 227] * 0.00616;
  }

  //Account for the negative sign if required.
  if(negative) {
    rads = PI - rads;
  }
  
  return rads;
}

float Speed_Trig::atan2(float opp, float adj) {
  float hypt = sqrt(adj * adj + opp * opp);
  float rad = SpeedTrig.acos(adj / hypt);
  
  if(opp < 0) {
    rad = -rad;
  }
  
  return rad;
}

//Initialize SpeedTrig object:
Speed_Trig SpeedTrig;
