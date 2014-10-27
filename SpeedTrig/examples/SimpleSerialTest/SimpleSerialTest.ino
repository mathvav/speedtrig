/*
==============================================================
 SpeedTrig Library
==============================================================
 Original Code (C) 2012-2013 Oscar Liang
 Ported September 2014 with permission from original author
 Licensed under the MIT licence.
 
 This is a library to quickly do common trigonometry functions
 on Arduinos/other microprocessors.
 
 This file is a dummy file to allow editing/compiling with the
 Arduino IDE. Select the tabs at the top for the associated
 file. Also serves as example sketch.
==============================================================
*/

/*
Serial output for this example showing accuracy of library (compare to calculator; cos/sin perfect, acos a little off but not too much):

Sin 15: 
 - Standard [RAD]: 0.6503
 - Fast [DEG]: 0.2588
Cos 15: 
 - Standard [RAD]: -0.7597
 - Fast [DEG]: 0.9659
Acos .15: 
 - Standard [RAD]: 1.4202
 - Fast [RAD]: 1.4230
Atan2 5, 5: 
 - Standard [RAD]: 0.7854
 - Fast [RAD]: 0.7823
*/

#include <SpeedTrig.h>

void setup() {
  //Start Serial for testing:
  Serial.begin(9600);
  //Send values:
  Serial.println("Sin 15: ");
  Serial.print(" - Standard [RAD]: ");
  Serial.println(sin(15), 4);
  Serial.print(" - Fast [DEG]: ");
  Serial.println(SpeedTrig.sin(15), 4);
  
  Serial.println("Cos 15: ");
  Serial.print(" - Standard [RAD]: ");
  Serial.println(cos(15), 4);
  Serial.print(" - Fast [DEG]: ");
  Serial.println(SpeedTrig.cos(15), 4);
  
  Serial.println("Acos .15: ");
  Serial.print(" - Standard [RAD]: ");
  Serial.println(acos(.15), 4);
  Serial.print(" - Fast [RAD]: ");
  Serial.println(SpeedTrig.acos(.15), 4);
  
  Serial.println("Atan2 5, 5: ");
  Serial.print(" - Standard [RAD]: ");
  Serial.println(atan2(5, 5), 4);
  Serial.print(" - Fast [RAD]: ");
  Serial.println(SpeedTrig.atan2(50, 50), 4);
}

void loop() {
}
