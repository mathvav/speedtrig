SpeedTrig
=========

Simple Arduino library that speeds up trigonometry functions, based on work by Oscar Liang.

Simply drag the main folder into the `libraries` subdirectory of your Arduino IDE sketch folder.

This is a simple output (via serial) to show accuracy of library compared to the Arduino functions:

```
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
```

Also useful if you need degrees for sin/cos.